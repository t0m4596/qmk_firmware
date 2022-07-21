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

enum uno_keycode
{
  UNO = SAFE_RANGE
};

static uint16_t pressTimer = 0xFFFF;
#define CUSTOM_LONGPRESS 150
#define CUSTOM_LONGERPRESS 750
#define CUSTOM_STRING "\nHier sind die Links zu den Teilen die du benoetigst: \nhttps://www.hornbach.de/shop/GEBERIT-Mepla-Uebergangsbogen-90-16mm-x-1-2-mit-Aussengewinde/4666456/artikel.html   2x \nhttps://www.hornbach.de/shop/GEBERIT-Mepla-Anschlusswinkel-90-16mm-x-1-2-36mm-tief/4666461/artikel.html  2x"
#define RESET_LENGTH 3000
const uint8_t PROGMEM RGBLED_RAINBOW_MOOD_INTERVALS[] = { 10, 25, 50 };

char stringToSend[2] = "a";
char maxLetter = 'z';

uint8_t presetCounter = 0;

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
            }
            else {
                uint16_t timeElapsed = timer_elapsed(pressTimer);

                if (timeElapsed < CUSTOM_LONGPRESS) {
                    tap_code(KC_MUTE);
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

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _ENCODER) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
            tap_code(KC_A);
        } else {
            tap_code(KC_VOLD);
            tap_code(KC_B);
        }
		return false;
    }
	return true;
}

