#include "makro06.h"
#include "oled.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT(
		RGB_MOD, RGB_HUI, RGB_VAI,
		RGB_TOG, RGB_HUD, RGB_VAD),
};
