/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xCEEB
#define PRODUCT_ID      0x0007
#define DEVICE_VER      0x0001
#define MANUFACTURER    leafcutterlabs
#define PRODUCT         vsfighter2

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 16

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *                  NO_DIODE = switches are directly connected to AVR pins
 *
*/

// Srating with closest to USB port 
#define DIRECT_PINS {   \
    { F7, F6, F5, F4, D0, D1, D2, D3, D4, B1, B2, B3, B4, B5, B6, D7} \
}
//speed for double tap
#define TAPPING_TERM 300

#define UNUSED_PINS

/* ws2812 RGB LED */
#define RGB_DI_PIN C7 //D3 - underglow C7 - backlight
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 5    // Number of LEDs

// Max 32
#define JOYSTICK_BUTTON_COUNT 16
// Max 6: X, Y, Z, Rx, Ry, Rz
#define JOYSTICK_AXES_COUNT 2
