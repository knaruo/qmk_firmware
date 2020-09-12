/* Copyright 2018
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

/* Make layout the right way:
 *  - USB port on left side
 *  - Switches facing the correct way
 */
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#define MATRIX_ROW_PINS { B6, B2, B3, B1, F7 }
#define MATRIX_COL_PINS { D0, D4, C6, D7, E6, B4 }

#define TAPPING_TERM    175 // milliseconds
#define IGNORE_MOD_TAP_INTERRUPT
#define COMBO_COUNT     5
#define COMBO_TERM      30

// LED under grow
#undef RGB_DI_PIN
#undef RGBLED_NUM
#define RGB_DI_PIN D3
#define RGBLED_NUM 1
#define RGBLIGHT_LAYERS
