// Copyright © 2025 Neil Finlay / thslkeys <finbsp@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define DEV_RIG

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#define DEBUG_MATRIX_SCAN_RATE

#ifdef BACKLIGHT_ENABLE
#    define BACKLIGHT_BREATHING
#    define BREATHING_PERIOD 10
#    define BACKLIGHT_PWM_DRIVER PWMD4
#    define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_A

//   multiple pins are not supported on hardware PWM
#    define BACKLIGHT_PIN GP8

#    undef BACKLIGHT_LEVELS
#    define BACKLIGHT_LEVELS 3

//   Forces the backlight to be enabled on boot
#    define BL_ENABLE_ON_BOOT

//   If BL_ENABLE_ON_BOOT is defined, this sets the backlight level on boot
//   MUST be between 0 and BACKLIGHT_LEVELS
#    define BL_LEVEL_ON_BOOT BACKLIGHT_LEVELS
#endif

#ifdef ENCODER_ENABLE
#    ifdef POINTING_DEVICE_ENABLE
#        error "Pointing device and encoder cannot be enabled at the same time."
#    endif
#    define ENCODER_RESOLUTION 2
#    define ENCODER_MAP_ENABLE
#endif

#undef QUANTUM_PAINTER_NUM_IMAGES
#define QUANTUM_PAINTER_NUM_IMAGES 32

#define DISP_CS_PIN GP5
#define DISP_DC_PIN GP6
#define DISP_RST_PIN GP7

#define SPI_DRIVER SPID0

#undef SPI_SCK_PIN
#undef SPI_MOSI_PIN
#undef SPI_MISO_PIN

#define SPI_SCK_PIN GP2
#define SPI_MOSI_PIN GP3
#define SPI_MISO_PIN GP4

#ifdef POINTING_DEVICE_ENABLE
#    ifdef ENCODER_ENABLE
#        error "Pointing device and encoder cannot be enabled at the same time."
#    endif

#    define TP_CS_PIN GP1
#    define TP_READY_PIN GP0 // UNUSED

#    define POINTING_DEVICE_CS_PIN TP_CS_PIN

// Ready pin is optional but not able to be used with inertial cursor
// #   define POINTING_DEVICE_MOTION_PIN TP_READY_PIN

#    define POINTING_DEVICE_DEBUG
#    define CIRQUE_PINNACLE_DIAMETER_MM 40
#    define CIRQUE_PINNACLE_TAP_ENABLE
#    define POINTING_DEVICE_HIRES_SCROLL_ENABLE
#    define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
#    define POINTING_DEVICE_HIRES_SCROLL_MULTIPLIER 20
#    define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
#endif // POINTING_DEVICE_ENABLE

#define BOOTMAGIC_ROW 6
#define BOOTMAGIC_COLUMN 0

#define _DEF 0
#define _GME 1
#define _COL 2
#define _LWR 3
#define _RSE 4
#define _ADJ 5
#define _CFG 6

#define TRI_LAYER_LOWER_LAYER _LWR
#define TRI_LAYER_UPPER_LAYER _RSE
#define TRI_LAYER_ADJUST_LAYER _ADJ
