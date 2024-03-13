// Copyright ©️ 2024 Neil Finlay

#include "quantum.h"
#include "display.h"
#include "enums.h"

#include "CKCPWD.h"

void keyboard_post_init_kb(void) {
#ifdef PIN_LCD_POWER
    setPinOutput(PIN_LCD_POWER);
    writePinHigh(PIN_LCD_POWER);
#endif

#ifdef PIN_STATUS_LED
    setPinOutput(PIN_STATUS_LED);
    writePinHigh(PIN_STATUS_LED);
#endif

    display_startup();
    keyboard_post_init_user();
}

static uint32_t last_time = 0;

// Pascal Getreuer's "Jiggler" macro
// https://getreuer.info/posts/keyboards/macros3/index.html#a-mouse-jiggler
uint32_t jiggler_callback(uint32_t trigger_time, void *cb_arg) {
    // Deltas to move in a circle of radius 20 pixels over 32 frames.
    static const int8_t deltas[32] = {0, -1, -2, -2, -3, -3, -4, -4, -4, -4, -3, -3, -2, -2, -1, 0, 0, 1, 2, 2, 3, 3, 4, 4, 4, 4, 3, 3, 2, 2, 1, 0};
    static uint8_t      phase      = 0;

    report_mouse_t *report = (report_mouse_t *)cb_arg;
    // Get x delta from table and y delta by rotating a quarter cycle.
    report->x = deltas[phase];
    report->y = deltas[(phase + 8) & 31];
    phase     = (phase + 1) & 31;
    host_mouse_send(report);
    return 16; // Call the callback every 16 ms.
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    last_time = timer_read32();
    switch (keycode) {
        case CUSTOM_P:
            if (record->event.pressed) {
                SEND_STRING(CKCP);
            }
            return false;
    }
    if (record->event.pressed) {
        static deferred_token mouse_jiggle_token = INVALID_DEFERRED_TOKEN;
        static report_mouse_t report             = {0};
        if (mouse_jiggle_token) {
            // If jiggler is currently running, stop when any key is pressed.
            cancel_deferred_exec(mouse_jiggle_token);
            mouse_jiggle_token = INVALID_DEFERRED_TOKEN;
            report             = (report_mouse_t){}; // Clear the mouse.
            host_mouse_send(&report);
        } else if (keycode == JIGGLE) {
            mouse_jiggle_token = defer_exec(1, jiggler_callback, &report); // Schedule callback.
        }
    }
    return process_record_user(keycode, record);

    return true;
}

void housekeeping_task_user(void) {
#ifdef PIN_LCD_POWER
    static bool on = false;

    if (timer_elapsed32(last_time) > DISP_TIMEOUT - 500) {
        writePinLow(PIN_LCD_POWER);
        on = false;
    } else {
        if (!on) {
            writePinHigh(PIN_LCD_POWER);
        }
    }
#endif
}

void suspend_power_down_user(void) {
#ifdef PIN_LCD_POWER
    writePinLow(PIN_LCD_POWER);
#endif
}

void suspend_wakeup_init_user(void) {
#ifdef PIN_LCD_POWER
    writePinHigh(PIN_LCD_POWER);
#endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
    nd_cur_layer = get_highest_layer(state);
    return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    nd_mode = get_highest_layer(state);
    return state;
}