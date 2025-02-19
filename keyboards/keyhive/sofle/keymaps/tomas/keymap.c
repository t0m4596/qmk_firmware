 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
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
#include "transactions.h"
#include "oled.c"
#include "encoder.c"
#include "keymap_german.h"
#include "tomas_custom_keycodes.h"

enum layer_names {
  _BASE,
  _VIA1,
  _VIA2,
  _VIA3
};


//Default keymap. This can be changed in Via. Use oled.c and encoder.c to change beavior that Via cannot change.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTZ
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  ^   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  ß   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Z  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ü  |  #   |
 * |------+------+------+------+------+------|  MUTE |    |  F13  |------+------+------+------+------+------|
 * |LShift|   Y  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   Ö  |  Ä   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Space  /       \Enter \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */

[_BASE] = LAYOUT(
  DE_CIRC,  DE_1,   DE_2,    DE_3,    DE_4,    DE_5,                     DE_6,    DE_7,    DE_8,    DE_9,    DE_0,  DE_SS,
  KC_ESC,   DE_Q,   DE_W,    DE_E,    DE_R,    DE_T,                     DE_Z,    DE_U,    DE_I,    DE_O,    DE_P,  KC_BSPC,
  KC_TAB,   DE_A,   DE_S,    DE_D,    DE_F,    DE_G,                     DE_H,    DE_J,    DE_K,    DE_L, DE_UDIA,  DE_HASH,
  KC_LSFT,  DE_Y,   DE_X,    DE_C,    DE_V,    DE_B, KC_MUTE,    KC_F13, DE_N,    DE_M, DE_COMM,  DE_DOT, DE_ODIA,  DE_ADIA,
                 KC_LGUI,KC_LALT,KC_LCTRL, MO(1), KC_SPC,            KC_ENT,  MO(2), KC_RCTRL, KC_RALT, KC_RGUI
),




/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   !  |   @  |  _   |   $  |   %  |-------.    ,-------|   "  |   &  |   <  |   >  |   |  | F12  |
 * |------+------+------+------+------+------|  MUTE |    |  F13  |------+------+------+------+------+------|
 * | Shift|  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   (  |   )  |   /  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Space  /       \Enter \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
[_VIA1] = LAYOUT(
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_BSPC,
  _______, DE_EXLM,   DE_AT, DE_UNDS,  DE_DLR, DE_PERC,                        DE_DQUO, DE_AMPR, DE_LABK, DE_RABK, DE_PIPE, KC_F12,
  _______,  DE_EQL, DE_MINS, DE_PLUS, DE_LCBR, DE_RCBR, _______,       _______, DE_LBRC, DE_RBRC, DE_SCLN, DE_COLN, DE_SLSH, DE_BSLS,
                       _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),




/* RAISE
 * ,----------------------------------------.                     ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  | Ins  | Pscr |CnxtM |      |      |                    | PGup | PWrd |  Up  | NWrd |  Del | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | LAt  | LCtl |LShift|      | Caps |-------.    ,-------| PGup | Left | Down | Rigth|  Del | Bspc |
 * |------+------+------+------+------+------|  MUTE |    |  F13  |------+------+------+------+------+------|
 * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------|      | Pos1 |      |  End |      | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Space  /       \Enter \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
[_VIA2] = LAYOUT(
  _______, _______ , _______ , _______ , _______ , _______,                     _______,  _______  , _______,  _______ ,  _______ ,_______,
  _______,  KC_INS,  KC_PSCR,   KC_APP,  XXXXXXX, XXXXXXX,                        KC_PGUP,   WRD_L,  KC_UP,   WRD_R,  KC_DEL, KC_BSPC,
  _______, KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX, KC_CAPS,                       KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL, KC_BSPC,
  _______, WIN_UNDO, WIN_CUT, WIN_COPY, WIN_PASTE, XXXXXXX,  _______,      _______,  XXXXXXX, KC_HOME, XXXXXXX, KC_END,   XXXXXXX, _______,
                         _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
)
};




//RGB mode to static gradient at post
int i;

void keyboard_post_init_user(void) {
    #ifdef DOG_ENABLE
      transaction_register_rpc(KEY_PRESSED_EVENT, keyboard_sync_keypressed_event);
    #endif
    rgblight_sethsv_noeeprom(255, 255, 255);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT);
    for(i=0; i<5; i++){ //set RGB mode to gradient 6. is defenetly cleaner to get but this way it works
        rgblight_step_noeeprom();
    }
}

