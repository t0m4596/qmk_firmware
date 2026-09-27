// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "keymap_german.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,          KC_7,    KC_8,    KC_9,    KC_0,    DE_SS,   DE_ACUT, KC_BSPC,
        KC_TAB,  DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,    DE_Z,          DE_U,    DE_I,    DE_O,    DE_P,    DE_UDIA, DE_PLUS, KC_DEL,
        KC_CAPS, DE_A,    DE_S,    DE_D,    DE_F,    DE_G,    DE_H,          DE_J,    DE_K,    DE_L,    DE_ODIA, DE_ADIA, DE_HASH, KC_ENT,
        KC_LCTL, DE_LABK, DE_Y,    DE_X,    DE_C,    DE_V,    DE_B,          DE_N,    DE_M,    DE_COMM, DE_DOT,  DE_MINS, KC_RSFT, KC_RCTL,

                           KC_LGUI, KC_LALT,                                      KC_RALT, KC_RGUI,

                                             KC_ESC,  KC_TAB,     KC_DEL,  KC_BSPC,
                                             KC_HOME, KC_END,     KC_PGUP, KC_PGDN,
                                             KC_SPC,  KC_ENT,     KC_ENT,  KC_SPC
    )
};
