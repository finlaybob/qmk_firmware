// Copyright © 2025 Neil Finlay / thslkeys <finbsp@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


#include "display.h"
#include "enums.h"
#include <printf.h>
#include "CKCP.h"

static uint32_t idle_time = 0;
static bool backlight_active = true;

static bool bl_last_state;
static bool bl_last_brtg;
static uint8_t bl_last_level = 0;

void keyboard_post_init_kb(void) {
    display_startup();
}

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
    return 250; // Call the callback every 250 ms.
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    idle_time = timer_read32();

#ifdef BACKLIGHT_ENABLE
    // Handle backlight state
    if (!backlight_active) {
        printf("restoring backlight state: %d, level: %d, breathing: %d\n", bl_last_state, bl_last_level, bl_last_brtg);

        backlight_active = true;

        if(bl_last_state) {
            backlight_enable();
            backlight_level(bl_last_level);
            if (bl_last_brtg) {
                backlight_enable_breathing();
            } else {
                backlight_disable_breathing();
            }

        }
    }
#endif

    switch (keycode) {
        case KC_CKCP:
            if (record->event.pressed) {
                SEND_STRING(CKCP);
            }
            return false;
        case KC_HUP:
            // if (record->event.pressed) {
            //     nd_hue   = (nd_hue + HUE_STEP) % 256; // Cycle hue
            //     nd_dirty = true;
            // }
            return true;
        case KC_HDN:
            // if (record->event.pressed) {
            //     if (nd_hue - HUE_STEP <= 0) {
            //         nd_hue = 256 - nd_hue - HUE_STEP;
            //     } else {
            //         nd_hue = (nd_hue - HUE_STEP);
            //     }
            //     nd_dirty = true;
            // }
            return true;
    }

    // If jiggler is currently running, stop when any key is pressed.
    if (record->event.pressed) {
        static deferred_token mouse_jiggle_token = INVALID_DEFERRED_TOKEN;
        static report_mouse_t report             = {0};
        if (mouse_jiggle_token) {
            cancel_deferred_exec(mouse_jiggle_token);
            mouse_jiggle_token = INVALID_DEFERRED_TOKEN;
            report             = (report_mouse_t){}; // Clear the mouse.
            host_mouse_send(&report);
        } else if (keycode == JIGGLE) {
            mouse_jiggle_token = defer_exec(1, jiggler_callback, &report); // Schedule callback.
        }
    }
    return process_record_user(keycode, record);
}


void housekeeping_task_kb(void) {
#ifdef BACKLIGHT_ENABLE
    if (timer_elapsed32(idle_time) > DISP_TIMEOUT - 500) {
        if(backlight_active) {
            bl_last_state = is_backlight_enabled();
            bl_last_level = get_backlight_level();
            bl_last_brtg = is_backlight_breathing();
            backlight_disable();
            backlight_active = false;
            printf("last_state: %d, last_level: %d, last_brtg: %d\n", bl_last_state, bl_last_level, bl_last_brtg);
            printf("Backlight disabled due to inactivity.\n");
        }
    }
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

