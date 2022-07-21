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

enum uno_keycode
{
  UNO = SAFE_RANGE
};

static uint16_t pressTimer = 0xFFFF;
#define CUSTOM_LONGPRESS 500
#define CUSTOM_LONGERPRESS 1500
#define CUSTOM_STRING "\nHier sind die Links zu den Teilen die du benoetigst: \nhttps://www.hornbach.de/shop/GEBERIT-Mepla-Uebergangsbogen-90-16mm-x-1-2-mit-Aussengewinde/4666456/artikel.html   2x \nhttps://www.hornbach.de/shop/GEBERIT-Mepla-Anschlusswinkel-90-16mm-x-1-2-36mm-tief/4666461/artikel.html  2x"
#define RESET_LENGTH 130000
#define ALPHA "AaBbCcDdEeFfGgHhIiJjKkLlMmOnNoPpQqRrSsTtUuVvWwXxYyZz"
#define NUMBERS "0123456789"
#define PUNCTUATION "\\\""
const uint8_t PROGMEM RGBLED_RAINBOW_MOOD_INTERVALS[] = { 10, 25, 50 };

bool firstChar = true;
bool lastChar = true;
int charIndex = 0;
char* chars = ALPHA NUMBERS;


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
    // int charLen = strlen(chars);
    switch (keycode) {
		case UNO:
            if (record->event.pressed) {
                pressTimer = timer_read();
                while (record->event.pressed){
                    uint16_t timeElapsed = timer_elapsed(pressTimer);
                    if (timeElapsed > CUSTOM_LONGERPRESS){
                        tap_code(KC_BSPC);
                        wait_ms(200);
                    }
                }    
                break;
            } 
            else {
                uint16_t timeElapsed = timer_elapsed(pressTimer);

                if (timeElapsed < CUSTOM_LONGPRESS) {
                    send_string(" ");
                    firstChar = true;
                    charIndex = 0;
                } else if (timeElapsed < CUSTOM_LONGERPRESS) {
                    send_string("\n");
                    firstChar = true;
                    charIndex = 0; 
                } else if (timeElapsed < RESET_LENGTH) {
                    // Longer press, display macro.
                    //SEND_STRING(CUSTOM_STRING);
                } else {
                    reset_keyboard();
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
            if(!firstChar){
                charIndex--;
                if(charIndex < 0)
                    charIndex = charLen - 1;
            }
        } else {
            if(!firstChar){
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

