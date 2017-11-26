#include <TimerOne.h>

#include "mylib.h"

volatile uint16_t cpt1 = 0, cpt2 = 0, cpt3 = 0;
volatile uint16_t interuptCycle = 0;
uint8_t heartBeatLed = 13; //3

HWDimLed *led[NB_LED];

unsigned long time;

// Lamp program, Pandora style
Programme prg;

// Signal generator
#ifdef DEBUG_GEN
HistoPulseGen pulseGen;
#else
PulseGen pulseGen;
PulseGen *pulse[NB_OSC];
#endif

// Frequency generator
FreqGen freqGen;
FreqGen *freq[NB_OSC];

// serial stuff
SerialParse sReader;

// Parser
CmdParser cmdParser;


/*
   Called every ms
*/
void interruptF(void) {

  digitalWrite(23, 1);
  static bool heartBeatLedState = 0;
  static uint16_t currentFreq;
  static uint8_t currentDuty;
  uint8_t mode = Global::global.getMode();
  static bool out23 = false;

  // Call the pulse generator at each interrupt
  switch (mode) {
    case Global::MANUAL:
      pulseGen.tick();
      // Apply pulse generator output to the LED
      if (pulseGen.getPulse() == 0) {
        for (int i = 0; i < NB_LED; i++) led[i]->setState(0);
      }

      else {
        int8_t val = min(255, pulseGen.getPulse());
        for (int i = 0; i < NB_LED; i++) led[i]->setDimedState(1, val);
      }


      break;

    case Global::AUTO:
      for (int i = 0; i < NB_OSC; i++) {
        pulse[i]->tick();
      }
      prg.applyOutputs();
      break;
  }

  // Heartbeat LED each 1 sec
  // Call the program code every second
  if (interuptCycle % (1000000 / interruptPeriod) == 0) {
    digitalWrite (heartBeatLed, heartBeatLedState);
    heartBeatLedState = !heartBeatLedState;
    prg.tick();
  }

  /*
     Debug : high frequency pulse generation is instable due to this 10Hz call that takes a looong time to execute
     We switch from 10Hz to 100Hz, but we do things in steps
  */
  // Call the frequency generator at 10Hz, every 100ms ((1000000/interruptPeriod) / freqPeriodMultiplier) interrupts = 1/freqPeriodMultiplier second
  // freqPeriodMultiplier = 1 -> interrupt applied every cycle
  // freqPeriodMultiplier = 10 -> interrupt applied every 10 cycles
  if (interuptCycle % (1000000 / freqPeriodMultiplier / interruptPeriod / 10)  == 0) {
    FreqGen::icycle = (interuptCycle / 10) % 10;
    switch (mode) {
      case Global::MANUAL:
        // We have kept this part for manual pulse generation (from parser), normally this is no longer used : everything is driven from the Programme object
        if (FreqGen::icycle == 0) freqGen.tick();
        break;
      case Global::AUTO:
        if (FreqGen::icycle < 4) {
          for (int i = 0; i < NB_OSC; i++) {
            freq[i]->tick();
          }
        }
        break;
    }
  }

  interuptCycle++;
  digitalWrite(23, 0);
}

void setup() {
  
  // Assign LEDs to physical output and store pointers
  for (int i = 0; i < NB_LED; i++) {
    led[i] = HWDimLed::getFromStore(i);
  }
  led[0]->setPin(3);
  led[1]->setPin(5);
  led[2]->setPin(6);
  led[3]->setPin(9);
  
  Serial.begin(38400);
  PRINTLN(F("Boot after reset."));

  pinMode(23, OUTPUT);
  digitalWrite(23, 0);
  // Manual generators
  freqGen.init(&pulseGen);

  // Auto generators
  // Store pointers to pulse generators & init
  for (int i = 0; i < NB_OSC; i++) {
    pulse[i] = PulseGen::getFromStore(i);
    freq[i] = FreqGen::getFromStore(i);

    // We teach freq generator about its slave pulse generator
    freq[i]->init(pulse[i]);
  }

  // PWM to 31372 Hz, FAST PWM
  setPwmFrequencyMEGA2560(3, 1);
  setPwmFrequencyMEGA2560(5, 1);
  setPwmFrequencyMEGA2560(6, 1);
  setPwmFrequencyMEGA2560(9, 1);


  prg.init(led, freq);
  prg.clear();
  pinMode(heartBeatLed, OUTPUT);
  digitalWrite(heartBeatLed, 0);

  setupParser();

  Timer1.initialize(interruptPeriod); // Every interruptPeriod x micro
  Timer1.attachInterrupt(interruptF);

  PRINT(F("Free RAM apres setup:"));
  PRINTLN(freeRam());
  PRINTLND(F("Main setup done."));

}

void loop() {
  static uint16_t mainLoopCycle = 0, stepN = 65535;

  mainLoopCycle++;
  /*if (mainLoopCycle % 1000 == 0) {
    Serial.println(cpt1);
    }*/
  if (prg.isRunning() && stepN != prg.getCurrentStepN()) {
    stepN = prg.getCurrentStepN();
    prg.printCurrentStepShort();
  }

  //PRINTLND("Main loop");
  /*
    if (prg.isRunning() && (mainLoopCycle % 200) == 0) {

    // prg.printState();
    for (int i = 0; i < NB_OSC; i++) freq[i]->print();

    if (freeRam() < 500) {
      Serial.println(F("freeRam() = "));
      Serial.print(freeRam());
      Serial.println(F("Switching log off to preserve RAM"));
      Log::log1.off();
    }
    }*/
  loopSerial();
  delay(1);
}


void setupParser() {
  // Parser init. We ask him to store the pointer to serial reader, program object, pulsed and freq objects
  cmdParser.init(&sReader, &pulseGen, &freqGen, led[0], &prg);
  PRINTLND(F("Parser setup done."));
}


// Reads serial
void loopSerial() {
  sReader.readSerial();
  if (sReader.isEOL()) {
    cmdParser.newLine();
    cmdParser.run();
    sReader.clearBuffer();
  }
}


