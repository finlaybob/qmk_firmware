// Copyright © 2025 Neil Finlay <finbsp@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "display.h"
#include "enums.h"

void keyboard_post_init_kb(void) {
    display_startup();
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

    return mouse_report;
}

