#include QMK_KEYBOARD_H
#include "custom_tap.h"


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
    TD_LAYER, /* single tap: toggle base/num layer
                 double tap: to default layer
                 hold: enable Fn layer */
    TD_X_ZK_WIN, /* single tap: x,
                  double tap: 全角半角
                  hold: Win */
    TD_Q_ESC, /* single tap: q,
                 double tap: Esc */
    TD_A_TAB, /* single tap: a,
                 double tap: Tab */
};


/***********************************************************
 * Function Prototypes
 **********************************************************/

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);
void xzk_finished(qk_tap_dance_state_t *state, void *user_data);
void xzk_reset(qk_tap_dance_state_t *state, void *user_data);
static void toggle_base_num_layer(void);
static void back_to_default_layer(void);


/***********************************************************
 * Constant Definitions
 **********************************************************/

/* Keycode definitions */
// #define FN1_SPC     LT(1, KC_SPC)
#define SFT_ENT     RSFT_T(KC_ENT)
#define CTL_BSPC    RCTL_T(KC_BSPC)
#define KC_J_BSLS   KC_INT1 /* JIS \_ */
#define SFT_Z       LSFT_T(KC_Z)


/***********************************************************
 * Configurations / Variables
 **********************************************************/

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275),
    [TD_X_ZK_WIN] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, xzk_finished, xzk_reset, 275),
    [TD_Q_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
    [TD_A_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_TAB),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base QWERTY key map */
  [CL_BASE] = LAYOUT_ortho_3x10_inv(
    TD(TD_Q_ESC),    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    TD(TD_A_TAB),    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    CTL_BSPC,
    SFT_Z,    TD(TD_X_ZK_WIN),  KC_C,    KC_V,   KC_SPC,  TD(TD_LAYER), KC_B,   KC_N,   KC_M,   SFT_ENT
  ),

  [CL_NUM] = LAYOUT_ortho_3x10_inv(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    /* |-/= |^/~ |\/| | */                                /* |@/` |;/+ |:* |[/{ |]/} */
    KC_MINS,   KC_EQL,   KC_JYEN,   KC_NO, KC_LBRC, KC_SCLN, KC_QUOT, KC_RBRC, KC_BSLS, _______,
    _______, _______, _______, KC_COMM, _______,  _______, KC_DOT, KC_SLSH, KC_J_BSLS, _______
  ),

  [CL_FN] = LAYOUT_ortho_3x10_inv(
    KC_F1, KC_F2,   KC_F3, KC_F4,  KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
    KC_F11,  KC_F12,  _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______,
    KC_PSCR, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
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


// Initialize tap structure associated with example tap dance key
static custom_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = 0
};


// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    // uint8_t   highest_layer;

    (void)user_data;

    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case SINGLE_HOLD:
            layer_on(CL_FN);
            break;
        case DOUBLE_TAP:
            back_to_default_layer();
            break;
        case SINGLE_TAP:
            toggle_base_num_layer();
            break;
        default:
            break;
    }
}


void ql_reset(qk_tap_dance_state_t *state, void *user_data) {

    (void)state;
    (void)user_data;

    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == SINGLE_HOLD) {
        layer_off(CL_FN);
    }
    ql_tap_state.state = 0;
}


static custom_tap_t xzk_tap_state = {
    .is_press_action = true,
    .state = 0
};


void xzk_finished(qk_tap_dance_state_t *state, void *user_data) {

    (void)user_data;

    xzk_tap_state.state = cur_dance(state);
    switch (xzk_tap_state.state) {
        case SINGLE_TAP:
            register_code(KC_X);
            break;
        case SINGLE_HOLD:
            register_code(KC_LWIN);
            break;
        case DOUBLE_TAP:
            register_code(KC_ZKHK);
            break;
        default:
          break;
    }
}


void xzk_reset(qk_tap_dance_state_t *state, void *user_data) {

    (void)state;
    (void)user_data;

    switch (xzk_tap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_X);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LWIN);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_ZKHK);
            break;
        default:
          break;
    }
    xzk_tap_state.state = 0;

}


static void toggle_base_num_layer(void) {
    uint8_t   highest_layer;

    /* get the current layer id */
    highest_layer = get_highest_layer(layer_state);

    if (highest_layer == CL_BASE) {
        layer_on(CL_NUM);
    }
    else {
        layer_off(CL_NUM);
    }
}


static void back_to_default_layer(void) {
    uint8_t i;
    /* disable all higher layers -> go back to base layer */
    for (i=(uint8_t)CL_BASE + 1U; i<CL_END; i++) {
        layer_off(i);
    }
}
