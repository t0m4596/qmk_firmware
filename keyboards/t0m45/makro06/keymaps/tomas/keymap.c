#include "makro06.h"
#include "oled.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		RGB_MOD, KC_1, RGB_VAI,
		RGB_TOG, QK_BOOT, RGB_VAD, DF(1)
        ),

    [1] = LAYOUT(
        RGB_MOD, KC_2, RGB_VAI,
		RGB_TOG, QK_BOOT, RGB_VAD, DF(2)
    ),

    [2] = LAYOUT(
        RGB_MOD, KC_3, RGB_VAI,
		RGB_TOG, QK_BOOT, RGB_VAD, DF(3)
    ),

    [3] = LAYOUT(
        RGB_MOD, KC_4, RGB_VAI,
		RGB_TOG, QK_BOOT, RGB_VAD, DF(0)
    ),
};



void keyboard_post_init_user(void) {
    /* stuff keyboard should do after boot */
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}

