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
#include "quantum_keycodes.h"

bool buttonpush = false;
bool MOVE = true;
uint16_t pressTimer;

enum uno_keycode
{
  UNO = SAFE_RANGE
};


const uint8_t PROGMEM RGBLED_RAINBOW_MOOD_INTERVALS[] = { 10, 25, 50 };


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
    switch (keycode) {
		case UNO:
          if (record->event.pressed){
                   pressTimer = timer_read();
                   buttonpush = true;
                }
           else { 
            uint16_t timeElapsed = timer_elapsed(pressTimer);
            buttonpush = false;
            if (timeElapsed < 1000) {
                if (MOVE){
                    MOVE = false;
                    rgblight_setrgb(255,0,0);
                    _delay_ms(500);
                }
                else {
                    MOVE = true;
                    rgblight_setrgb(0,255,0);
                    _delay_ms(500);
                }
            }
          
            else if ((1000 <= timeElapsed) && (timeElapsed <= 2000)) {
                tap_code(KC_MS_BTN1);
            }    
           
           
            else if ((2000 <= timeElapsed) && (timeElapsed <= 5000)) {
                tap_code(KC_MS_BTN2);
            }

            else if (5000 <= timeElapsed) {
                tap_code(KC_MS_BTN3);
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
    if (index == _ENCODER) { /* First encoder */
        if (counterClockwise) {
            if (MOVE){
                    tap_code(KC_MS_L);
                }
               else{
                    tap_code(KC_MS_D);
                }
            } 
        else {
            if (MOVE){
                tap_code(KC_MS_R);
            }
            else{
                tap_code(KC_MS_U);
            }
        }
    }
    return true;
}

