#pragma once

#include <LinkedList.h>
#include "Streaming.h"
#include "stateM.h"

void printFloat(float , int );

#ifdef SERIAL_ON
#define PRINTLN(A) Serial.println(A)
#define PRINT(A) Serial.print(A)
#else
#define PRINTLN(A) 
#define PRINT(A) 
#endif
//#define DEBUG
//#define DEBUG_GEN

#ifdef DEBUG
#define PRINTLND(A) Serial.println(A)
#define PRINTD(A) Serial.print(A)
#define PRINTLNFD(A) printFloat(A,1) ; Serial.println()
#define PRINTFD(A) printFloat(A,1)

#else
#define PRINTLND(A)
#define PRINTD(A)
#define PRINTLNFD(A)
#define PRINTFD(A)
#endif

#define INT() PRINTLND("INT");interrupts()
#define NOINT() PRINTLND("NO INT");noInterrupts()


#if defined(WIRING) && WIRING >= 100
#include <Wiring.h>
#elif defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <string.h>

#define MIN_POWER 5 // Values under this won't lit the current LEDs we use at the PWM freq we use

#define CHECK(A) if(A==CmdParser::ERROR){PRINTLN("Parse error");PRINTD ("cursor ");PRINTLND(m_cursorPos);PRINTD ("buffer ");PRINTLND(m_lineBuffer);doneWithThisLine();return CmdParser::ERROR;}
#define UCHECK(A) if(A!=1){PRINTLN("Parse error");PRINTD ("cursor ");PRINTLND(m_cursorPos);PRINTD ("buffer ");PRINTLND(m_lineBuffer);doneWithThisLine(); return;}


void fastAnalogWrite(uint8_t , uint8_t );

void setPwmFrequencyMEGA2560(int pin, int divisor);

// Size of the input buffer in bytes (maximum length of one command plus arguments)
#define SerialParse_BUFFER 1024

// Uncomment the next line to run the library in debug mode (verbose messages)
#define SerialParse_DEBUG



void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
  // transmit diagnostic informations through serial link.
  Serial.println(__func);
  Serial.println(__file);
  Serial.println(__lineno, DEC);
  Serial.println(__sexp);
  Serial.flush();
  // abort program execution.
  abort();
}


/*
   Begin Log
   Stores log into RAM, usefull from interrupts since we can not use serial there

*/
class LogData {
  public:
    enum origins {PULSE_ID, FREQ_ID, PROGRAMME_ID, LAST_ID};
    enum programme_log_actions {ON_P, NEWSTEP_P, END_OF_STEP_P, DONE_P, OFF_P};
    enum pulse_log_actions {ON_PU = OFF_P + 1, SETPARAMS_PU, BLEND_LOW_DELAYED_PU, BLEND_LOW_IMMEDIATE_PU, BLEND_HIGH_DELAYED_PU, BLEND_HIGH_IMMEDIATE_PU, OFF_PU};
    enum osc_log_actions {ON_O = OFF_PU + 1, SETPARAMS_O, DONE_O, OFF_O, LAST_O};
    static const __FlashStringHelper*getOriginLabel(uint8_t);
    static const __FlashStringHelper*getActionLabel(uint8_t);

    void print(uint16_t);
    uint8_t origin, action;
    uint32_t timestamp, value, cycle;
};

class Log {
  public :


    void add(const LogData &);
    void clear();
    void print();
    void on();
    void off();
    static Log log1;
  private:
    bool m_power {false};
    LinkedList<LogData> m_log;

};

/*
   End log
*/

/*
   Begin Processor
   generic Class with power and run state and tick() method
*/


class Processor {

  public:

    Processor() : m_isOn(false), m_isDone(true), m_time(0) {}
    void setPower(bool isOn) ; // must be called only from inside interrupt routine
    void protectedSetPower(bool isOn); // same as before, must be called only from outside interrupt routine
    virtual void tick()  = 0 ; // must be called at each cycle to run the machine

    // geters

    bool isRunning() ; // generator is powered and not done
    bool isDone() ; // generator is powered and done
    bool getPower() ;

  // protected: enable
    // Those are called autmatically when transitions happen due to setPower() calls
    virtual void actionOn2Off()  {};
    virtual void actionOff2On()  {};

    uint32_t m_time = 0; // internal counter (kind of clock), increment each time the tick() method is called
    bool m_isOn; // generator power state. If false, outputs always return low.
    bool m_isDone; // generator job state. Turns true when job timer expires, turns off when new job starts
};
/*
   End Processor
*/


class SerialParse {
  public:
    SerialParse ();      // Constructor
    void readSerial();    // Main entry point.
    void clearBuffer();   // Clears the input buffer.
    bool isEOL();
    char *getBuffer();

  private:
    char delim[2]; // null-terminated list of character to be used as delimeters for tokenizing (default " ")
    char term;     // Character that signals end of command (default '\n')

    char buffer[SerialParse_BUFFER + 1]; // Buffer of stored characters while waiting for terminator character
    byte bufPos;                        // Current position in the buffer
    byte bufRPos;
    char *last;                         // State variable used by strtok_r during processing
    bool EOL;
};

#define LABEL_SIZE 8
#define NB_OSC 4
#define NB_LED 4

#define FREQ_DIVISOR 100 // used to avoid floats. ex 5.65 HZ = 565
#define MAX_F 20000 // 200 x FREQ_DIVISOR
#define MIN_F 10 // 0.1 x FREQ_DIVISOR
#define MAX_DUTY 99
#define MIN_DUTY 1
enum OscWave {OFF, SQUARE, SINE, LAST_WAVE};

class LEDdata {
  public:
    LEDdata() : start(0), end(0) {};
    void print(uint8_t l);
    uint8_t start, end; //intensity
};

class Osc {
  public:
    Osc () : wave (1), freqStart(10), freqEnd(10), dutyStart(50), dutyEnd(50) {};
    void print(uint8_t l);
    uint8_t wave;
    uint16_t freqStart, freqEnd;
    uint8_t dutyStart, dutyEnd;
    LEDdata intensity [NB_LED];
};




class Step {
  public:
    Step () : m_duration (0) {
      strcpy(description, "");
    };
    uint32_t m_duration;
    char description [LABEL_SIZE];
    Osc osc[NB_OSC];
};

// prgPeriodMultiplier = 1 : programme runs every sec
// prgPeriodMultiplier = 10 : programme runs every 0.1 sec
// ...

class HWDimLed;
class FreqGen;


//#define prgPeriodMultiplier 10
/*
   Begin Programme
*/

class Programme : public Processor, public StateM {

  public :
    enum { NO_CHANGE, OFF, FIRST_CYCLE, RUNNEWSTEP, WAITENDOFSTEP, DONE, SERROR }; // STATES
    Programme() : m_nbSteps(0), m_duration(0), m_currentStepN(0), m_dim(1), dState(0), dCpt(0), steps(LinkedList<Step * >()) {
      for (int i = 0; i < NB_OSC; i++) m_osc[i] = 0;
      for (int i = 0; i < NB_LED; i++) m_led[i] = 0;
    };

    void tick()  final;
    void init(HWDimLed *led[NB_LED], FreqGen *osc[NB_OSC]) ;
    void setNbSteps(uint16_t) ;
    void setDuration(uint16_t) ;
    void setDim(uint8_t dim) ;
    void print() ;
    void printStep(uint8_t, Step *);
    void printCurrentStepShort();
    uint16_t getCurrentStepN();
    void printState() ;
    void applyOutputs() ;
    uint8_t getOutput (uint8_t led) ;
    void clear() ; // erase previous program
    uint8_t dState;
    uint16_t dCpt;
    LinkedList<Step*> steps;
    uint16_t m_debug1 {0};
  private :
    void printID() final;
    uint8_t loop(uint8_t state, uint8_t action, uint8_t cycle) override ; // actual StateMachine loop method, called from StateM father
    virtual void actionOff2On() final;
    virtual void actionOn2Off() final;
    uint16_t m_nbSteps, m_duration;
    uint16_t m_currentStepN;
    uint32_t m_timeInStep;

    HWDimLed *m_led[NB_LED];
    FreqGen *m_osc[NB_OSC];

    uint8_t m_dim; // 1->10 Global DIM for LED outputs
};

/*
   End Programme
*/


/*
   Begin PulseGen
   Square signal generator. Frequency can be adjusted while running.
*/

// interrupt period in micro seconds
// 100 is right for computation but Arduino can't follow all the job we have to do during interrupts
// We try 1000, it will give bad frequency precision, but no choice here...
#define interruptPeriod 1000
#define baseFreqFreq 10 // frequency generator is called at this frequency
class FreqTimeStamp {
  public:
    FreqTimeStamp (uint32_t sysTime, uint32_t cycleLength, uint32_t highLength, uint32_t lowLength,
                   bool pulse, uint32_t nextHighTime, uint32_t nextLowTime, uint8_t myCase) :
      m_sysTime(sysTime), m_cycleLength(cycleLength), m_highLength(highLength), m_lowLength(lowLength),
      m_pulse(pulse), m_nextHighTime(nextHighTime), m_nextLowTime(nextLowTime), m_case(myCase) {};

    void  print();
  private:
    uint32_t m_sysTime;
    bool m_pulse;
    uint16_t m_freq;
    uint8_t m_duty;
    uint32_t m_highLength, m_lowLength, m_cycleLength;
    uint32_t m_nextHighTime;
    uint32_t m_nextLowTime;
    uint8_t m_case;
};

class IPulseGen : public Processor {
  public:
    void virtual setParams(uint16_t freq, uint8_t duty, uint8_t wave)  = 0 ;
    void virtual print() = 0;

    // geters
    uint16_t virtual getFreq() = 0;
    uint8_t virtual getDuty() = 0;
    uint8_t virtual getPulse()  = 0; // actual oscillator output
};

class PulseGen : public IPulseGen {
  public:
    PulseGen() : m_freq(10), m_duty(50), m_nextHighTime(0), m_nextLowTime(0),
      m_cycle(0), m_pulse(0), m_lastHighTime(0), m_lastLowTime(0), m_inTransition(false), m_freqTimeStamp(LinkedList<FreqTimeStamp * >()) {};
    // seters and actions


    void setParams(uint16_t freq, uint8_t duty, uint8_t wave) ; // can be called even if the generator is already running
    void tick()  override; // must be called at each cycle to run the generator
    void print();

    // geters

    uint16_t getFreq();
    uint8_t getDuty();
    uint8_t getPulse() ; // actual oscillator output

    // static stuff
    static PulseGen *getFromStore(uint8_t n);

    void resetCounters();
    uint32_t m_cycle; // pulse counter, increment each time pulse switch from low to high
    uint16_t m_freq; // frequency of the generator (unit is 0.1Hz. Example 10 is 1 Hz)
    uint8_t m_duty; // duty of the generated pulse (percentage)
    bool m_pulse; // actual pulse state. At this level it is only 0 or 1, even for Sinus generator
    uint8_t m_wave; // wave type
    uint32_t m_nextHighTime; // next time we shall switch pulse to High
    uint32_t m_lastHighTime; // next time we have switched pulse to High
    uint32_t m_nextLowTime; // next time we shall switch pulse to Low
    uint32_t m_lastLowTime; // next time we have switched pulse to Low
    uint32_t m_highLength, m_lowLength;
    bool m_inTransition; // is true during the period between last pulse freq/duty and new freq/duty. Used to reset counters at the exact moment required.
    LinkedList<FreqTimeStamp*> m_freqTimeStamp;

    // static stuff
    static PulseGen store[NB_OSC];

  private:
    virtual void actionOff2On() final;
    virtual void actionOn2Off() final;
    uint8_t ourSinus();
};

/*
   End PulseGen
*/


class PulseTimeStamp {
  public:
    PulseTimeStamp(uint32_t sysTime, bool pulse, bool inTransition): m_sysTime(sysTime), m_pulse(pulse), m_inTransition(inTransition)  {};

    void  print();
  private:
    uint32_t m_sysTime;
    bool m_pulse;
    bool m_inTransition;
};

// Histo class for PulseGen. Logs timestamped pulse changes into RAM , to be printer after a run.
class HistoPulseGen : public PulseGen {
  public :
    HistoPulseGen() : pulseTimeStamps(LinkedList<PulseTimeStamp * >()) {};
    void tick()  override;
    // bool getPulse(); // log wil happen upon pulse read
    void print();
  private :
    LinkedList<PulseTimeStamp*> pulseTimeStamps;
    bool m_lastPulse;
    uint32_t m_sysTime;
    bool m_inTransition;
};


/*
   Begin FreqGen
   Generates moving frequency and duty using linear math
*/

// freqPeriodMultiplier = 1 : freqGen runs every sec
// freqPeriodMultiplier = 10 : freqGen runs every 0.1 sec


#define freqPeriodMultiplier 10


class FreqGen : public Processor {
  public:
    FreqGen() {};
    // seters and actions
    void init (PulseGen *pulseGen);
    bool setParams(uint8_t wave, uint16_t freqStart, uint16_t freqEnd, uint8_t dutyStart, uint8_t dutyEnd, LEDdata intensity[], uint16_t stepDuration); // if called even when the generator is already running : no effect, new values are ignored and we return false
    void tick()  final; // must be called at each cycle to run the generator

    // geters
    bool getCalcValues(uint16_t &currentFreq, uint8_t &currentDuty ); // will return false if values are not fresh (generator not running)
    uint8_t getIntensity(uint8_t ledN); // return the calculated Intensity for led #ledN
    uint8_t getPulse(); // give pulse state of underlying pulseGenerator
    void print();
    // static stuff
    static FreqGen *getFromStore(uint8_t n);
    volatile static uint8_t icycle;
    void resetCounters();

  private:
    virtual void actionOff2On() final;
    virtual void actionOn2Off() final;

    uint8_t m_wave; // generator type : off,square, sinus
    uint16_t m_freqStart; // start frequency in 0.1 Hz, stored parameter
    uint16_t m_freqEnd; // end frequency in 0.1 Hz, stored parameter
    uint8_t m_dutyStart; // start duty in percentage, stored parameter
    uint8_t m_dutyEnd; // end duty in percentage, stored parameter
    LEDdata m_intensity [NB_LED]; // intensity in percentage of current Oscillator for each LED, stored parameter

    uint16_t m_duration; // generator duration in seconds

    uint16_t m_currentFreq; // current frequency in 0.1 Hz, calculated
    uint8_t m_currentDuty; // current duty in percentage, calculated
    uint8_t m_currentIntensity[NB_LED]; // current intensity in percentage of current Oscillator for each LED, calculated
    uint8_t m_tmpIntensity[NB_LED]; // current intensity in percentage of current Oscillator for each LED, calculated
    
    PulseGen *m_pulseGen; // each freq generator has its slave pulse generator

    // static stuff
    static FreqGen store[NB_OSC];
};


// END Frequency Generator

class HWDimLed {
  public :
    HWDimLed() : m_dim(1), m_state(0), m_hwoutput(0) {};
    void setPin(uint8_t pin);
    void setState(bool state);
    void setDim (uint8_t dim);
    void setDimedState(bool state, uint8_t dim );

    // static stuff
    static HWDimLed *getFromStore(uint8_t n);

  private :
    uint8_t m_hwoutput; // the HW output number
    uint8_t m_dim; // dim level from 0 (off) to 255 (full on)
    bool m_state; // 0 : off, 1 : on at dim level

    // static stuff
    static HWDimLed store[NB_LED];
};



class CmdParser : public StateM {
  public:
    enum { NO_CHANGE, ERROR, READY, DONE, CMD, PRG_HEAD, PRG_BODY, PRG_END}; // STATES
    CmdParser() {};
    void init(SerialParse * sReader, PulseGen* pulseGen, FreqGen* freqGen, HWDimLed * led1, Programme *prg);
    uint8_t parse(uint8_t state, uint8_t action, uint8_t cycle);
    void newLine();

  private:
    uint8_t loop(uint8_t state, uint8_t action, uint8_t cycle) override ; // actual StateMachine loop method, called from StateM father
    void printID() final;
    void doneWithThisLine();

    uint8_t sCheck(uint8_t, char c);
    char sPeek();
    uint8_t sToken (uint8_t state, char *s, char const *sep);
    uint8_t sLabel (uint8_t state, const char *s, char sep);
    uint8_t sNumber (uint8_t state, float &val , char sep);
    uint8_t sNumber (uint8_t state, uint16_t &val );
    uint8_t sNumber (uint8_t state, uint8_t &val );
    uint8_t SInf (uint8_t state);
    uint8_t SHead(uint8_t state);
    uint8_t SOSC(uint8_t state, Step * step);
    uint8_t SSTR(uint8_t state, Step * step);
    uint8_t SDLY(uint8_t state, Step * step);
    uint8_t SStep(uint8_t state);
    uint8_t SBody(uint8_t state);
    uint8_t SEOL(uint8_t state);
    uint8_t pulseCMD(uint8_t);
    uint8_t ledCMD(uint8_t);
    uint8_t freqCMD(uint8_t);
    uint8_t helpCMD(uint8_t);
    uint8_t processCMD (uint8_t);
    uint8_t prgCMD(uint8_t);
    uint8_t logCMD(uint8_t);

    char token [LABEL_SIZE];
    char * m_lineBuffer; // pointer to the current line buffer
    char * m_cursorPos; // parser position in the current line buffer
    SerialParse * m_textInput;

    FreqGen * m_freqGen;
    PulseGen * m_pulseGen;
    HWDimLed * m_led1;
    Programme *m_prg;
};

class Global {
  public:
    enum modes {MANUAL, AUTO};
    Global() : m_mode(MANUAL) {};
    uint8_t getMode() volatile ;
    void setMode (uint8_t mode) volatile ;
    // Programme prg;

    static Global global;

  private:
    volatile uint8_t m_mode;
};


int freeRam ();
