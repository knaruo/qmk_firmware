#include QMK_KEYBOARD_H
#include "quantum.h"


#define KC_J_BSLS   KC_INT1 /* JIS \_ */

enum combo_event {
    KL_ZKHK_COMBO,
};

const uint16_t PROGMEM zkhk_combo[] = {KC_S, KC_D, COMBO_END};

// Register the combo action
combo_t key_combos[COMBO_COUNT] = {
    [KL_ZKHK_COMBO] = COMBO(zkhk_combo, KC_ZKHK),
};

// Called after a combo event is triggered
void process_combo_event(uint8_t combo_index, bool pressed) {
    switch (combo_index) {
        default:
            break;
    }
}
