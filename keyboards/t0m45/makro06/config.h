#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    t0m45
#define PRODUCT         makro06

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

/* key matrix pins */
#define MATRIX_ROW_PINS { B1, B3, B6 }
#define MATRIX_COL_PINS { F5, D4, D7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL


#ifdef LINK_TIME_OPTIMIZATION_ENABLE
#    ifndef NO_ACTION_MACRO
#        define NO_ACTION_MACRO
#    endif
#    ifndef NO_ACTION_FUNCTION
#        define NO_ACTION_FUNCTION
#    endif
#endif

/* LED configuration */
#define RGB_DI_PIN D2
#define RGBLED_NUM 6
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_TWINKLE

/* Encoder configuration */
#define ENCODERS_PAD_A { F1 }
#define ENCODERS_PAD_B { F0 }
#define ENCODER_RESOLUTION 4

#define TAP_CODE_DELAY 10

/* if direction must be flipped */
/* #define ENCODER_DIRECTION_FLIP */
