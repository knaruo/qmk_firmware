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
#include QMK_KEYBOARD_H
#include "custom_tap.h"
#include "td_qesc.h"

// extern rgblight_config_t rgblight_config;

/***********************************************************
 * Data Type Definitions
 **********************************************************/

/* User custom keymap layers */
enum custom_layers {
  CL_BASE = 0,
  CL_NUM,
  CL_FN,
  CL_END,  /* end of supported layers */
};

// Tap Dance declarations
enum {
    TD_Q_ESC, /* single tap: q,
                 double tap: Esc */
};


/***********************************************************
 * Function Prototypes
 **********************************************************/

/***********************************************************
 * Constant Definitions
 **********************************************************/

/* Keycode definitions */
#define SPC_LY_NUM     LT(CL_NUM, KC_SPC)
#define DEL_LY_FN      LT(CL_FN, KC_DEL)
#define SFT_ENT     RSFT_T(KC_ENT)
#define CTL_BSPC    RCTL_T(KC_BSPC)
#define CTL_DEL     RCTL_T(KC_DEL)
#define KC_J_BSLS   KC_INT1 /* JIS \_ */
#define SFT_Z       LSFT_T(KC_Z)


/***********************************************************
 * Configurations / Variables
 **********************************************************/

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_Q_ESC] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, qesc_finished, qesc_reset, 200),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base QWERTY key map */
  [CL_BASE] = LAYOUT_split(
    TD(TD_Q_ESC),    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    CTL_BSPC,
    SFT_Z,    LWIN_T(KC_X),  KC_C,    KC_V,   SPC_LY_NUM,  DEL_LY_FN, KC_B,   KC_N,   KC_M,   SFT_ENT
  ),

  [CL_NUM] = LAYOUT_split(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    /* |-/= |^/~ |\/| | */                                /* |@/` |;/+ |:* |[/{ |]/} */
    KC_TAB,  KC_MINS,   KC_EQL,   KC_JYEN, KC_LBRC, KC_SCLN, KC_QUOT, KC_RBRC, KC_BSLS, CTL_BSPC,
    KC_LSFT, KC_ZKHK, KC_LALT, KC_COMM, _______,  _______, KC_DOT, KC_SLSH, KC_J_BSLS, _______
  ),

  [CL_FN] = LAYOUT_split(
    KC_F11, KC_F2,   KC_F3, KC_F4,  KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
    KC_TAB,  KC_F12,  _______, _______, KC_PSCR, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, LALT(LCTL(KC_DEL)),
    KC_LSFT, _______, _______, KC_HENK, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),

};


/***********************************************************
 * Functions
 **********************************************************/

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.
}


void led_set_user(uint8_t usb_led) {
  (void)usb_led;
}


bool process_record_user(uint16_t keycode, keyrecord_t * record) {
  (void)keycode;
  (void)record;

  return true;
}


const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,2,HSV_ORANGE}
	);
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,2,HSV_GREEN}
	);
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,2,HSV_RED}
);
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
		my_layer0_layer,
		my_layer1_layer,
		my_layer2_layer
	);

void keyboard_post_init_user(void) {
	//Enable the LED layers
	rgblight_layers = my_rgb_layers;
  rgblight_enable();
	layer_state_set_user(layer_state);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, false);
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    if (layer_state_cmp(state, 0)) {
      rgblight_disable_noeeprom();
    }
    else {
      rgblight_enable_noeeprom();
    }
    return state;
}