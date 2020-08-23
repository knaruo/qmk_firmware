#include QMK_KEYBOARD_H
#include "quantum.h"


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
    KL_ESC_COMBO,
    KL_ZKHK_COMBO,
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
const uint16_t PROGMEM esc_combo[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM zkhk_combo[] = {KC_X, KC_C, COMBO_END};

// Register the combo action
combo_t key_combos[COMBO_COUNT] = {
    [KL_UNDS_COMBO] = COMBO(unds_combo, KC_J_BSLS),
    [KL_DOT_COMBO] = COMBO(dot_combo, KC_DOT),
    [KL_COMM_COMBO] = COMBO(comm_combo, KC_COMM),
    [KL_MINUS_COMBO] = COMBO(minus_combo, KC_MINS),
    [KL_TAB_COMBO] = COMBO(tab_combo, KC_TAB),
    [KL_DEL_COMBO] = COMBO(del_combo, KC_DEL),
    [KL_CLN_COMBO] = COMBO(cln_combo, KC_QUOT),
    [KL_SLSH_COMBO] = COMBO(slsh_combo, KC_SLSH),
    [KL_SCLN_COMBO] = COMBO(scln_combo, KC_SCLN),
    [KL_TAB2_COMBO] = COMBO(tab_combo2, KC_TAB),
    [KL_ESC_COMBO] = COMBO(esc_combo, KC_ESC),
    [KL_ZKHK_COMBO] = COMBO(zkhk_combo, KC_ZKHK),
};

// Called after a combo event is triggered
void process_combo_event(uint8_t combo_index, bool pressed) {
    switch (combo_index) {
        default:
            break;
    }
}
