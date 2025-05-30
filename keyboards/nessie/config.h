// Copyright © 2025 Neil Finlay <finbsp@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Double tap reset button to enter bootloader */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#ifdef BACKLIGHT_ENABLE
#   define BACKLIGHT_PWM_DRIVER PWMD4
#   define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_A
#endif
