#include QMK_KEYBOARD_H


enum custom_keycodes {
  TO_UP_LAYER = SAFE_RANGE, /* move to upper layer */
  TO_LO_LAYER, /* move to lower layer */
  TO_DEF_LAYER, /* to default layer */
};

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


#define FN1_SPC     LT(1, KC_SPC)
#define FN2_BSPC    LT(2, KC_BSPC)
#define FN3_C       LT(3, KC_C)
#define FN4_V       LT(4, KC_V)
#define FN5_B       LT(5, KC_B)
#define CTL_Z       CTL_T(KC_Z)
#define ALT_X       ALT_T(KC_X)
#define ALT_N       ALGR_T(KC_N)
#define CTL_M       RCTL_T(KC_M)
#define SFT_ENT     RSFT_T(KC_ENT)
#define LAYER_CHG   MT(TO_DEF_LAYER, TO_UP_LAYER) /* MTを使ってもレイヤー切り替えがうまくいかない */
#define CTL_ESC     RCTL_T(KC_ESC)
#define WIN_ZKHK    LWIN(KC_ZKHK) /* WINキーへの切り替えがうまくいかない */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base QWERTY key map */
  [CL_BASE] = LAYOUT_ortho_3x10_inv(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    CTL_ESC,
    KC_Z,    KC_X,    KC_C,    KC_V,   FN1_SPC,  LAYER_CHG, KC_B,   KC_N,   KC_M,   SFT_ENT
  ),

  /* Mainly to support Japanese input */
  [CL_JP] = LAYOUT_ortho_3x10_inv(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
    _______, KC_ZKHK, _______, _______, _______, _______, _______, _______, _______, KC_BSPACE
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

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(D5);
  setPinOutput(B0);
}

void led_set_user(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
    writePinLow(D5);
  } else {
    writePinHigh(D5);
  }

  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinLow(B0);
  } else {
    writePinHigh(B0);
  }
}


bool process_record_user(uint16_t keycode, keyrecord_t * record)
{
  uint8_t   highest_layer;
  uint8_t   i;

  if (record->event.pressed) {
    switch (keycode) {
      case TO_UP_LAYER:
        /* get the current layer id */
        highest_layer = get_highest_layer(layer_state);
        if (highest_layer < (uint8_t)(CL_END - 1U)) {
          /* increment & turn on the layer above */
          layer_on(highest_layer + 1U);
        }
        return false;
        // break;

      case TO_LO_LAYER:
        /* get the current layer id */
        highest_layer = get_highest_layer(layer_state);
        if (highest_layer > (uint8_t)CL_BASE) {
            /* just disable the current layer */
            layer_off(highest_layer);
        }
        return false;
        // break;

      case TO_DEF_LAYER:
        /* disable all higher layers -> go back to base layer */
        for (i=(uint8_t)CL_BASE + 1; i<CL_END; i++) {
          layer_off(i);
        }
        return false;
        // break;

      default:
        break;
    }
  }
  return true;
}
