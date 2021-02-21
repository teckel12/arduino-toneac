/* ---------------------------------------------------------------------------
Created by Tim Eckel - teckel@leethost.com
Copyright 2019 License: GNU GPL v3 http://www.gnu.org/licenses/gpl-3.0.html

See "toneAC.h" for purpose, syntax, version history, links, and more.
--------------------------------------------------------------------------- */

#include "toneAC.h"
#include "toneAC_internal.h"

void toneAC(unsigned long frequency, uint8_t volume, unsigned long length, uint8_t background) {
  toneAC_init();
  if (frequency == NOTONEAC || volume == 0) { noToneAC(); return; } // If frequency or volume are 0, turn off sound and return.
  if (volume > 10) volume = 10;       // Make sure volume is in range (1 to 10).

  toneAC_playNote(frequency, volume); // Routine that plays the note using timers.

  if (length == PLAY_FOREVER) return; // If length is zero, play note forever.

  if (background) {                   // Background tone playing, returns control to your sketch.
    noToneAC_setTimer(length);
  } else {
    delay(length);                    // Just a simple delay, doesn't return control till finished.
    noToneAC();
  }
}
