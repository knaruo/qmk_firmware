#include QMK_KEYBOARD_H
#include "td_atab.h"
#include "custom_tap.h"


static custom_tap_t atab_tap_state = {
    .is_press_action = true,
    .state = 0
};


void atab_finished(qk_tap_dance_state_t *state, void *user_data){

    (void)user_data;

    atab_tap_state.state = cur_dance(state);
    switch (atab_tap_state.state) {
        case SINGLE_TAP:
            register_code(KC_A);
            break;
        case DOUBLE_TAP:
            register_code(KC_TAB);
            break;
        default:
          break;
    }

}


void atab_reset(qk_tap_dance_state_t *state, void *user_data){

    (void)state;
    (void)user_data;

    switch (atab_tap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_A);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_TAB);
            break;
        default:
          break;
    }
    atab_tap_state.state = 0;

}