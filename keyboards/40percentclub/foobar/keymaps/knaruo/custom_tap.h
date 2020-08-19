#include QMK_KEYBOARD_H


typedef struct {
    bool is_press_action;
    uint8_t state;
} custom_tap_t;


// Define a type for as many tap dance states as you need
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_SINGLE_TAP,
    DOUBLE_HOLD,
    TRIPLE_TAP,
    TRIPLE_HOLD,
};


// Function associated with all tap dances
uint8_t cur_dance(qk_tap_dance_state_t *state);
