/* ---------------------------------------------------------------------------
Created by Tim Eckel - teckel@leethost.com
Copyright 2019 License: GNU GPL v3 http://www.gnu.org/licenses/gpl-3.0.html

See "toneAC.h" for purpose, syntax, version history, links, and more.
--------------------------------------------------------------------------- */

#ifndef toneAC_internal_h
  #define toneAC_internal_h

  #include "toneAC.h"

  #if !defined(__AVR__)
    #error Unsupported architecture
  #endif

  const uint8_t _tAC_volume[] = { 200, 100, 67, 50, 40, 33, 29, 22, 11, 2 }; // Duty for linear volume control.

  void toneAC_init();
  void toneAC_playNote(unsigned long frequency, uint8_t volume);
  void noToneAC_setTimer(unsigned long delay);
#endif
