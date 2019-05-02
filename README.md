# toneAC Arduino Library for Arduino

## Introduction

Replacement to the standard tone library with many advantages:

* Nearly twice the volume (because it uses two out of phase pins in push/pull fashion)
* Higher quality (less clicking)
* Capability of producing higher frequencies (even if microcontroller is running at a lower clock speed)
* Nearly 1.5k smaller compiled code
* Bug fixes (standard tone library can generate some odd and unpredictable results)
* Can set not only the frequency but also the sound volume
* Less stress on the speaker so it will last longer and sound better

Disadvantages are that it must use certain pins and it uses two pins instead of one. But, if you're flexible with your pin choices, this is a great upgrade. It also uses timer 1 instead of timer 2, which may free up a conflict you have with the tone library. It exclusively uses port registers for the fastest and smallest code possible (which also makes it **ONLY compatible with ATmega microcontrollers**).

## Difference between toneAC and toneAC2

First off, toneAC is **SUPERIOR** to [toneAC2](https://bitbucket.org/teckel12/arduino-toneac2/wiki/Home). It's called [toneAC2](https://bitbucket.org/teckel12/arduino-toneac2/wiki/Home) only because it uses timer 2, not because it's a newer version of toneAC. [https://bitbucket.org/teckel12/arduino-toneac2/wiki/Home](toneAC2) is an alternate but **INFERIOR** version of toneAC that uses timer 2 instead of timer 1 and allows for any two pins to be used. You should use toneAC instead of [toneAC2](https://bitbucket.org/teckel12/arduino-toneac2/wiki/Home) if at all possible because toneAC is more accurate, higher quality, allows for higher frequencies, uses fewer CPU cycles, and creates smaller code. However, if you're having a conflict with timer 1, or just can't use the default PWM pins for timer 1, then [toneAC2](https://bitbucket.org/teckel12/arduino-toneac2/wiki/Home) may be your answer.

## Download & Install

**[v1.5.0 Released](https://github.com/teckel12/arduino-toneac/releases)**

Save the .zip file to your desktop, then use the [Importing a .zip Library](https://www.arduino.cc/en/Guide/Libraries#toc4) instructions to import the library into the Arduino IDE.

(12,437 downloads on Bitbucket before moving to GitHub, 7,405 downloads on Google Code before being closed)

## Show Your Appreciation

Help future development by making a small donation (the teckel@bex.net payee is correct).

[![Donate](https://bitbucket.org/repo/Bpybg9/images/698700421-btn_donate_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=teckel%40bex%2enet&lc=US&item_name=Arduino%20toneAC&item_number=Arduino%20toneAC&no_note=0&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donate_LG%2egif%3aNonHostedGuest)

## Supporters

* SuperTechSales $10 on July 29th, 2018
* Petr V. $5 on July 1st, 2018
* [D&D Archive](https://www.dndarchive.com) $5
* John C. $5
* Christian L. $2
* John W. $5
* Molly N. $5
* Erez M. $5
* Jonny R. $1
* Thomas W. $1
* Louis B. $20
* Regalia S. $5
* Shawn C. $30

## Compatibility

toneAC is written specifically for the ATmega AVR platform as it uses timer events that only exist with this platform.  Compatibility includes the following platforms/microcontrollers:

* ATmega328, ATmega128, ATmega640, ATmega8, Uno, Leonardo, ATmega2560/2561, ATmega1280/1281, Mega, ATmega1284P, ATmega644, Teensy 2.0, Teensy++ 2.0

## Connection Example

Connection is very similar to a piezo or standard speaker. Except, instead of connecting one speaker wire to ground you connect both speaker wires to Arduino pins. The pins you connect to are specific, as toneAC lets the ATmega microcontroller do all the pin timing and switching. This is important due to the high switching speed possible with toneAC and to make sure the pins are always perfectly out of phase with each other (push/pull). See the below list for which pins to use for different Arduinos. Just as usual when connecting a speaker, make sure you add an inline 100 ohm resistor between one of the pins and the speaker wire.

* **Pins 9 & 10** - ATmega328, ATmega128, ATmega640, ATmega8, Uno, Leonardo, etc.
* **Pins 11 & 12** - ATmega2560/2561, ATmega1280/1281, Mega
* **Ping 12 & 13** - ATmega1284P, ATmega644
* **Pins 14 & 15** - Teensy 2.0
* **Pins 25 & 26** - Teensy++ 2.0

![oneAC3.png](https://bitbucket.org/repo/Kg6beL/images/3490992041-toneAC3.png)

## Syntax

**toneAC(frequency [, volume [, length [, background ]]])** - Play a note.

* **frequency** - Play the specified frequency indefinitely, turn off with toneAC().
* **volume** - [optional] Set a volume level. (default: 10, range: 0 to 10 [0 = off])
* **length** - [optional] Set the length to play in milliseconds. (default: 0 [forever], range: 0 to 2^32-1)
* **background** - [optional] Play note in background or pause till finished? (default: false, values: true/false)

**toneAC()** - Stop output.

**noToneAC()** - Same as toneAC().

## History

**v1.5.0 - Released 04/27/2019** - Moved repo to GitHub and made toneAC compatible with Arduino library manager.

**v1.4 - Released 10/02/2017** - Added NOTONEAC and PLAY_FOREVER macros for code clarity and improved readability. Gabriel Staples, www.ElectricRCAircraftGuy.com

**v1.3 - Released 08/19/2016** - Fixed to work with Teensy++ 2.0 and probably the 1.0 model as well. Cleaned up and organized code which resulted in smaller compiled code size and no longer the need for the TONEAC_TINY switch and alternate method.

**v1.2 - Released 01/27/2013** - Fixed a counter error which went "over the top" and caused periods of silence (thanks Krodal). For advanced users needing tight code, the TONEAC_TINY switch in toneAC.h activates a version of toneAC() that saves 110 bytes. With TONEAC_TINY, the syntax is toneAC(frequency, length) which plays the note at full volume in the background. Added support for the ATmega 640, 644, 1281, 1284P and 2561 microcontrollers.

**v1.1 - Released 01/16/2013** - Option to play notes in background, returning control back to your sketch for processing while note plays (similar to the way the tone library works). Volume is now linear and in the range from 0-10. Now uses prescaler 256 instead of 64 for frequencies below 123 Hz so it can go down to 1 Hz no matter what speed the CPU is clocked at (helpful if using toneAC to control a two-pin dual LED).

**v1.0 - Released 01/11/2013** - Initial release.

## Support Forum

[toneAC support forum](https://forum.arduino.cc/index.php?topic=142097.0)

## Example

```cpp
#include <toneAC.h>

void setup() {} // Nothing to setup, just start playing!

void loop() {
  for (unsigned long freq = 150; freq <= 15000; freq += 10) {  
    toneAC(freq); // Play the frequency (150 Hz to 15 kHz in 10 Hz steps).
    delay(1);     // Wait 1 ms so you can hear it.
  }
  toneAC(0); // Turn off toneAC, can also use noToneAC().

  while(1); // Stop (so it doesn't repeat forever driving you crazy--you're welcome).
}
```

## How Does It Work

The library is named toneAC because it produces an alternating push/pull between two pins. It's not really AC (alternating current) as in-wall electrical wiring because it's a square wave and never produces a negative voltage. However, the effect of the alternating push/pull creates an effective double voltage differential which produces the higher volume level.

The ATmega's PWM takes care of the alternating push/pull so the accuracy is exact. When you send a tone to a speaker with the standard tone library, the loudest is at 50% duty cycle (only on half the time). Which at 5 volts, is like sending only 2.5v to the speaker. With toneAC, we're sending out of phase signals on two pins. So, in effect, the speaker is getting 5 volts instead of 2.5, making it nearly twice as loud.

The sound quality difference has to do with allowing the Arduino's PWM to take care of everything and careful programming. Longer piezo life happens because instead of driving the transducer disc only ever in one direction (deforming the disc and reducing sound and quality), it drives it in both directions keeping the disc uniform.

## Cool User Projects Using toneAC

[![YouTube of Arduino Soundtube (Kundt's Tube)](https://bitbucket.org/repo/Kg6beL/images/3758661730-soundtube.jpg)](https://www.youtube.com/watch?v=RRxPJvIBGxM) | [![YouTube of EE 47 Final Project](https://bitbucket.org/repo/Kg6beL/images/4144195896-ee47final.jpg)](https://www.youtube.com/watch?v=8FrwLX6i0J0)
--- | ---
[![Project-HandBat](https://bitbucket.org/repo/Kg6beL/images/3974880769-toneAC-handbat.jpg)](https://arduino-info.wikispaces.com/Project-HandBat) |

## My Other Arduino Libraries

**[NewPing](https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home)** Works with many ultrasonic sensors, can communicate using only one pin, very low lag, fast (up to 30 pings per second), timer interrupt method for event-driven sketches, light code, and much more.

**[LCDBitmap](https://bitbucket.org/teckel12/arduino-lcd-bitmap/wiki/Home)** Arduino library that allows you to create a tiny 20x16 pixel bitmap (raster) display on a normally character-only Hitachi HD44780 based LCD display. Typical drawing functions like line, rectangle, invert, etc. Control is right down to the pixel level.

**[toneAC2](https://bitbucket.org/teckel12/arduino-toneac2/wiki/Home)** Replacement to the standard tone library with the advantage of nearly twice the volume, 800 bytes smaller compiled code size, and less stress on the speaker.

**[NewTone](https://bitbucket.org/teckel12/arduino-new-tone/wiki/Home)** About 1,200 bytes smaller code size than the standard tone library, faster execution time, exclusive use of port registers for fastest and smallest code, higher quality sound output than tone library.

**[TimerFreeTone](https://bitbucket.org/teckel12/arduino-timer-free-tone/wiki/Home)** Replacement to the standard tone library but without using timers.  Also, over 1.5k smaller compiled code, exclusive use of port registers, and compatible with ATmega, ATtiny, and ARM-based microcontrollers.