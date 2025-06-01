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

#define SPI_DRIVER SPID0

#undef SPI_SCK_PIN
#define SPI_SCK_PIN GP2

#undef SPI_MOSI_PIN
#define SPI_MOSI_PIN GP3

#undef SPI_MISO_PIN
#define SPI_MISO_PIN GP4

#define TP_CS_PIN GP1

// READY pin seems unused by the Cirque driver,
// but when I've tried to use the trackpad
// without it on e.g. circuitpython, it doesn't work.
#define TP_READY_PIN GP0

#define POINTING_DEVICE_DEBUG

// #define DISP_CS_PIN GP5
// #define DISP_DC_PIN GP6
// #define DISP_RST_PIN GP7

// #define DISP_TIMEOUT 30000

#define POINTING_DEVICE_CS_PIN TP_CS_PIN

// #define CIRQUE_PINNACLE_SPI_DIVISOR 8 // Removed to use driver default (64)
#define CIRQUE_PINNACLE_SPI_LSBFIRST false
#define CIRQUE_PINNACLE_SPI_CS_PIN TP_CS_PIN
#define CIRQUE_PINNACLE_DIAMETER_MM 40
