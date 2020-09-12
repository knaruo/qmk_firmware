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
        case DOUBLE_TAP:
            register_code(KC_ESC);
            break;
        case SINGLE_HOLD:
            register_code(KC_LCTL);
            break;
        case SINGLE_TAP:
        default:
            register_code(KC_Q);
            break;
    }

}


void qesc_reset(qk_tap_dance_state_t *state, void *user_data){

    (void)state;
    (void)user_data;

    switch (qesc_tap_state.state) {
        case DOUBLE_TAP:
            unregister_code(KC_ESC);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LCTL);
            break;
        case SINGLE_TAP:
        default:
            unregister_code(KC_Q);
            break;
    }
    qesc_tap_state.state = 0;

}