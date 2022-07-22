/* Copyright 2020 Snipeye
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include <string.h>
#include "quantum_keycodes.h"

enum uno_keycode
{
  UNO = SAFE_RANGE
};


//custom text after 2sec push
#define CUSTOM_STRING "||The world’s first computer programmer was a renowned female mathematician||\nBorn in London on December 10, 1815, Ada Lovelace, the daughter of the famous poet Lord Byron, was an extremely talented mathematician. Later on in life, she would work closely with Charles Babbage, a popular mechanical engineer responsible for creating one of the earliest mechanical computers.\n\nFrom there, she would write a theory about coding a machine to calculate Bernoulli numbers. The subsequent code would eventually become the first algorithm carried out by a machine, and in essence, was the first computer program."
//custom text after 10sec push
#define CUSTOM_STRINGA "||The first computer \"bug\" was an actual real-life bug||\nIn the programming world, a bug is an error that causes a program to crash or behave in strange ways. First coined by Thomas Edison in 1878 (to refer to technical errors of the period), the term \"bug\" would eventually find mainstream use in modern computing.\n\nHowever, it was in 1947 that the first case of a computer bug was recorded. Grace Hopper, an admiral in the US Navy, was working on a Mark II computer when she discovered a moth had become stuck in the relay, thus causing it to malfunction.\n\nOnce the moth was removed, she wrote in her journal \"first actual case of bug being found\" – and the rest is history."
//custom text after 30sec push
#define CUSTOM_STRING_LONG "What are you pushing so long? What do you think happens then? I can't think of any reason someone pushes for that long time. So go back to work and don't play any further with this."
//custom text after 1min
#define CUSTOM_STRING_EEGG "WOW \nYou have clearly no other things to do than push this button. But now you are here and here is your reward. A little picture how it all began. \n\n                            /`*_\n                            /    `-_\n                 _.,  _.   /        `-_\n             _,-` __`-_ `-/            `-_\n          ,-  .,~`  /  `-/               .`\n         :_ -`     \"    /`-@             /\n                  /`\\  ;    `-_         /\n               |-`.. `-\\  |    `-_     / `-_\n            _-`  `_.`\\  `-_ |;\\   @-_ / `-_/\n           -  .__.,,;___o  `-_|      /`-__-_\n          - 1`-_ .~--` _~` o   `-_   ;   `   -\n        .`Q W 2 `-_ `,`. /- - o   `-_\\  `     `\n       - A S  E  3 `-_  . / .|   _ ..`-_;     :\n    _-` Z X  D F R T 4`-_  ;  ;   `_ `_-`.-_,`\n .-`--_     C   G   Y  5 `-_ i    _-`    ;\n:  `-_//`-_   V  H J U I 6  `-_.-`       *\n-_    `-_  `-_    B N K L O 7 -          :\n  `-_    `-_  `-_    M . ; P .`      es  ;\n     `-_    `-_  `-_     ,  -           _`\n        `-_    `-_ /     -`         _-`\n           `-_    `-_/-_`        _-`\n              `-_    `-.      _-`\n                 `-_   .   .-`\n                    `-_:_-`    \n                       `\n\n------------------------------------------------\nThis ASCII pic can be found at\nhttps://asciiart.website/index.php?art=objects/typewriter\n"

static uint16_t pressTimer = 0xFFFF;
#define CUSTOM_LONGPRESS 300
#define CUSTOM_LONGERPRESS 1000
#define MACRO_LENGTH 2000
#define RESET_LENGTH 10000
#define CUSTOM_THIRTY 30000
#define CUSTOM_EEGG_LENGTH 60000
#define ALPHA "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"
#define NUMBERS "0123456789"
#define PUNCTUATION "?!.:,;&-+\\/\"%()={}[]*~<>|^'"
const uint8_t PROGMEM RGBLED_RAINBOW_MOOD_INTERVALS[] = { 10, 25, 50 };


bool buttonpush = false;
bool firstChar = true;
bool lastChar = true;
int charIndex = 0;
char* chars = ALPHA NUMBERS PUNCTUATION;


#define COUNTER X_A

enum encoder_names {
	_ENCODER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [0] = LAYOUT(
            UNO
          )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
		case UNO:
            if (record->event.pressed){
                pressTimer = timer_read();
                buttonpush = true;
            }
            else {
                uint16_t timeElapsed = timer_elapsed(pressTimer);
                buttonpush = false;
                if (timeElapsed < CUSTOM_LONGPRESS) {
                    send_string(" ");
                    firstChar = true;
                    charIndex = 0;
                } else if (timeElapsed < CUSTOM_LONGERPRESS) {
                    tap_code(KC_BSPC);
                } else if (timeElapsed < CUSTOM_THIRTY) {
                    send_string("\n");
                    firstChar = true;
                    charIndex = 0;
                } /*else if (timeElapsed < RESET_LENGTH) {
                    send_string(CUSTOM_STRING);
                } else if (timeElapsed < CUSTOM_THIRTY) {
                    send_string(CUSTOM_STRINGA);
                }*/ else if (timeElapsed < CUSTOM_EEGG_LENGTH) {
                    send_string(CUSTOM_STRING_LONG);
                } else {
                    send_string(CUSTOM_STRING_EEGG);
                }
            }
        break;
    }
    return false;
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(0, 0, 0);
    rgblight_mode(1);
    // Uncomment to enable rainbow mode when plugged in.
    // Otherwise, the LED will be revealed after a few keypresses.
    rgblight_sethsv_noeeprom(255, 255, 255);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD);
}

bool encoder_update_user(uint8_t index, bool counterClockwise) {
    int charLen = strlen(chars);

    if (index == _ENCODER) { /* First encoder */
        if (counterClockwise) {
            if(buttonpush){
                tap_code(KC_VOLD);
            }
            else if(!firstChar){
                charIndex--;
                if(charIndex < 0)
                    charIndex = charLen - 1;
            }
        } else {
            if(buttonpush){
                tap_code(KC_VOLU);
            }
            else if(!firstChar){
                charIndex++;
                charIndex = charIndex % charLen;
            }
        }

        firstChar = false;
        SEND_STRING(SS_TAP(X_BSPACE));

        char str[2] = "\0";
        str[0] = chars[charIndex];
        send_string(str);
    }
	return true;
}

