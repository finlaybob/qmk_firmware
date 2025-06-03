// Copyright © 2025 Neil Finlay <finbsp@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "display.h"
#include "enums.h"
#include <printf.h>

void keyboard_post_init_kb(void) {
    display_startup();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
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

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    // static uint32_t last_task_print_time = 0; // Keep this specific to the task
    // if (timer_elapsed32(last_task_print_time) > 2000) { // Print every 2 seconds
    //     printf("Nessie pointing device task running (from nessie.c task V2).\n");
    //     last_task_print_time = timer_read32();
    // }
    return mouse_report;
}

