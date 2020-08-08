#include QMK_KEYBOARD_H


/***********************************************************
 * Data Type Definitions
 **********************************************************/

/* User custom keycode (for layer transition) */
enum custom_keycodes {
  TO_UP_LAYER = SAFE_RANGE, /* move to upper layer */
  TO_LO_LAYER, /* move to lower layer */
  TO_DEF_LAYER, /* to default layer */
};

/* User custom keymap layers */
enum custom_layers {
  CL_BASE = 0,
  CL_JP,
  CL_NUM,
  CL_FN,
  CL_3,
  CL_4,
  CL_MACROS,
  CL_END,  /* end of supported layers */
};

// Tap Dance declarations
enum {
    TD_LAYER, /* single tap: Go to higher layer,
                 double tap: Go to lower layer,
                 hold: Go to default layer */
    TD_X_ZKHK, /* single tap: x,
                  double tap: 全角半角 */
};

typedef struct {
    bool is_press_action;
    uint8_t state;
} custom_tap_t;

// Define a type for as many tap dance states as you need
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP
};


/***********************************************************
 * Function Prototypes
 **********************************************************/
// Function associated with all tap dances
uint8_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);


/***********************************************************
 * Constant Definitions
 **********************************************************/

/* Keycode definitions */
#define FN1_SPC     LT(1, KC_SPC)
#define SFT_ENT     RSFT_T(KC_ENT)
#define CTL_ESC     RCTL_T(KC_ESC)


/***********************************************************
 * Configurations / Variables
 **********************************************************/

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275),
    [TD_X_ZKHK] = ACTION_TAP_DANCE_DOUBLE(KC_X, KC_ZKHK),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base QWERTY key map */
  [CL_BASE] = LAYOUT_ortho_3x10_inv(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    CTL_ESC,
    KC_Z,    TD(TD_X_ZKHK),    KC_C,    KC_V,   FN1_SPC,  TD(TD_LAYER), KC_B,   KC_N,   KC_M,   SFT_ENT
  ),

  /* Mainly to support Japanese input */
  [CL_JP] = LAYOUT_ortho_3x10_inv(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSPACE
  ),

  [CL_NUM] = LAYOUT_ortho_3x10_inv(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    _______, _______, _______, _______, KC_DEL,  _______, _______, _______, _______, _______
  ),

  [CL_FN] = LAYOUT_ortho_3x10_inv(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, KC_GRV,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [CL_3] = LAYOUT_ortho_3x10_inv(
    _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    KC_TAB,  _______, _______, _______, _______, KC_COMM, KC_DOT,  KC_SLSH, KC_SCLN, KC_QUOT,
    _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

  [CL_4] = LAYOUT_ortho_3x10_inv(
    _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    KC_TAB,  _______, _______, _______, _______, KC_LABK, KC_RABK, KC_QUES, KC_COLN, KC_DQUO,
    _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),

  [CL_MACROS] = LAYOUT_ortho_3x10_inv(
    KC_CALC, KC_WHOM, KC_MAIL, KC_MYCM, _______, _______, _______, _______, _______, KC_PSCR,
    _______, _______, _______, _______, _______, _______, _______, _______, BL_DEC,  BL_INC,
    _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______
  )

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


// Determine the current tap dance state
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) return DOUBLE_TAP;
    else return 8;
}


// Initialize tap structure associated with example tap dance key
static custom_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = 0
};


// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    uint8_t   highest_layer;

    (void)state;
    (void)user_data;

    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case SINGLE_TAP:
            /* get the current layer id */
            highest_layer = get_highest_layer(layer_state);
            if (highest_layer < (uint8_t)(CL_END - 1U)) {
              /* increment & turn on the layer above */
              layer_on(highest_layer + 1U);
            }
            break;
        case SINGLE_HOLD:
            ql_reset(state, user_data);
            break;
        case DOUBLE_TAP:
            /* get the current layer id */
            highest_layer = get_highest_layer(layer_state);
            if (highest_layer > (uint8_t)CL_BASE) {
                /* just disable the current layer */
                layer_off(highest_layer);
            }
            break;
        default:
          break;
    }
}


void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    uint8_t   i;

    (void)state;
    (void)user_data;

    // If the key was held down and now is released then switch off the layer
    /* tap dance: Hold is detected.
       Go to default layer */
    if (ql_tap_state.state == SINGLE_HOLD) {
      /* disable all higher layers -> go back to base layer */
      for (i=(uint8_t)CL_BASE + 1U; i<CL_END; i++) {
        layer_off(i);
      }
    }
    ql_tap_state.state = 0;
}