
#pragma once

#include "config_common.h"

//board infos
#define DEVICE_VER 0x0001
#define MANUFACTURER t0m45
#define PRODUCT makro06

//define matrix
#define MATRIX_ROWS 2
#define MATRIX_COLS 4

//pinout
#define MATRIX_ROW_PINS { B3, F6 }
#define MATRIX_COL_PINS { D4, D7, B4, B5 }

#define DIODE_DIRECTION ROW2COL

#define DEBOUNCE 10

/* encoder support */
#define ENCODERS_PAD_A { B6 }
#define ENCODERS_PAD_B { B2 }
