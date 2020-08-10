#include QMK_KEYBOARD_H
#include "td_xzk.h"
#include "custom_tap.h"


static custom_tap_t xzk_tap_state = {
    .is_press_action = true,
    .state = 0
};


void xzk_finished(qk_tap_dance_state_t *state, void *user_data){

    (void)user_data;

    xzk_tap_state.state = cur_dance(state);
    switch (xzk_tap_state.state) {
        case SINGLE_TAP:
            register_code(KC_X);
            break;
        case DOUBLE_TAP:
        case DOUBLE_SINGLE_TAP:
            register_code(KC_X);
            register_code(KC_X);
            break;
        case SINGLE_HOLD:
            register_code(KC_LWIN);
            break;
        case TRIPLE_TAP:
            register_code(KC_ZKHK);
            break;
        default:
          break;
    }

}


void xzk_reset(qk_tap_dance_state_t *state, void *user_data){

    (void)state;
    (void)user_data;

    switch (xzk_tap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_X);
            break;
        case DOUBLE_TAP:
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_X);
            unregister_code(KC_X);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LWIN);
            break;
        case TRIPLE_TAP:
            unregister_code(KC_ZKHK);
            break;
        default:
          break;
    }
    xzk_tap_state.state = 0;

}
