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

#define TAPPING_TERM    175 // milliseconds
#define COMBO_COUNT     12
#define COMBO_TERM      20

// LED under grow
#undef RGB_DI_PIN
#undef RGBLED_NUM
#define RGB_DI_PIN D3
#define RGBLED_NUM 2
#define RGBLIGHT_LAYERS
#define RGBLIGHT_SPLIT
#define RGBLED_SPLIT { 1, 1 }

