#include QMK_KEYBOARD_H
#include "quantum.h"


#define KC_J_UNDS   S(KC_INT1)

enum combo_event {
    KL_UNDS_COMBO,
};

const uint16_t PROGMEM unds_combo[] = {KC_N, KC_M, COMBO_END};

// Register the combo action
combo_t key_combos[COMBO_COUNT] = {
    [KL_UNDS_COMBO] = COMBO_ACTION(unds_combo),
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
        default:
            break;
    }
}
