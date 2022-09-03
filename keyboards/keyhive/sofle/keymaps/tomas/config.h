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

#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/

//OLED Settings
#define OLED_DISABLE_TIMEOUT
#define OLED_DRIVER_ENABLE  //when disabled, dog must be disabled for compiling to work
#define OLED_BRIGHTNESS 30
#define SPLIT_OLED_ENABLE
#define SPLIT_LED_STATE_ENABLE

//activate Dog
#define DOG_ENABLE 

//activate WPM counter
#define WPM_COUNTER

//features when usb isn't left for oled to work //can be disabled when oled not used
#define SPLIT_WPM_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_TRANSACTION_IDS_KB KEY_PRESSED_EVENT

//Add RGB underglow
#define RGB_DI_PIN D3
#define RGBLED_NUM 74
#define RGBLED_SPLIT {37,37}
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_LIMIT_VAL 150

//left_right setting
#define EE_HANDS