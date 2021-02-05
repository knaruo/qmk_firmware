#include "split_util.h"
#include "matrix.h"
#include "keyboard.h"
#include "config.h"
#include "timer.h"
#include "transport.h"
#include "quantum.h"
#include "wait.h"

#ifdef PROTOCOL_LUFA
#    include <LUFA/Drivers/USB/USB.h>
#endif

#ifdef PROTOCOL_VUSB
#    include "usbdrv.h"
#endif

#ifdef EE_HANDS
#    include "eeconfig.h"
#endif

#if defined(RGBLIGHT_ENABLE) && defined(RGBLED_SPLIT)
#    include "rgblight.h"
#endif

#ifndef SPLIT_USB_TIMEOUT
#    define SPLIT_USB_TIMEOUT 2000
#endif

#ifndef SPLIT_USB_TIMEOUT_POLL
#    define SPLIT_USB_TIMEOUT_POLL 10
#endif

#ifdef PROTOCOL_CHIBIOS
#    define SPLIT_USB_DETECT  // Force this on for now
#endif

volatile bool isLeftHand = true;

#ifdef SPLIT_HAND_MATRIX_GRID
void matrix_io_delay(void);

static uint8_t peek_matrix_intersection(pin_t out_pin, pin_t in_pin) {
    setPinInputHigh(in_pin);
    setPinOutput(out_pin);
    writePinLow(out_pin);
    // It's almost unnecessary, but wait until it's down to low, just in case.
    wait_us(1);
    uint8_t pin_state = readPin(in_pin);
    // Set out_pin to a setting that is less susceptible to noise.
    setPinInputHigh(out_pin);
    matrix_io_delay(); // Wait for the pull-up to go HIGH.
    return pin_state;
}
#endif

__attribute__((weak)) bool is_keyboard_left(void) {
    return eeconfig_read_handedness();
#if defined(SPLIT_HAND_PIN)
    // Test pin SPLIT_HAND_PIN for High/Low, if low it's right hand
    // setPinInputHigh(SPLIT_HAND_PIN);
    setPinInput(SPLIT_HAND_PIN);
    return readPin(SPLIT_HAND_PIN);
#elif defined(EE_HANDS)
    return eeconfig_read_handedness();
#endif
    return true;
}

__attribute__((weak)) bool is_keyboard_master(void) {
    static enum { UNKNOWN, MASTER, SLAVE } usbstate = UNKNOWN;

    // only check once, as this is called often
    if (usbstate == UNKNOWN) {
        usbstate = is_keyboard_left() ? MASTER : SLAVE;
    }

    return (usbstate == MASTER);
}

// this code runs before the keyboard is fully initialized
void split_pre_init(void) {
    isLeftHand = is_keyboard_left();

#if defined(RGBLIGHT_ENABLE) && defined(RGBLED_SPLIT)
    uint8_t num_rgb_leds_split[2] = RGBLED_SPLIT;
    if (isLeftHand) {
        rgblight_set_clipping_range(0, num_rgb_leds_split[0]);
    } else {
        rgblight_set_clipping_range(num_rgb_leds_split[0], num_rgb_leds_split[1]);
    }
#endif

    if (is_keyboard_master()) {
#if defined(USE_I2C) && defined(SSD1306OLED)
        matrix_master_OLED_init();
#endif
        transport_master_init();
    }
}

// this code runs after the keyboard is fully initialized
//   - avoids race condition during matrix_init_quantum where slave can start
//     receiving before the init process has completed
void split_post_init(void) {
    if (!is_keyboard_master()) {
        transport_slave_init();
    }
}
