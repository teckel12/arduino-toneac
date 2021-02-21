/* ---------------------------------------------------------------------------
Created by Tim Eckel - teckel@leethost.com
Copyright 2019 License: GNU GPL v3 http://www.gnu.org/licenses/gpl-3.0.html

See "toneAC.h" for purpose, syntax, version history, links, and more.
--------------------------------------------------------------------------- */

#include "toneAC_internal.h"

#if defined(__AVR__)

#if defined (__AVR_ATmega32U4__) || defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1281__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__) || defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
  #define PWMT1AMASK DDB5
  #define PWMT1BMASK DDB6
  #define PWMT1DREG DDRB
  #define PWMT1PORT PORTB
#elif defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644__) || defined(__AVR_ATmega644P__)
  #define PWMT1AMASK DDD4
  #define PWMT1BMASK DDD5
  #define PWMT1DREG DDRD
  #define PWMT1PORT PORTD
#else
  #define PWMT1AMASK DDB1
  #define PWMT1BMASK DDB2
  #define PWMT1DREG DDRB
  #define PWMT1PORT PORTB
#endif

#if defined(__AVR_ATmega8__) || defined(__AVR_ATmega128__)
  #define TIMSK1 TIMSK
#endif

void toneAC_init() {
}

void toneAC_playNote(unsigned long frequency, uint8_t volume) {
  PWMT1DREG |= _BV(PWMT1AMASK) | _BV(PWMT1BMASK); // Set timer 1 PWM pins to OUTPUT (because analogWrite does it too).

  uint8_t prescaler = _BV(CS10);                  // Try using prescaler 1 first.
  unsigned long top = F_CPU / frequency / 2 - 1;  // Calculate the top.
  if (top > 65535) {                              // If not in the range for prescaler 1, use prescaler 256 (122 Hz and lower @ 16 MHz).
    prescaler = _BV(CS12);                        // Set the 256 prescaler bit.
    top = top / 256 - 1;                          // Calculate the top using prescaler 256.
  }

  ICR1   = top;                                     // Set the top.
  if (TCNT1 > top) TCNT1 = top;                     // Counter over the top, put within range.
  TCCR1B = _BV(WGM13)  | prescaler;                 // Set PWM, phase and frequency corrected (top=ICR1) and prescaler.
  OCR1A  = OCR1B = top / _tAC_volume[volume - 1];   // Calculate & set the duty cycle (volume).
  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(COM1B0); // Inverted/non-inverted mode (AC).
}

void noToneAC() {
  TIMSK1 &= ~_BV(OCIE1A);        // Remove the timer interrupt.
  TCCR1B  = _BV(CS11);           // Default clock prescaler of 8.
  TCCR1A  = _BV(WGM10);          // Set to defaults so PWM can work like normal (PWM, phase corrected, 8bit).
  PWMT1PORT &= ~_BV(PWMT1AMASK); // Set timer 1 PWM pins to LOW.
  PWMT1PORT &= ~_BV(PWMT1BMASK); // Other timer 1 PWM pin also to LOW.
}

unsigned long _tAC_time; // Used to track end note with timer when playing note in the background.

void noToneAC_setTimer(unsigned long delay) {
  _tAC_time = millis() + delay;     // Set when the note should end.
  TIMSK1 |= _BV(OCIE1A);            // Activate the timer interrupt.
}

ISR(TIMER1_COMPA_vect) {                 // Timer interrupt vector.
  if (millis() >= _tAC_time) noToneAC(); // Check to see if it's time for the note to end.
}

#endif
