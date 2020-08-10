#include QMK_KEYBOARD_H
#include "td_qesc.h"
#include "custom_tap.h"


static custom_tap_t qesc_tap_state = {
    .is_press_action = true,
    .state = 0
};


void qesc_finished(qk_tap_dance_state_t *state, void *user_data){

    (void)user_data;

    qesc_tap_state.state = cur_dance(state);
    switch (qesc_tap_state.state) {
        case SINGLE_TAP:
            register_code(KC_Q);
            break;
        case DOUBLE_TAP:
            register_code(KC_ESC);
            break;
        default:
          break;
    }

}


void qesc_reset(qk_tap_dance_state_t *state, void *user_data){

    (void)state;
    (void)user_data;

    switch (qesc_tap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_Q);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_ESC);
            break;
        default:
          break;
    }
    qesc_tap_state.state = 0;

}