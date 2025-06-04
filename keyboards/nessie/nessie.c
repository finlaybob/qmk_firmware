// Copyright © 2025 Neil Finlay <finbsp@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


#include "display.h"
#include "enums.h"
#include <printf.h>

static uint32_t idle_time = 0;
static bool backlight_active = true;

static bool bl_last_state;
static bool bl_last_brtg;
static uint8_t bl_last_level = 0;



void keyboard_post_init_kb(void) {
    display_startup();
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
    // Call the user processing function.
    if (keycode == CUSTOM_P && record->event.pressed) {
        // Custom keycode action
        printf("Custom P key pressed!\n");
        printf("nd_hue: %hhu", nd_hue);
        nd_hue = (nd_hue + 10) % 256; // Cycle hue
        nd_dirty = true; // Mark the display as dirty to trigger a redraw

        // You can add more actions here if needed
    }
    return process_record_user(keycode, record);
}

void housekeeping_task_user(void) {
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

// report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
//     return mouse_report;
// }

