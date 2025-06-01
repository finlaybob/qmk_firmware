// Copyright © 2025 Neil Finlay <finbsp@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "custom_keys.h"

void keyboard_post_init_kb(void) {

}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // Call the user processing function.
    if (keycode == KC_CKCP && record->event.pressed) {
        // Custom keycode action
        printf("Custom keycode KC_CKCP pressed!\n");
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

