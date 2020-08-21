#include QMK_KEYBOARD_H
#include "quantum.h"


#define KC_J_UNDS   S(KC_INT1)
#define KC_J_BSLS   KC_INT1 /* JIS \_ */

enum combo_event {
    KL_UNDS_COMBO,
    KL_DOT_COMBO,
    KL_COMM_COMBO,
    KL_MINUS_COMBO,
    KL_TAB_COMBO,
    KL_DEL_COMBO,
    KL_CLN_COMBO,
    KL_SLSH_COMBO,
    KL_SCLN_COMBO,
    KL_TAB2_COMBO,
};

const uint16_t PROGMEM unds_combo[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM dot_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM comm_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM minus_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM cln_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM slsh_combo[] = {KC_B, KC_N, COMBO_END};
const uint16_t PROGMEM scln_combo[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM tab_combo2[] = {KC_EQL, KC_JYEN, COMBO_END};

// Register the combo action
combo_t key_combos[COMBO_COUNT] = {
    [KL_UNDS_COMBO] = COMBO_ACTION(unds_combo),
    [KL_DOT_COMBO] = COMBO_ACTION(dot_combo),
    [KL_COMM_COMBO] = COMBO_ACTION(comm_combo),
    [KL_MINUS_COMBO] = COMBO_ACTION(minus_combo),
    [KL_TAB_COMBO] = COMBO_ACTION(tab_combo),
    [KL_DEL_COMBO] = COMBO_ACTION(del_combo),
    [KL_CLN_COMBO] = COMBO_ACTION(cln_combo),
    [KL_SLSH_COMBO] = COMBO_ACTION(slsh_combo),
    [KL_SCLN_COMBO] = COMBO_ACTION(scln_combo),
    [KL_TAB2_COMBO] = COMBO_ACTION(tab_combo2),
};

// Called after a combo event is triggered
void process_combo_event(uint8_t combo_index, bool pressed) {
    switch (combo_index) {
        case KL_UNDS_COMBO:
            if (pressed) {
                register_code(KC_J_BSLS);
            } else {
                unregister_code(KC_J_BSLS);
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
        case KL_TAB2_COMBO:
            if (pressed) {
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case KL_DEL_COMBO:
            if (pressed) {
                register_code(KC_DEL);
            } else {
                unregister_code(KC_DEL);
            }
            break;
        case KL_CLN_COMBO:
            if (pressed) {
                register_code(KC_QUOT);
            } else {
                unregister_code(KC_QUOT);
            }
            break;
        case KL_SLSH_COMBO:
            if (pressed) {
                register_code(KC_SLSH);
            } else {
                unregister_code(KC_SLSH);
            }
            break;
        case KL_SCLN_COMBO:
            if (pressed) {
                register_code(KC_SCLN);
            } else {
                unregister_code(KC_SCLN);
            }
            break;
        default:
            break;
    }
}
