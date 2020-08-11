#include QMK_KEYBOARD_H
#include "quantum.h"


#define KC_J_UNDS   S(KC_INT1)

enum combo_event {
    KL_UNDS_COMBO,
    KL_DOT_COMBO,
    KL_COMM_COMBO,
    KL_MINUS_COMBO,
    KL_TAB_COMBO,
};

const uint16_t PROGMEM unds_combo[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM dot_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM comm_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM minus_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_A, KC_S, COMBO_END};

// Register the combo action
combo_t key_combos[COMBO_COUNT] = {
    [KL_UNDS_COMBO] = COMBO_ACTION(unds_combo),
    [KL_DOT_COMBO] = COMBO_ACTION(dot_combo),
    [KL_COMM_COMBO] = COMBO_ACTION(comm_combo),
    [KL_MINUS_COMBO] = COMBO_ACTION(minus_combo),
    [KL_TAB_COMBO] = COMBO_ACTION(tab_combo),
};

// Called after a combo event is triggered
void process_combo_event(uint8_t combo_index, bool pressed) {
    switch (combo_index) {
        case KL_UNDS_COMBO:
            if (pressed) {
                register_code16(KC_J_UNDS);
            } else {
                unregister_code16(KC_J_UNDS);
            }
            break;
        case KL_DOT_COMBO:
            if (pressed) {
                register_code(KC_DOT);
            } else {
                unregister_code(KC_DOT);
            }
            break;
        case KL_COMM_COMBO:
            if (pressed) {
                register_code(KC_COMM);
            } else {
                unregister_code(KC_COMM);
            }
            break;
        case KL_MINUS_COMBO:
            if (pressed) {
                register_code(KC_MINS);
            } else {
                unregister_code(KC_MINS);
            }
            break;
        case KL_TAB_COMBO:
            if (pressed) {
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        default:
            break;
    }
}
