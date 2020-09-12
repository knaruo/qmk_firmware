#include QMK_KEYBOARD_H
#include "quantum.h"


#define KC_J_BSLS   KC_INT1 /* JIS \_ */

enum combo_event {
    KL_UNDS_COMBO,
    KL_DOT_COMBO,
    KL_COMM_COMBO,
    KL_DBLQUOT_COMBO,
    KL_ZKHK_COMBO,
};

const uint16_t PROGMEM unds_combo[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM dot_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM comm_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM dblquot_combo[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM zkhk_combo[] = {KC_S, KC_D, COMBO_END};

// Register the combo action
combo_t key_combos[COMBO_COUNT] = {
    [KL_UNDS_COMBO] = COMBO(unds_combo, KC_J_BSLS),
    [KL_DOT_COMBO] = COMBO(dot_combo, KC_DOT),
    [KL_COMM_COMBO] = COMBO(comm_combo, KC_COMM),
    [KL_DBLQUOT_COMBO] = COMBO(dblquot_combo, S(KC_2)),
    [KL_ZKHK_COMBO] = COMBO(zkhk_combo, KC_ZKHK),
};

// Called after a combo event is triggered
void process_combo_event(uint8_t combo_index, bool pressed) {
    switch (combo_index) {
        default:
            break;
    }
}
