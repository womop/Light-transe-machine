#include <assert.h>

#include "mylib.h"

// To simplify math and best accuracy need one sample per interrupt cycle per second
/*
   python to generate high1000
      for x in range(0, 1000):
           print str(int(16+16*math.sin(math.pi*x/1000)),)+str(","),
*/
// High 1000 is the half top of sinus above 127 : from 127 to 254 back to 127
byte high1000[]  = {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,};

/*
   python to generate low1000
      for x in range(1000, 2000):
           print str(int(127+127*math.sin(math.pi*x/1000)),)+str(","),
*/



/*
   python to generate low1000
      for x in range(0, 1000):
           print str(int(127+127*math.sin(math.pi*x/1000)),)+str(","),
*/

// Low 1000 is the halve bottom of sinus under 127 : from 127 to 0 back to 127

//byte low1000[] = {127, 126, 126, 125, 125, 125, 124, 124, 123, 123, 123, 122, 122, 121, 121, 121, 120, 120, 119, 119, 119, 118, 118, 117, 117, 117, 116, 116, 115, 115, 115, 114, 114, 113, 113, 113, 112, 112, 111, 111, 111, 110, 110, 109, 109, 109, 108, 108, 107, 107, 107, 106, 106, 105, 105, 105, 104, 104, 103, 103, 103, 102, 102, 102, 101, 101, 100, 100, 100, 99, 99, 98, 98, 98, 97, 97, 96, 96, 96, 95, 95, 95, 94, 94, 93, 93, 93, 92, 92, 91, 91, 91, 90, 90, 90, 89, 89, 88, 88, 88, 87, 87, 86, 86, 86, 85, 85, 85, 84, 84, 83, 83, 83, 82, 82, 82, 81, 81, 80, 80, 80, 79, 79, 79, 78, 78, 78, 77, 77, 76, 76, 76, 75, 75, 75, 74, 74, 74, 73, 73, 72, 72, 72, 71, 71, 71, 70, 70, 70, 69, 69, 68, 68, 68, 67, 67, 67, 66, 66, 66, 65, 65, 65, 64, 64, 64, 63, 63, 63, 62, 62, 62, 61, 61, 60, 60, 60, 59, 59, 59, 58, 58, 58, 57, 57, 57, 56, 56, 56, 55, 55, 55, 54, 54, 54, 53, 53, 53, 52, 52, 52, 52, 51, 51, 51, 50, 50, 50, 49, 49, 49, 48, 48, 48, 47, 47, 47, 46, 46, 46, 46, 45, 45, 45, 44, 44, 44, 43, 43, 43, 43, 42, 42, 42, 41, 41, 41, 40, 40, 40, 40, 39, 39, 39, 38, 38, 38, 38, 37, 37, 37, 36, 36, 36, 36, 35, 35, 35, 34, 34, 34, 34, 33, 33, 33, 33, 32, 32, 32, 32, 31, 31, 31, 30, 30, 30, 30, 29, 29, 29, 29, 28, 28, 28, 28, 27, 27, 27, 27, 26, 26, 26, 26, 25, 25, 25, 25, 24, 24, 24, 24, 24, 23, 23, 23, 23, 22, 22, 22, 22, 21, 21, 21, 21, 21, 20, 20, 20, 20, 19, 19, 19, 19, 19, 18, 18, 18, 18, 18, 17, 17, 17, 17, 17, 16, 16, 16, 16, 16, 15, 15, 15, 15, 15, 14, 14, 14, 14, 14, 14, 13, 13, 13, 13, 13, 12, 12, 12, 12, 12, 12, 11, 11, 11, 11, 11, 11, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 21, 22, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 24, 24, 25, 25, 25, 25, 26, 26, 26, 26, 27, 27, 27, 27, 28, 28, 28, 28, 29, 29, 29, 29, 30, 30, 30, 30, 31, 31, 31, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 34, 35, 35, 35, 36, 36, 36, 36, 37, 37, 37, 38, 38, 38, 38, 39, 39, 39, 40, 40, 40, 40, 41, 41, 41, 42, 42, 42, 43, 43, 43, 43, 44, 44, 44, 45, 45, 45, 46, 46, 46, 46, 47, 47, 47, 48, 48, 48, 49, 49, 49, 50, 50, 50, 51, 51, 51, 52, 52, 52, 52, 53, 53, 53, 54, 54, 54, 55, 55, 55, 56, 56, 56, 57, 57, 57, 58, 58, 58, 59, 59, 59, 60, 60, 60, 61, 61, 62, 62, 62, 63, 63, 63, 64, 64, 64, 65, 65, 65, 66, 66, 66, 67, 67, 67, 68, 68, 68, 69, 69, 70, 70, 70, 71, 71, 71, 72, 72, 72, 73, 73, 74, 74, 74, 75, 75, 75, 76, 76, 76, 77, 77, 78, 78, 78, 79, 79, 79, 80, 80, 80, 81, 81, 82, 82, 82, 83, 83, 83, 84, 84, 85, 85, 85, 86, 86, 86, 87, 87, 88, 88, 88, 89, 89, 90, 90, 90, 91, 91, 91, 92, 92, 93, 93, 93, 94, 94, 95, 95, 95, 96, 96, 96, 97, 97, 98, 98, 98, 99, 99, 100, 100, 100, 101, 101, 102, 102, 102, 103, 103, 103, 104, 104, 105, 105, 105, 106, 106, 107, 107, 107, 108, 108, 109, 109, 109, 110, 110, 111, 111, 111, 112, 112, 113, 113, 113, 114, 114, 115, 115, 115, 116, 116, 117, 117, 117, 118, 118, 119, 119, 119, 120, 120, 121, 121, 121, 122, 122, 123, 123, 123, 124, 124, 125, 125, 125, 126, 126,};


void printFloat(float value, int places) {
  // this is used to cast digits
  int digit;
  float tens = 0.1;
  int tenscount = 0;
  int i;
  float tempfloat = value;

  // make sure we round properly. this could use pow from <math.h>, but doesn't seem worth the import
  // if this rounding step isn't here, the value  54.321 prints as 54.3209

  // calculate rounding term d:   0.5/pow(10,places)
  float d = 0.5;
  if (value < 0)
    d *= -1.0;
  // divide by ten for each decimal place
  for (i = 0; i < places; i++)
    d /= 10.0;
  // this small addition, combined with truncation will round our values properly
  tempfloat +=  d;

  // first get value tens to be the large power of ten less than value
  // tenscount isn't necessary but it would be useful if you wanted to know after this how many chars the number will take

  if (value < 0)
    tempfloat *= -1.0;
  while ((tens * 10.0) <= tempfloat) {
    tens *= 10.0;
    tenscount += 1;
  }


  // write out the negative if needed
  if (value < 0)
    Serial.print('-');

  if (tenscount == 0)
    Serial.print(0, DEC);

  for (i = 0; i < tenscount; i++) {
    digit = (int) (tempfloat / tens);
    Serial.print(digit, DEC);
    tempfloat = tempfloat - ((float)digit * tens);
    tens /= 10.0;
  }

  // if no places after decimal, stop now and return
  if (places <= 0)
    return;

  // otherwise, write the point and continue on
  Serial.print('.');

  // now write out each decimal place by shifting digits one by one into the ones place and writing the truncated value
  for (i = 0; i < places; i++) {
    tempfloat *= 10.0;
    digit = (int) tempfloat;
    Serial.print(digit, DEC);
    // once written, subtract off that digit
    tempfloat = tempfloat - (float) digit;
  }
}

// Tweaked the code to keep clean patterns. We must call analogWrite once at least output before calling fastAnalogWrite
// 2016-09-08 JYL
void fastAnalogWrite(uint8_t pin, uint8_t val)
{
  // JYL : remove the digitalWrite to keep timer running, else we have artifacts.
  /*if (val == 0)
    {
    digitalWrite(pin, LOW);
    }
    else if (val == 255)
    {
    digitalWrite(pin, HIGH);
    }
    else
    {*/
  switch (digitalPinToTimer(pin))
  {
#if defined(TCCR0) && defined(COM00) && !defined(__AVR_ATmega8__)
    // XXX fix needed for atmega8
    case TIMER0A:
      // connect pwm to pin on timer 0
      OCR0 = val; // set pwm duty
      break;
#endif

#if defined(TCCR0A) && defined(COM0A1)
    case TIMER0A:
      OCR0A = val; // set pwm duty
      break;
#endif

#if defined(TCCR0A) && defined(COM0B1)
    case TIMER0B:
      OCR0B = val; // set pwm duty
      break;
#endif

#if defined(TCCR1A) && defined(COM1A1)
    case TIMER1A:
      OCR1A = val; // set pwm duty
      break;
#endif

#if defined(TCCR1A) && defined(COM1B1)
    case TIMER1B:
      OCR1B = val; // set pwm duty
      break;
#endif

#if defined(TCCR1A) && defined(COM1C1)
    case TIMER1C:
      OCR1C = val; // set pwm duty
      break;
#endif

#if defined(TCCR2) && defined(COM21)
    case TIMER2:
      OCR2 = val; // set pwm duty
      break;
#endif

#if defined(TCCR2A) && defined(COM2A1)
    case TIMER2A:
      OCR2A = val; // set pwm duty
      break;
#endif

#if defined(TCCR2A) && defined(COM2B1)
    case TIMER2B:
      OCR2B = val; // set pwm duty
      break;
#endif

#if defined(TCCR3A) && defined(COM3A1)
    case TIMER3A:
      OCR3A = val; // set pwm duty
      break;
#endif

#if defined(TCCR3A) && defined(COM3B1)
    case TIMER3B:
      OCR3B = val; // set pwm duty
      break;
#endif

#if defined(TCCR3A) && defined(COM3C1)
    case TIMER3C:
      OCR3C = val; // set pwm duty
      break;
#endif

#if defined(TCCR4A)
    case TIMER4A:
      OCR4A = val;  // set pwm duty
      break;
#endif

#if defined(TCCR4A) && defined(COM4B1)
    case TIMER4B:
      OCR4B = val; // set pwm duty
      break;
#endif

#if defined(TCCR4A) && defined(COM4C1)
    case TIMER4C:
      OCR4C = val; // set pwm duty
      break;
#endif

#if defined(TCCR4C) && defined(COM4D1)
    case TIMER4D:
      OCR4D = val;  // set pwm duty
      break;
#endif


#if defined(TCCR5A) && defined(COM5A1)
    case TIMER5A:
      OCR5A = val; // set pwm duty
      break;
#endif

#if defined(TCCR5A) && defined(COM5B1)
    case TIMER5B:
      OCR5B = val; // set pwm duty
      break;
#endif

#if defined(TCCR5A) && defined(COM5C1)
    case TIMER5C:
      OCR5C = val; // set pwm duty
      break;
#endif

    case NOT_ON_TIMER:
    default:
      if (val < 128) {
        digitalWrite(pin, LOW);
      } else {
        digitalWrite(pin, HIGH);
      }
  }
}


SerialParse::SerialParse()
  :
  term('\n'),           // default terminator for commands, newline character
  last(NULL),
  EOL(false),
  bufPos(0),
  bufRPos(0)
{
  strcpy(delim, ","); // strtok_r needs a null-terminated string
  clearBuffer();
}

/** JYL
   This checks the Serial stream for characters, and assembles them into a buffer.
   When the terminator character (default '\n') is seen
*/

void SerialParse::readSerial() {
  while (Serial.available() > 0) {
    char inChar = Serial.read();   // Read single available character, there may be more waiting
    if (inChar == term) {     // Check for the terminator (default '\n') meaning end of command
      EOL = true;
#ifdef SerialParse_DEBUG
      Serial.print(F("Serial receives : "));
      Serial.println(buffer);
      return;
#endif
    }
    else if (isprint(inChar)) {     // Only printable characters into the buffer
      if (bufPos < SerialParse_BUFFER) {
        buffer[bufPos++] = inChar;  // Put character into buffer
        buffer[bufPos] = '\0';      // Null terminate
      } else {
#ifdef SerialParse_DEBUG
        Serial.println(F("Line buffer is full - increase SerialParse_BUFFER"));
        return;
#endif
      }
    }
  }
  //  Serial.println(F("Exiting serial due to lack of chars"));
}




/*
   Clear the input buffer.
*/
void SerialParse::clearBuffer() {
  buffer[0] = '\0';
  bufPos = 0;
  EOL = false;
}

char * SerialParse::getBuffer() {
  return buffer;
}

bool SerialParse::isEOL() {
  return EOL;
}

/*
   Begin Programme
   Warning : Pando editor does not repeat OSC or STR data when there is no change between steps
*/

void Programme::init(HWDimLed *led[NB_LED], FreqGen *osc[NB_OSC])  {
  // Set State machine
  StateM::init(OFF);

  for (int i = 0 ; i < NB_LED; i++) {
    m_led[i] = led[i];
  }

  for (int i = 0 ; i < NB_OSC; i++) {
    m_osc[i] = osc[i];
  }


}

void Programme::printID() {
  Serial << F("Programme");
}

void Programme::clear()  {
  setPower(false);
  Step* sample;
  for (int i = 0; i < steps.size(); i++) {
    sample = steps.get(i);
    delete sample;
  }
  steps.clear();
  m_nbSteps = 0;
  m_duration = 0;
  m_currentStepN = 0;
}

void Programme::setNbSteps(uint16_t p) {
  for (int i = 0; i < p; i++) {
    Step * step;
    step = new Step();
    PRINTLND(F("Step creation"));
    steps.add(step);
    /*Serial.print(F("Ram : "));
      Serial.println(freeRam());*/
  }
  m_nbSteps = p;
}

void Programme::setDuration(uint16_t p) {
  m_duration = p;
}

void Programme::setDim(uint8_t dim) {
  m_dim = dim;
}

void Programme::printStep(uint8_t n, Step * step) {
  PRINT(F("step # "));
  PRINT (n + 1);
  PRINT(F(" / duration "));
  PRINT( step->m_duration);
  PRINT(F(" / description : "));
  PRINT( step->description);
  PRINTLN();
  for (int o = 0; o < NB_OSC; o++) {
    step->osc[o].print(o);
  }

  PRINTLN();
}

void Programme::printCurrentStepShort() {
  if (! isRunning()) {
    PRINTLN(F("Stopped"));
    return;
  }
  Step *step;
  step = steps.get(m_currentStepN);

  PRINT(F("step # "));
  PRINT (m_currentStepN + 1);
  PRINT(F(" / duration "));
  PRINT( step->m_duration);
  PRINT(F(" / description : "));
  PRINT( step->description);
  PRINTLN();
}

uint16_t Programme::getCurrentStepN() {
  return m_currentStepN;
}

void Programme::print() {
  Step * step;
  PRINTLN(F("## PROGRAM ##"));
  PRINT(F("duration: "));
  PRINTLN(m_duration);
  PRINT(F("nbSteps (conf/actual): "));
  PRINT(m_nbSteps);
  PRINT(F(" / "));
  PRINTLN(steps.size());

  for (int i = 0; i < steps.size(); i++) {
    step = steps.get(i);
    printStep(i, step);
  }
  PRINTLN(F("## END ##"));
}

void Programme::actionOff2On() {
  LogData mylog {LogData::PROGRAMME_ID, LogData::ON_P, millis(), 0, m_time };
  Log::log1.add(mylog);
  m_currentStepN = 0;
  m_time = 0;
  m_isDone = false;
}

void Programme::actionOn2Off() {
  LogData mylog {LogData::PROGRAMME_ID, LogData::OFF_P, millis(), 0, m_time };
  Log::log1.add(mylog);
  for (int o = 0; o < NB_OSC; o++) m_osc[o]->setPower(false);
  applyOutputs();
}

void Programme::tick()  {
  run();
}

uint8_t Programme::loop(uint8_t state, uint8_t action, uint8_t cycle) {
  // At any time, is we loose power, we switch to OFF

  if (getPower() == false) return OFF;

  dCpt++;
  switch (state) {
    case OFF:
      switch (action) {
        case ENTER:
          break;
        case LOOP:
          // We leave this state when we are powered and not done
          if (isRunning()) return FIRST_CYCLE;
          break;
        case EXIT:
          break;
      }

      break;

    case FIRST_CYCLE:
      switch (action) {
        case ENTER:
          m_currentStepN = 0;
          break;
        case LOOP:
          if (m_nbSteps == 0) return DONE; // No program executed if 0 steps to run
          return RUNNEWSTEP; // else we run the first step
          break;
        case EXIT:

          break;
      }
      break;

    case RUNNEWSTEP:
      switch (action) {
        case ENTER:
          m_debug1++;
          if (m_currentStepN < m_nbSteps) {
            {
              LogData mylog {LogData::PROGRAMME_ID, LogData::NEWSTEP_P, millis(), m_currentStepN, m_time };
              Log::log1.add(mylog);
            }

            if (m_currentStepN >= steps.size()) return SERROR;
            m_timeInStep = 0;
            // Clear and Start the Oscillators
            for (int o = 0; o < NB_OSC; o++) {
              Osc * osc = &(steps.get(m_currentStepN)->osc[o]);
              // m_osc[o]->setPower(false);
              if ((osc->wave > OscWave::OFF) && (osc->wave < OscWave::LAST_WAVE) ) {
                m_osc[o]->setParams(osc->wave, osc->freqStart, osc->freqEnd, osc->dutyStart, osc->dutyEnd, osc->intensity, steps.get(m_currentStepN)->m_duration);
                m_osc[o]->resetCounters();
                m_osc[o]->setPower(true);
              }
            }
          }
          break;
        case LOOP:
          // Cases that trigger immediate programme stop
          if (m_currentStepN >= m_nbSteps || m_time >= m_duration ) return DONE;
          // If we are here, we are going to switch to end of step, but we wan't to exit our state machine and come back at next cycle
          // instead of going into that state right away. This is performed to keep m_time and m_timeInStep accurate
          nextCycle();
          return WAITENDOFSTEP;
          break;
        case EXIT:

          break;
      }
      break;

    case WAITENDOFSTEP:
      switch (action) {
        case ENTER:
          break;
        case LOOP:
          m_timeInStep++;
          m_time++;

          if (m_time >= m_duration) return DONE;
          if (m_timeInStep >= steps.get(m_currentStepN)->m_duration) {
            m_currentStepN++;
            return RUNNEWSTEP;
          }


          break;
        case EXIT:
          {
            LogData mylog {LogData::PROGRAMME_ID, LogData::END_OF_STEP_P, millis(), m_timeInStep, m_time };
            Log::log1.add(mylog);
          }
          break;
      }

      break;

    case DONE:
      switch (action) {
        case ENTER:
          {
            LogData mylog {LogData::PROGRAMME_ID, LogData::DONE_P, millis(), 0, m_time };
            Log::log1.add(mylog);
          }
          m_isDone = true;
          for (int o = 0; o < NB_OSC; o++) m_osc[o]->setPower(false);
          break;
        case LOOP:

          break;
        case EXIT:
          break;
      }
      break;
  }

  // In the cases we did not return anything in the switch
  return NO_CHANGE;
}

void Programme::printState() {
  Step * step;
  PRINT(F("prg : isRunning? , m_currentStepN, m_timeInStep : "));
  PRINT(isRunning());
  PRINT(F(" "));
  PRINT (m_currentStepN);
  PRINT(F(" "));
  PRINTLN (m_timeInStep);
  step = steps.get(m_currentStepN);
  printStep(m_currentStepN, step);
}

/*


   Computes output according to programmed Intensity and pulse generator state
   Requires all 4 pulse generator states (refreshed every 1000 micros) and 16 calculated intensities (refreshed every 100ms) to be able to compute the results

   This computation works only when NB_OSC = NB_LED, it must be adapted for other cases
   getIntensity() return 0->100 but here we want 0->255 (PWM requirement), also we know that the sum of intensities on one LED shall not be more than
   100% (requirement of programme builder). We do not check this requirement here, it is check upon program load : TODO
*/

void Programme::applyOutputs() {
  uint8_t pulse[NB_LED];
  uint16_t intensity[NB_LED] {0, 0, 0, 0};

  assert (NB_OSC == NB_LED) ;

  // retreive pulse state of oscillators
  for (int i = 0; i < NB_OSC; i++) {
    if (m_osc[i]) pulse[i] = m_osc[i]->getPulse();
    else return;
  }

  // compute intensity for each LED
  for (int led = 0; led < NB_LED; led++) {
    intensity[led] = 0;
    for (int osc = 0; osc < NB_OSC; osc++) {
      intensity[led] += pulse[osc] * m_osc[osc]->getIntensity(led) / 100;
    }

    // Here intensity is 0->32, we need to multiply by dim (1->8) to go 5->255
    if (intensity[led] != 0) intensity[led] = min(255, max(MIN_POWER, intensity[led] * m_dim ));

  }


  for (int i = 0; i < NB_LED; i++) {
    if (m_led[i]) {
        m_led[i]->setDimedState(1, intensity[i]);     
    }
    else return;
  }
}

/*
   End Programme
*/



void LEDdata::print(uint8_t l) {
  PRINT (F("LEDdata# "));
  PRINT (l);
  PRINT (F(" start intensity: "));
  PRINT (start);
  PRINT (F(", end intensity: "));
  PRINTLN (end);
}

void Osc::print(uint8_t l) {
  PRINT (F("Oscillator# "));
  PRINT (l);
  PRINT (F(" wave: "));
  PRINT (wave);
  PRINT (F(", freq start (/100): "));
  PRINT (freqStart);
  PRINT (F(", freq end (/100): "));
  PRINT (freqEnd);
  PRINT (F(", duty start: "));
  PRINT (dutyStart);
  PRINT (F(", duty end: "));
  PRINT (dutyEnd);
  PRINTLN();

  PRINT (F("Intensity: "));
  PRINTLN (l);
  for (int i = 0; i < NB_LED; i++) {
    intensity[i].print(i);
  }
  PRINTLN();
}

void PulseGen::resetCounters() {
  m_time = 0;
  m_cycle = 0;
  m_pulse = 0;
  m_nextHighTime = 0;
  m_lastHighTime = 0;

  m_nextLowTime = -1; // highest unsigned value to make sure this does not happen too soon for the first cycle. It should not anyway is the algo is right
  m_lastLowTime = -1;

  m_inTransition = false;
}

// seters and actions

void PulseGen::actionOff2On() {
  LogData mylog {LogData::PULSE_ID, LogData::ON_PU, millis(), 0, m_time };
  Log::log1.add(mylog);
  resetCounters();
}

void PulseGen::actionOn2Off() {
  LogData mylog {LogData::PULSE_ID, LogData::OFF_PU, millis(), 0, m_time };
  Log::log1.add(mylog);
  m_pulse = 0;
}
// Complex method because it allows frequency and duty change during run.

void PulseGen::setParams(uint16_t freq, uint8_t duty, uint8_t wave)  {
  m_wave = wave; // we can alter generator type whithout changing its internal math computation. only the getPulse retrieval method is impacted

  if (m_freq != freq || m_duty != duty) {
    { LogData mylog {LogData::PULSE_ID, LogData::SETPARAMS_PU, millis(), freq, m_time };
      Log::log1.add(mylog);
      mylog.value = duty;
      Log::log1.add(mylog);
    }
    uint8_t myCase = 0;
    // Carefull when we change frequency or duty. If pulse is high, we calculate next low, if pulse is low, we calculate next high. This
    // is meant for smooth frequency transitions

    m_freq = freq;
    m_duty = duty;

    // m_cycle = 0;

    // If we are already running, we have a lot to do
    if (m_isOn) {
      m_inTransition = true; // this will be used by the generator to reset counters
      // we compute new cycle, high and low length
      uint32_t  cycleLength; // in nb of interrupts or "cycles"
      cycleLength = (1000000ul * FREQ_DIVISOR / (interruptPeriod)) / m_freq ;
      m_highLength = cycleLength * m_duty / 100; // 100 is a percentage
      m_lowLength = cycleLength - m_highLength;

      // Now we "insert" our new frequency properly into the old one, so that it blends without creating high transient frequency, or any delay
      if (m_pulse == 0) {
        // we must let current pulse last the correct length according to new frequency
        // If we need to make current pulse longer (high freq to low freq), this math takes care of it
        m_nextHighTime = m_lastLowTime + m_lowLength;
        // But if we need to make it shorter, we shall switch immediately
        if (m_time > m_nextHighTime) {
          m_nextHighTime = m_time;
          myCase = 1;
          { LogData mylog {LogData::PULSE_ID, LogData::BLEND_LOW_IMMEDIATE_PU, millis(), m_nextHighTime, m_time };
            Log::log1.add(mylog);
          }
        }
        else {
          { LogData mylog {LogData::PULSE_ID, LogData::BLEND_LOW_DELAYED_PU, millis(), m_nextHighTime, m_time };
            Log::log1.add(mylog);
          }
          myCase = 2;
        }
      }
      // same job if we are currently on the high pulse
      else {
        m_nextLowTime = m_lastHighTime + m_highLength;
        if (m_time > m_nextLowTime) {
          m_nextLowTime = m_time;
          myCase = 3;
          { LogData mylog {LogData::PULSE_ID, LogData::BLEND_HIGH_IMMEDIATE_PU, millis(), m_nextLowTime, m_time };
            Log::log1.add(mylog);
          }
        }
        else {
          { LogData mylog {LogData::PULSE_ID, LogData::BLEND_HIGH_DELAYED_PU, millis(), m_nextLowTime, m_time };
            Log::log1.add(mylog);
          }
          myCase = 4;
        }
        m_nextHighTime = m_nextLowTime + m_lowLength; // required because nextHigh is computer by tick() only on 0->1 transition,if we don't do this we use current next HighTime instead of new one
      }
#ifdef DEBUG_GEN
      FreqTimeStamp * tmp = new FreqTimeStamp(micros(), cycleLength, highLength, lowLength, m_pulse, m_nextHighTime, m_nextLowTime, myCase );
      m_freqTimeStamp.add(tmp);
#endif
      /*  */
    }
  }
}


void PulseGen::tick()   {
  if (m_isOn) {
    // 0 -> 1 transition
    if (m_pulse == 0) {
      if (m_time >= m_nextHighTime) {
        if (m_inTransition) resetCounters();
        m_lastHighTime = m_nextHighTime; // backup old value

        m_nextHighTime = (1000000ul * FREQ_DIVISOR / (interruptPeriod)) * (m_cycle + 1) / m_freq ;
        m_nextLowTime = (m_lastHighTime + ((m_nextHighTime - m_lastHighTime) * m_duty / 100)); // 100 is percentage

        m_pulse = 1;
        m_cycle++;
      }
    }
    else {
      // 1 -> 0 transition
      if (m_time >= m_nextLowTime) {
        m_lastLowTime = m_nextLowTime; // backup old value
        m_pulse = 0;
      }
    }
    m_time++;
  }
}

// geters


uint16_t PulseGen::getFreq() {
  return m_freq;
}

uint8_t PulseGen::getDuty() {
  return m_duty;
}

/*
   We transform high pulse into a half top sine wave (over 127)
   low pulse is transformed into a half bottom sine wave (under 127)
   This enables us to have sinus AND duty settings working together
*/
uint8_t PulseGen::ourSinus() {
  uint8_t sine;
  if (m_pulse) {
    sine = high1000 [min(999l, (m_time - m_lastHighTime) * 999l / (m_nextLowTime - m_lastHighTime))];
    return sine;
  }
  else {
    sine = high1000 [min(999l, (m_time - m_lastLowTime) * 999l / (m_nextHighTime - m_lastLowTime))];
    return 32 - sine;
  }
}

uint8_t PulseGen::getPulse()  {
  if (m_isOn) {
    switch (m_wave) {
      case OFF: return 0;
      case SQUARE : return 32 * m_pulse;
      case SINE : return ourSinus();
    }
  }
  else
    return 0;
}

void PulseGen::print() {
  uint32_t cycle;
  uint32_t time ;
  uint32_t nextHighTime, nextLowTime;
  uint16_t lgenStep ;
  bool isOn ;
  uint16_t freq;
  uint8_t duty, wave;
  bool pulse ;
  NOINT();
  isOn = m_isOn;
  time = m_time;
  cycle = m_cycle;
  nextHighTime = m_nextHighTime;
  nextLowTime = m_nextLowTime;
  freq = m_freq ;
  duty = m_duty;
  pulse = m_pulse;
  wave = m_wave;
  INT();
  PRINT (F("isOn time cycle nextHigh nextLow freq duty wave pulse : "));
  PRINT(isOn); PRINT(F(" "));
  PRINT(time); PRINT(F(" "));
  PRINT(cycle); PRINT(F(" "));
  PRINT(nextHighTime); PRINT(F(" "));
  PRINT(nextLowTime); PRINT(F(" "));
  PRINT(freq); PRINT(F(" "));
  PRINT(duty); PRINT(F(" "));
  PRINT(wave); PRINT(F(" "));
  PRINTLN(pulse);
  PRINT(F("cycleLength, highLength, lowLength : "));
  uint32_t highLength, lowLength, cycleLength;
  cycleLength = (1000000ul * FREQ_DIVISOR / (interruptPeriod)) / m_freq ;
  highLength = cycleLength * m_duty / 100; // 100 is percentage
  lowLength = cycleLength - highLength;
  PRINT (cycleLength); PRINT(F(" "));
  PRINT (highLength); PRINT(F(" "));
  PRINT (lowLength); PRINTLN(F(" "));

  PRINT(F("histo Freq begin, size : "));
  PRINTLN (m_freqTimeStamp.size());
  PRINTLN(F("m_sysTime;m_cycleLength;m_highLength;m_lowLength;m_pulse;m_nextHighTime;m_nextLowTime;m_case"));
  FreqTimeStamp* sample;
  for (int i = 0; i < m_freqTimeStamp.size(); i++) {
    sample = m_freqTimeStamp.get(i);
    sample->print();
    delete sample;
  }
  m_freqTimeStamp.clear();
  PRINTLN(F("histo Freq end"));
}

PulseGen *PulseGen::getFromStore(uint8_t n) {
  if (n < NB_OSC) {
    return & store[n];
  }
  else
    return 0;
}

PulseGen PulseGen::store[NB_OSC];
//
// End PulseGen
//

//
// Begin PulseTimeStamp & HistoPulseGen
//

void PulseTimeStamp::print() {
  PRINT(m_sysTime);
  PRINT(F(";"));
  PRINT(m_pulse);
  PRINT(F(";"));
  PRINTLN(m_inTransition);
}

// Print cuurent state + histo, then clear histo
void HistoPulseGen::print() {
  PulseTimeStamp* sample;
  PulseGen::print();
  PRINT(F("histo begin, size : "));
  PRINTLN (pulseTimeStamps.size());
  for (int i = 0; i < pulseTimeStamps.size(); i++) {
    sample = pulseTimeStamps.get(i);
    sample->print();
    delete sample;
  }
  pulseTimeStamps.clear();
  PRINTLN(F("histo end"));
}

// We store the pulse into memory after tick()
void HistoPulseGen::tick()  {
  m_sysTime = micros();
  m_inTransition = PulseGen::m_inTransition;
  PulseGen::tick();
  // Did the pulse change state ?
  if (m_lastPulse != m_pulse) {
    PulseTimeStamp * tmp = new PulseTimeStamp(m_sysTime, m_pulse, m_inTransition );
    pulseTimeStamps.add(tmp);
    m_lastPulse = m_pulse;
  }
}



//
// End PulseTimeStamp & HistoPulseGen
//

// Begin Freq Generator

void FreqTimeStamp::print() {
  PRINT(m_sysTime); PRINT(F(";"));
  PRINT(m_cycleLength); PRINT(F(";"));
  PRINT(m_highLength); PRINT(F(";"));
  PRINT(m_lowLength); PRINT(F(";"));
  PRINT(m_pulse); PRINT(F(";"));
  PRINT(m_nextHighTime); PRINT(F(";"));
  PRINT(m_nextLowTime); PRINT(F(";"));
  PRINT(m_case);
  PRINTLN();
}

void FreqGen::init (PulseGen * pulseGen) {
  m_pulseGen = pulseGen;
}

void FreqGen::resetCounters() {
  m_time = 0;
  m_isDone = false;
}



void FreqGen::actionOff2On() {
  LogData mylog {LogData::FREQ_ID, LogData::ON_O, millis(), 0, m_time };
  Log::log1.add(mylog);
  resetCounters();
}

void FreqGen::actionOn2Off() {
  LogData mylog {LogData::FREQ_ID, LogData::OFF_O, millis(), 0, m_time };
  Log::log1.add(mylog);
  m_pulseGen->setPower(false);
}

uint8_t FreqGen::getIntensity(uint8_t ledN) {
  return m_currentIntensity[ledN];
}

bool FreqGen::setParams(uint8_t wave, uint16_t freqStart, uint16_t freqEnd, uint8_t dutyStart, uint8_t dutyEnd, LEDdata intensity[], uint16_t stepDuration) {
  LogData mylog {LogData::FREQ_ID, LogData::SETPARAMS_O, millis(), m_isOn, m_time };
  Log::log1.add(mylog);

  // We don't alter a running generator
  // if (m_isOn) return false;

  // Here, we know generator is not running
  // NOINT();
  m_freqStart = freqStart;
  m_freqEnd = freqEnd;
  m_dutyStart = dutyStart;
  m_dutyEnd = dutyEnd;
  m_wave = wave;
  if (stepDuration == 0) stepDuration = 1; // no 0 second step allowed
  m_duration = stepDuration;
  for (int i = 0; i < NB_LED; i++) m_intensity[i] = intensity[i];

  // INT();
  return true;
}

void FreqGen::print() {
  PRINTLN(F("printFrequency : m_isOn m_isDone m_time m_wave m_currentFreq m_currentDuty m_freqStart m_freqEnd m_dutyStart m_dutyEnd m_duration m_intensity[4]"));
  PRINT (m_isOn); PRINT(F(" "));
  PRINT (m_isDone); PRINT(F(" "));
  PRINT (m_time); PRINT(F(" "));
  PRINT (m_wave); PRINT(F(" "));
  PRINT (m_currentFreq); PRINT(F(" "));
  PRINT (m_currentDuty); PRINT(F(" "));
  PRINT (m_freqStart); PRINT(F(" "));
  PRINT (m_freqEnd); PRINT(F(" "));
  PRINT (m_dutyStart); PRINT(F(" "));
  PRINT (m_dutyEnd); PRINT(F(" "));
  PRINT (m_duration); PRINT(F("#"));
  for (int i = 0; i < NB_LED; i++) {
    PRINT (m_currentIntensity[i]); PRINT(F("/"));
  }
  PRINTLN(F("#"));

}

// Actual frequency, duty and intensity generator, is called by the signalGenerator every 0.1 second
// choice is made to avoid signed stuff
void FreqGen::tick() {
  if (m_isOn && !m_isDone) {
    // We calculate frequency based on : frequency = a.time + b
    // where a = (m_freqEnd - m_freqStart) / stepDuration
    // and b = m_freqStart
    // m_time in seconds
    // m_duration in seconds

    // Normal case : duration more than 1 second
    if (m_duration > 1) {
      switch (icycle) {
        case 0:
          if (m_freqEnd > m_freqStart)
            m_currentFreq = (m_freqEnd - m_freqStart) * m_time / (m_duration  * freqPeriodMultiplier) + m_freqStart;
          else
            m_currentFreq = m_freqStart - (m_freqStart - m_freqEnd) * m_time / (m_duration  * freqPeriodMultiplier);
          break;

        case 1:
          // Same job for duty math
          if (m_dutyEnd > m_dutyStart)
            m_currentDuty = (m_dutyEnd - m_dutyStart) * m_time / (m_duration  * freqPeriodMultiplier) + m_dutyStart;
          else
            m_currentDuty = m_dutyStart - (m_dutyStart - m_dutyEnd) * m_time / (m_duration  * freqPeriodMultiplier);
          break;

        case 2:
          // Same job for instensity
          for (int i = 0; i < NB_LED; i++) {
            if (m_intensity[i].end > m_intensity[i].start)
              m_tmpIntensity[i] = (m_intensity[i].end - m_intensity[i].start) * m_time / (m_duration  * freqPeriodMultiplier) +  m_intensity[i].start;
            else
              m_tmpIntensity[i] = m_intensity[i].start - (m_intensity[i].start - m_intensity[i].end) * m_time / (m_duration  * freqPeriodMultiplier);
          }
          break;
      }
    }

    // If duration is 1 sec, we apply mid frequency and mid duty during 1 sec.
    else {
      switch (icycle) {
        case 0:
          if (m_freqStart > m_freqEnd) {
            m_currentFreq = (m_freqStart - m_freqEnd) / 2;
          }
          else {
            m_currentFreq = (m_freqEnd - m_freqStart) / 2;
          }
          break;

        case 1:
          if (m_dutyStart > m_dutyEnd) {
            m_currentDuty = (m_dutyStart - m_dutyEnd) / 2;
          }
          else {
            m_currentDuty = (m_dutyEnd - m_dutyStart) / 2;
          }
          break;

        case 2:
          for (int i = 0; i < NB_LED; i++) {
            if (m_intensity[i].start > m_intensity[i].end)
              m_tmpIntensity[i] = (m_intensity[i].start - m_intensity[i].end ) / 2;
            else
              m_tmpIntensity[i] = (m_intensity[i].end - m_intensity[i].start ) / 2;
          }
          break;
      }
    }

    if (icycle == 3) {
      // Stop whenever last step is hit
      if (m_time++ >  (m_duration * freqPeriodMultiplier)) {
        m_isDone = true;
        LogData mylog {LogData::FREQ_ID, LogData::DONE_O, millis(), m_duration * freqPeriodMultiplier, m_time };
        Log::log1.add(mylog);
        m_pulseGen->setPower(false);
      }
      else {
        // Normal case : we teach pulse gen with calculated freq, duty. Intensity values are kept in the freq Gen, will be used when we apply Outputs.
        m_pulseGen->setParams(m_currentFreq, m_currentDuty, m_wave);
        for (int i = 0; i < NB_LED; i++) m_currentIntensity[i] = m_tmpIntensity[i];
        m_pulseGen->setPower(true);
      }
    }
  }
}

bool FreqGen::getCalcValues(uint16_t &currentFreq, uint8_t &currentDuty ) {
  currentFreq = m_currentFreq;
  currentDuty = m_currentDuty;
  return isRunning();
}


uint8_t FreqGen::getPulse() {
  return m_pulseGen->getPulse();
}

FreqGen* FreqGen::getFromStore(uint8_t n) {
  if (n < NB_OSC ) {
    return & store[n];
  }
  else
    return 0;
}

FreqGen FreqGen::store[NB_OSC];
volatile uint8_t FreqGen::icycle;

// End Freq Generator

//
// Begin HWDimLed
//

void HWDimLed::setState(bool state) {
  if (state != m_state) {
    m_state = state;
    if (m_state == 1) {
      fastAnalogWrite(m_hwoutput, max(MIN_POWER, m_dim));
    }
    else {
      fastAnalogWrite(m_hwoutput, 0);
    }
  }
}
void HWDimLed::setDim (uint8_t dim) {
  if (dim != m_dim) {
    m_dim = dim;
    if (m_state == 1) {
      fastAnalogWrite(m_hwoutput, max(MIN_POWER, m_dim));
    }
  }
}



void HWDimLed::setDimedState(bool state, uint8_t dim ) {
  if (state != m_state || dim != m_dim) {
    m_state = state;
    m_dim = dim;
    if (m_state == 1)
      fastAnalogWrite(m_hwoutput, dim);
    else
      fastAnalogWrite(m_hwoutput, 0);
  }
}

void HWDimLed::setPin(uint8_t pin) {
  m_hwoutput = pin;
  digitalWrite(pin,0);
  pinMode(pin, OUTPUT);
  // Required to enable Arduino PWM
  analogWrite(pin, 10);
  // and back to off
  fastAnalogWrite(pin, 0);

}

HWDimLed *HWDimLed::getFromStore(uint8_t n) {
  if (n < NB_LED) {
    return & store[n];
  }
  else
    return 0;
}

HWDimLed HWDimLed::store[NB_LED];
//
// End HWDimLed
//

//
// Begin parser
//

uint8_t CmdParser::sCheck(uint8_t state, char c) {
  PRINTD(F("sCheck ("));
  PRINTD(c);
  PRINTD(F(") : "));

  if (*m_cursorPos++ == c) {
    PRINTLND(F(" found"));
    return state;
  }
  else PRINTLND(F(" missing"));

  return ERROR;
}

// returns next char without moving the cursor. Usefull to make a decision without "eating" a char
char CmdParser::sPeek() {
  return *m_cursorPos;
}

// wait for a any label followed by a separator (char *), returns the label found
uint8_t CmdParser::sToken (uint8_t state, char *s, char const * sep) {
  uint16_t len;
  PRINTD(F("sToken ("));
  PRINTD(s);
  PRINTD(F(" , "));
  PRINTD(sep);
  PRINTD(F(") : "));
  // Search for the separator
  len = strcspn(m_cursorPos, sep);
  // Then copy from cursor to the separator
  // If the token found is too big -> drop excess
  // if (len >= LABEL_SIZE) return ERROR;
  strncpy (s, m_cursorPos, min(len, LABEL_SIZE - 1));
  // Add the 0 terminator char
  s[min(len, LABEL_SIZE - 1)] = '\0';

  // We align the cursor, it depends if we have found the delimiter or not
  if (len >= strlen(m_cursorPos)) {
    // No delimiter found
    m_cursorPos = m_cursorPos + len;
  }
  else {
    // We align the cursor, including the separator, hence the +1
    m_cursorPos = m_cursorPos + len + 1;
  }
  PRINTD (F("token found : "));
  PRINTLND (s);
  return state;
}

// wait for a given label followed by a separator
uint8_t CmdParser::sLabel (uint8_t state, const char *s, char sep) {
  uint16_t tmp;
  PRINTD(F("sLabel ("));
  PRINTD(s);
  PRINTD(F(" , "));
  PRINTD(sep);
  PRINTD(F(") : "));

  tmp = strncmp(s, m_cursorPos, strlen(s));

  if (tmp != 0) {
    PRINTLND(F(" not found"));
    return ERROR;
  }
  PRINTLND (F(" found"));
  // We align the cursor
  m_cursorPos += strlen(s);

  // And check for separator
  return (sCheck(state, sep));
}

// wait for a float followed by a separator, will return positive integer value in parameter (16 bits)
uint8_t CmdParser::sNumber (uint8_t state, float & val , char sep) {
  char * newCursor;

  PRINTD(F("sNumber ( &val ,"));
  PRINTD(sep);
  PRINTD(F(") : "));

  PRINTD (F("number "));
  val = strtod (m_cursorPos, &newCursor);

  if (m_cursorPos == newCursor) {
    PRINTLN(F(" not found"));
    return ERROR;
  }
  PRINTD (F(" found  :"));
  PRINTLNFD (val);
  // We align the cursor
  m_cursorPos = newCursor;

  // And check for separator
  return (sCheck(state, sep));
}

// wait for a positive integer, will return positive integer value in parameter (16 bits)
uint8_t CmdParser::sNumber (uint8_t state, uint16_t &val ) {
  char * newCursor;

  PRINTD(F("sNumber ( &val ) : "));

  PRINTD (F("number "));
  val = strtol (m_cursorPos, &newCursor, 10);

  if (m_cursorPos == newCursor) {
    PRINTLND(F(" not found"));
    return ERROR;
  }
  PRINTD (F(" found  :"));
  PRINTLND (val);
  // We align the cursor
  m_cursorPos = newCursor;

  return state;
}

// wait for a positive integer, will return positive integer value in parameter (8 bits)
uint8_t CmdParser::sNumber (uint8_t state, uint8_t &val ) {
  char * newCursor;

  PRINTD(F("sNumber ( &val ) : "));

  PRINTD (F("number "));
  val = strtol (m_cursorPos, &newCursor, 10);

  if (m_cursorPos == newCursor) {
    PRINTLND(F(" not found"));
    return ERROR;
  }
  PRINTD (F(" found  :"));
  PRINTLND (val);
  // We align the cursor
  m_cursorPos = newCursor;

  return state;
}

uint8_t CmdParser::SInf (uint8_t state) {
  PRINTD(F("SInf () : "));
  return sCheck(state, '<');
}

uint8_t CmdParser::SHead(uint8_t state) {
  if (state != PRG_HEAD) return state;

  uint16_t ret;

  // Wait for '<'
  CHECK(SInf(state));
  CHECK(sLabel(state, "STC", ','));
  CHECK(sNumber(state, ret));
  CHECK(sCheck(state, ','));
  m_prg->setNbSteps(ret);
  CHECK(sNumber(state, ret));
  CHECK(sCheck(state, '>'));
  m_prg->setDuration(ret);

  return PRG_BODY;
}

uint8_t CmdParser::SOSC(uint8_t state, Step * step) {
  uint16_t osc, wave, ds, de;
  float fs, fe;
  // First is Oscillator number
  CHECK(sNumber(state, osc));
  CHECK(sCheck(state, ','));
  if (osc > NB_OSC || osc < 1) {
    PRINTLN(F("SStep () : invalid oscillator"));
    return ERROR;
  }

  CHECK(sNumber(state, wave));
  CHECK(sCheck(state, ','));
  if (wave >= LAST_WAVE) {
    PRINTLN(F("SStep () : invalid wave"));
    return ERROR;
  }


  CHECK(sNumber(state, fs, ','));
  CHECK(sNumber(state, fe, ','));
  CHECK(sNumber(state, ds));
  CHECK(sCheck(state, ','));
  if (ds > MAX_DUTY) {
    PRINTLN(F("SStep () : duty start too high, we set it to MAX and do not fail"));
    ds = MAX_DUTY;
  }
  if (ds < MIN_DUTY) {
    PRINTLN(F("SStep () : duty start too low, we set it to MIN and do not fail"));
    ds = MIN_DUTY;
  }
  CHECK(sNumber(state, de));
  CHECK(sCheck(state, '>'));
  if (de > MAX_DUTY) {
    PRINTLN(F("SStep () : duty end too high, we set it to MAX and do not fail "));
    de = MAX_DUTY;
  }
  if (de < MIN_DUTY) {
    PRINTLN(F("SStep () : duty end too low, we set it to MIN and do not fail"));
    de = MIN_DUTY;
  }
  PRINTLND(F("SOSC() : done"));
  osc--;
  step->osc[osc].wave = wave;
  step->osc[osc].freqStart = min(max(MIN_F, fs * FREQ_DIVISOR), MAX_F);
  step->osc[osc].freqEnd = min(max(MIN_F, fe * FREQ_DIVISOR), MAX_F);
  step->osc[osc].dutyStart = ds;
  step->osc[osc].dutyEnd = de;

  return state;
}

uint8_t CmdParser::SSTR(uint8_t state, Step * step) {
  uint16_t ledN, wave;
  uint16_t start, end;

  float fs, fe;
  // First is LED number
  CHECK(sNumber(state, ledN));
  if (ledN > NB_LED || ledN < 1) {
    PRINTLND(F("SStep () : invalid led"));
    return ERROR;
  }
  // ledN in text file is 1 to NB_LED, here we need 0 to NB_LED-1
  ledN--;

  // then 4 x start
  for (int oscN = 0 ; oscN < NB_OSC; oscN++ ) {
    CHECK(sCheck(state, ','));
    CHECK(sNumber(state, start));
    if (start > 100) {
      PRINTLND(F("SStep () : invalid start %%"));
      return ERROR;
    }
    step->osc[oscN].intensity[ledN].start = start;
  }

  //  then 4 x end values
  for (int oscN = 0 ; oscN < NB_OSC; oscN++ ) {
    CHECK(sCheck(state, ','));
    CHECK(sNumber(state, end));
    if (end > 100) {
      PRINTLND(F("SStep () : invalid end %%"));
      return ERROR;
    }
    step->osc[oscN].intensity[ledN].end = end;
  }

  CHECK(sCheck(state, '>'));
  return state;
}

uint8_t CmdParser::SDLY(uint8_t state, Step * step) {
  uint16_t duration;
  CHECK(sNumber(state, duration));
  step->m_duration = duration;
  CHECK(sCheck(state, '>'));
  return state;
}

/*
   Waring : since Pando program generator does not repeat unchanged stuff between 2 steps, we must copy previous step values before we populate the new one
*/
uint8_t CmdParser::SStep(uint8_t state) {
  PRINTLND(F("SStep () : "));
  uint16_t stepNb, stepDuration;
  Step * step, *oldStep;

  CHECK(sNumber(state, stepNb));
  stepNb--;
  CHECK (sCheck(state, ','));

  // TODO : Add check that we do not have extra steps not configured : check that sNumber < m_prg->size()
  // we retrieve pre-created step, we will populate it.
  step = m_prg->steps.get(stepNb);

  // For all but 1st step, we must copy previous step data, due to Pando generator optimization
  if (stepNb > 0) {
    oldStep = m_prg->steps.get(stepNb - 1);
    *step = *oldStep;
  }

  CHECK(sNumber(state, stepDuration));
  CHECK (sCheck(state, ','));
  step->m_duration = stepDuration;
  //PRINTD(F("step->duration="));
  //PRINTLND(step->duration);
  CHECK(sToken(state, token, ">"));
  strcpy(step->description, token);

  // Here, we either have End of Line or ':' followed by <OSC or <STR
  for (;;) {
    if (SEOL(state) == state) {
      // If EOL, we get out of this loop
      break;
    }
    CHECK(sCheck(state, ':'));
    CHECK(SInf(state));
    CHECK(sToken(state, token, ","));
    if (strcmp (token, "OSC") == 0) {
      CHECK(SOSC(state, step));
      continue;
    }
    if (strcmp (token, "STR") == 0) {
      CHECK(SSTR(state, step));
      continue;
    }
    if (strcmp (token, "DLY") == 0) {
      CHECK(SDLY(state, step));
      continue;
    }
    // If we are here, token is unknown, we accept that and ignore any info until the next '>'
    CHECK(sToken(state, token, ">"));
    continue;
  }
  // Job is done
  PRINTLND(F("SStep () : done"));
  return state;

}

uint8_t CmdParser::SBody(uint8_t state) {
  if (state != PRG_BODY) return state;
  // Body is a sequence of lines starting with '<STP,...' the last line is <END,#>
  while (true) {
    CHECK(SInf(state));

    CHECK(sToken(state, token, ","));

    // End case
    if (strcmp (token, "END") == 0) {
      CHECK(sLabel(state, "#", '>'));
      return PRG_END;
    }

    // Step case
    if (strcmp (token, "STP") == 0) {
      CHECK(SStep(state));
      // If we are here, we have reached an EOL
      return PRG_BODY; // continue to next line
    }
    // If we are here, the line is starting with an unknown label XYZ like this <XYZ,
    return ERROR;
  }
}

void CmdParser::doneWithThisLine() {
  m_textInput->clearBuffer();
}

void CmdParser::newLine() {
  // Wait for a new line in the buffer
  m_cursorPos = m_lineBuffer;
}

uint8_t CmdParser::SEOL(uint8_t state) {
  if (*m_cursorPos != '\0') {
    return ERROR;
  }
  return state;
}





// Process plan commands
// gen : signal generator
// freq : frequency generator
// void startFreqency(float freqStart, float freqEnd, uint8_t dutyStart, uint8_t dutyEnd) {


uint8_t CmdParser::pulseCMD(uint8_t state) {
  if (sPeek() == '\0') {
    CHECK(SEOL(state));
    PRINTLN(F(" pulse on FREQ DUTY WAVE \n pulse off \n pulse print"));
    return DONE;
  }
  else {
    uint8_t wave;
    uint16_t freq, duty;
    CHECK(sToken(state, token, " "));
    if (strcmp(token, "on") == 0) {
      CHECK( sNumber(state, freq));
      CHECK( sCheck(state, ' '));
      CHECK( sNumber(state, duty));
      CHECK( sCheck(state, ' '));
      CHECK( sNumber(state, wave));

      CHECK( SEOL(state));
      NOINT();
      m_pulseGen->setParams(freq, duty, wave);
      m_pulseGen->setPower(true);
      INT();
      return DONE;
    }
    if (strcmp(token, "off") == 0) {
      m_pulseGen->setPower(false);
      return DONE;
    }
    if (strcmp(token, "print") == 0) {
      m_pulseGen->print();
      return DONE;
    }
  }
  // If we are here, command is incorrect
  return ERROR;
}

uint8_t CmdParser::ledCMD(uint8_t state) {
  if (sPeek() == '\0') {
    CHECK(SEOL(state));
    PRINTLN(F(" led power N (N is power from 1 to 255) \n led pwm N (N is 1 to 6)"));

    return DONE;
  }
  else {
    uint8_t power, mode;
    CHECK(sToken(state, token, " "));
    if (strcmp(token, "power") == 0) {
      CHECK( sNumber(state, power));
      CHECK( SEOL(state));
      m_led1->setDim(max(1, min(8, power)));
      m_prg->setDim(max(1, min(8, power)));
      return DONE;
    }
    if (strcmp(token, "pwm") == 0) {
      CHECK( sNumber(state, mode));
      CHECK( SEOL(state));
      setPwmFrequencyMEGA2560(3, mode);
      setPwmFrequencyMEGA2560(5, mode);
      setPwmFrequencyMEGA2560(6, mode);
      setPwmFrequencyMEGA2560(9, mode);
      return DONE;
    }
  }
  // If we are here, command is incorrect
  return ERROR;
}

// void startFreqency(uint16_t fStart, uint16_t fEnd, uint8_t dStart, uint8_t dEnd, uint16_t stepDuration)

// Frequency generator CLI parser

uint8_t CmdParser::freqCMD(uint8_t state) {
  if (sPeek() == '\0') {
    PRINTLN(F(" freq on WAVE FSTART FEND DUTYSTART DUTYEND TIME \n freq off \n freq print"));
    return DONE;
  }
  else {
    uint16_t fStart, fEnd;
    uint8_t dStart, dEnd, wave;
    uint16_t stepDuration;
    LEDdata intensity [NB_LED];
    for (int i = 0; i < NB_LED; i++) {
      intensity[i].start = 10;
      intensity[i].end = 10;
    }

    CHECK(sToken(state, token, " "));
    if (strcmp(token, "on") == 0) {
      CHECK( sNumber(state, wave));
      CHECK( sCheck(state, ' '));
      CHECK( sNumber(state, fStart));
      CHECK( sCheck(state, ' '));
      CHECK( sNumber(state, fEnd));
      CHECK( sCheck(state, ' '));
      CHECK( sNumber(state, dStart));
      CHECK( sCheck(state, ' '));
      CHECK( sNumber(state, dEnd));
      CHECK( sCheck(state, ' '));
      CHECK( sNumber(state, stepDuration));
      CHECK( SEOL(state));
      m_freqGen->setParams(wave, fStart, fEnd, dStart, dEnd, intensity, stepDuration);
      m_freqGen->protectedSetPower(true);
      return DONE;
    }
    if (strcmp(token, "off") == 0) {
      m_freqGen->protectedSetPower(false);
      return DONE;
    }
    if (strcmp(token, "print") == 0) {
      m_freqGen->print();
      return DONE;
    }
  }
  // If we are here, command is incorrect
  return ERROR;
}

uint8_t CmdParser::prgCMD(uint8_t state) {
  if (sPeek() == '\0') {
    PRINTLN(F(" prg on \n off \n print \n state \n dim N (1->10)"));
    return DONE;
  }
  else {
    CHECK(sToken(state, token, " "));
    if (strcmp(token, "on") == 0) {
      m_prg->setPower(true);
      Global::global.setMode(Global::AUTO);
      PRINTLND(F("Switch program to ON"));
      return DONE;
    }
    if (strcmp(token, "off") == 0) {
      m_prg->setPower(false);
      Global::global.setMode(Global::MANUAL);
      PRINTLND(F("Switch program to OFF"));
      return DONE;
    }
    if (strcmp(token, "print") == 0) {
      m_prg->print();
      return DONE;
    }
    if (strcmp(token, "state") == 0) {
      m_prg->printState();
      return DONE;
    }
    if (strcmp(token, "dim") == 0) {
      uint8_t dimVal;
      CHECK( sNumber(state, dimVal));
      CHECK( SEOL(state));
      m_prg->setDim(dimVal);
    }
    // If we are here, command is incorrect
    return ERROR;
  }
}

uint8_t CmdParser::logCMD(uint8_t state) {
  if (sPeek() == '\0') {
    PRINTLN(F(" log print \n  clear"));
    return DONE;
  }
  else {
    CHECK(sToken(state, token, " "));
    if (strcmp(token, "print") == 0) {
      Log::log1.print();
      Serial.println("done");
      return DONE;
    }
    if (strcmp(token, "clear") == 0) {
      Log::log1.clear();
      Serial.println("done");
      return DONE;
    }
    if (strcmp(token, "on") == 0) {
      Log::log1.on();
      Serial.println("done");
      return DONE;
    }
    if (strcmp(token, "off") == 0) {
      Log::log1.off();
      Serial.println("done");
      return DONE;
    }
    // If we are here, command is incorrect
    return ERROR;
  }
}

uint8_t CmdParser::helpCMD(uint8_t state) {
  if (sPeek() == '\0') {
    PRINTLN(F(" led : control LED power \n pulse : pulse generation at fixed freq and duty \n freq : pulse generation with variable freq and duty \n prg : programme load/run/stop/print/state \n log : debug log"));
    return DONE;
  }
}

uint8_t CmdParser::processCMD (uint8_t state) {
  CHECK(sToken(state, token, " "));
  if (strcmp(token, "pulse") == 0) {
    CHECK (pulseCMD(state));
    return DONE;
  }
  if (strcmp(token, "freq") == 0) {
    CHECK (freqCMD(state));
    return DONE;
  }
  if (strcmp(token, "led") == 0) {
    CHECK (ledCMD(state));
    return DONE;
  }

  if (strcmp(token, "prg") == 0) {
    CHECK (prgCMD(state));
    return DONE;
  }

  if (strcmp(token, "log") == 0) {
    CHECK (logCMD(state));
    return DONE;
  }
  if (strcmp(token, "help") == 0) {
    CHECK (helpCMD(state));
    return DONE;
  }
  PRINT (F("command not recognized : "));
  PRINTLN(token);
  return ERROR;
}


uint8_t  CmdParser::parse(uint8_t state, uint8_t action, uint8_t cycle) {
  char nextChar ;
  static uint8_t ret = 0;

  switch (state) {
    case READY:
      switch (action) {
        case ENTER:
          PRINTLND(F("Ready to parse new stuff"));
          break;

        case LOOP:
          // Empty line -> no job to do.

          if (SEOL(state) == state) return NO_CHANGE;
          //PRINTLND(F("Looping and characters to analyze"));
          nextChar = sPeek();
          switch (nextChar) {
            case '<' : return PRG_HEAD;
              break;
            default: return CMD;
          }

          break;
        case EXIT:
          break;
      }

      break;

    case CMD:
      switch (action) {
        case ENTER:
          break;

        case LOOP:
          return processCMD(state);
          break;

        case EXIT:
          break;
      }

      break;

    case PRG_HEAD:
      switch (action) {
        case ENTER:
          m_prg->clear();
          break;

        case LOOP:
          return SHead(state);
          break;

        case EXIT:
          // end of current machine cycle. Without this, we would try to read body section before any is available
          nextCycle();
          break;
      }

    case PRG_BODY:
      switch (action) {
        case ENTER:
          break;

        case LOOP:
          nextCycle();
          return SBody(state);
          break;

        case EXIT:
          break;
      }

      break;

    case PRG_END:

      switch (action) {
        case ENTER:
          PRINTLN(F("Program parsed successfully"));
          // m_prg->print();
          break;

        case LOOP:
          return DONE;
          break;

        case EXIT:
          break;
      }

      break;

    case DONE:

      switch (action) {
        case ENTER:
          PRINTLND(F("Command is done"));
          break;

        case LOOP:
          return READY;
          break;

        case EXIT:
          break;
      }
      break;

    case ERROR:

      switch (action) {
        case ENTER:
          PRINTLN(F("Parser error"));
          break;

        case LOOP:
          // Will exit Error state only when a new line is fed
          if (m_cursorPos == m_lineBuffer) return READY;
          else return NO_CHANGE;
          break;

        case EXIT:
          break;
      }
      break;

  }
  // In the cases we did not return anything in the switch
  return NO_CHANGE;
}

void CmdParser::printID() {
  Serial << F("Parser");
}

uint8_t CmdParser::loop(uint8_t state, uint8_t action, uint8_t cycle) {
  parse(state, action, cycle);
}


void CmdParser::init(SerialParse * sReader, PulseGen * pulseGen, FreqGen * freqGen, HWDimLed * led1, Programme * prg ) {
  m_textInput = sReader;
  m_lineBuffer = sReader->getBuffer();
  m_cursorPos = m_lineBuffer;
  m_freqGen = freqGen;
  m_pulseGen = pulseGen;
  m_prg = prg;
  m_led1 = led1;
  m_prg = prg;
  StateM::init(READY);
}

//
// End parser
//

//
// Begin Processor
//
void Processor::setPower(bool isOn)  {
  if (isOn != m_isOn) {
    m_isOn = isOn;

    if (isOn)   actionOff2On();
    else        actionOn2Off();
  }
}

void Processor::protectedSetPower(bool isOn)  {
  NOINT();
  setPower(isOn);
  INT();
}

bool Processor::isRunning() {
  return (m_isOn && !m_isDone);
}

bool Processor::isDone() {
  return (m_isOn && m_isDone);
}

bool Processor::getPower() {
  return m_isOn;
}

//
// End Processor
//


/*
    Function:     setPwmFrequencyMEGA2560(pin,divisior);





  This pins are together, can not modify frequency individually,same timmer):

  pin 13, 4
  pin 12, 11
  pin 10, 9
  pin 5, 3, 2
  pin 8, 7, 6

  For pins 13,4 (DO NOT MODIFY pins 13 & 4 is the one on which rely
  all time functions in Arduino: i.e., if you change the frequency of this pins,
  function like delay() or millis() will continue to work but at a different timescale
  quicker or slower!))


     Divisor          Frequency

    1     62500 Hz
  2     7812.5 Hz
  3     976.5625 Hz  <--DEFAULT Diecimila bootloader
  4     244.140625 Hz
  5     61.03515625 Hz

  For pins 2 to 13 EXCEPT 13,4:
            Divisor    Frequency

    1    31372.55 Hz
    2  3921.16  Hz
      3  490.20    Hz   <--DEFAULT Diecimila bootloader
    4  122.55    Hz
    5  30.610    Hz

*/
#if  defined(__AVR_ATmega2560__)
void setPwmFrequencyMEGA2560(int pin, int divisor) {
  byte mode;
  switch (divisor) {
    case 1: mode = 0x01; break;
    case 2: mode = 0x02; break;
    case 3: mode = 0x03; break;
    case 4: mode = 0x04; break;
    case 5: mode = 0x05; break;
    case 6: mode = 0x06; break;
    case 7: mode = 0x07; break;
    default: return;
  }

  switch (pin) {
    case 2:  TCCR3B = TCCR3B  & 0b11111000 | mode; break;
    case 3:  TCCR3B = TCCR3B  & 0b11111000 | mode; break;
    case 4:  TCCR0B = TCCR0B  & 0b11111000 | mode; break;
    case 5:  TCCR3B = TCCR3B  & 0b11111000 | mode; break;
    case 6:  TCCR4B = TCCR4B  & 0b11111000 | mode; break;
    case 7:  TCCR4B = TCCR4B  & 0b11111000 | mode; break;
    case 8:  TCCR4B = TCCR4B  & 0b11111000 | mode; break;
    case 9:  TCCR2B = TCCR0B  & 0b11111000 | mode; break;
    case 10: TCCR2B = TCCR2B  & 0b11111000 | mode; break;
    case 11: TCCR1B = TCCR1B  & 0b11111000 | mode; break;
    case 12: TCCR1B = TCCR1B  & 0b11111000 | mode; break;
    case 13: TCCR0B = TCCR0B  & 0b11111000 | mode; break;
    default: return;
  }

}

#endif

// Global stuff
Global Global::global;

uint8_t Global::getMode() volatile {
  return m_mode;
}
void Global::setMode (uint8_t mode) volatile {
  m_mode = mode;
}

int freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

// Static definition
Log Log::log1;


void Log::add(const LogData & data) {
  if (m_power)  m_log.add(data);
}
void Log::clear() {
  m_log.clear();
}

void Log::on() {
  m_power = true;
}

void Log::off() {
  m_power = true;
}

void Log::print() {
  Serial.print (F("log is "));
  Serial.println (m_power ? F("enabled") : F("disabled"));

  for (int i = 0; i < m_log.size(); i++) {
    m_log.get(i).print(i);
  }
}

void LogData::print (uint16_t index) {
  Serial.print (F("# "));
  Serial.print (index);
  Serial.print (F(" / t : "));
  Serial.print (timestamp);
  Serial.print (F(" / cycle : "));
  Serial.print (cycle);
  Serial.print (F(" / from : "));
  Serial.print (getOriginLabel(origin));
  Serial.print (F(" / action : "));
  Serial.print (getActionLabel(action));
  Serial.print (F(" / data : "));
  Serial.print (value);

  Serial.println();
}
// enum origins {PULSE_ID, FREQ_ID, PROGRAMME_ID};
const __FlashStringHelper*LogData::getOriginLabel(uint8_t id) {
  static const __FlashStringHelper* label[] = {
    F("Pulse"),
    F("Frequence"),
    F("Programme"),
    F("Invalide")
  };
  if (id < LAST_ID)
    return label[id];
  else
    return label[LAST_ID];
}

/*
           enum programme_log_actions {ON_P, NEWSTEP_P, DONE_P, OFF_P};
    enum pulse_log_actions {ON_PU=OFF_P+1, SETPARAMS_PU, BLEND_LOW_DELAYED_PU,BLEND_LOW_IMMEDIATE_PU,BLEND_HIGH_DELAYED_PU,BLEND_HIGH_IMMEDIATE_PU, OFF_PU};
    enum osc_log_actions {ON_O=OFF_PU+1,SETPARAMS_O,DONE_O, OFF_O, LAST_O};
*/

const __FlashStringHelper*LogData::getActionLabel(uint8_t id) {
  static const __FlashStringHelper* label[] = {
    F("On"),
    F("New step (data:step#)"),
    F("End of step (data:cycles in step)"),
    F("Done"),
    F("Off"),
    F("On"),
    F("set Params (data:freq&duty)"),
    F("blend Low delayed (data:next High time)"),
    F("blend Low immediate (data:next High time)"),
    F("blend High delayed (data:next Low time)"),
    F("blend High immediate (data:next Low time)"),
    F("Off"),
    F("On"),
    F("set Params (data : isRunning?)"),
    F("Done (data : calculated end time)"),
    F("Off"),
    F("Invalide")
  };
  if (id < LAST_O)
    return label[id];
  else
    return label[LAST_O];
}


