#include QMK_KEYBOARD_H


typedef struct {
    bool is_press_action;
    uint8_t state;
} custom_tap_t;


// Define a type for as many tap dance states as you need
enum {
    SINGLE_TAP = 1, // 単押し
    SINGLE_HOLD, // 単純に長押し
    DOUBLE_TAP,
    DOUBLE_SINGLE_TAP, // double tap後に他のキーで邪魔されたときのコード
    DOUBLE_HOLD, // tap後に長押しする
    TRIPLE_TAP,
    TRIPLE_HOLD,  // double tap後に長押しする
};


// Function associated with all tap dances
uint8_t cur_dance(qk_tap_dance_state_t *state);
