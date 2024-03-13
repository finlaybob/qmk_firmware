// Copyright ©️ 2024 Neil Finlay

#pragma once

#define SPI_DRIVER SPID0

#undef SPI_SCK_PIN
#define SPI_SCK_PIN GP2

#undef SPI_MOSI_PIN
#define SPI_MOSI_PIN GP3

#undef SPI_MISO_PIN
#define SPI_MISO_PIN GP4

#define DISP_CS_PIN GP5
#define DISP_DC_PIN GP6
#define DISP_RST_PIN GP7

#define DISP_TIMEOUT 30000

// #define PIN_STATUS_LED GP25

// TODO - What the fuck, I can't get any backlightage
// #define BACKLIGHT_PIN GP8
// #define BACKLIGHT_LEVELS 10

#define PIN_LCD_POWER GP8

#define QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS TRUE

// TODO - What the fuck, I can't get any Trackpaddage
// #define POINTING_DEVICE_CS_PIN GP1
// // #define CIRQUE_PINNACLE_SPI_CS_PIN GP1
// #define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_RELATIVE_MODE

#ifdef POINTING_DEVICE_ENABLE
#    ifdef ENCODER_ENABLE
#        error "Cannot enable both encoder and trackpad"
#    endif
#endif

#ifdef ENCODER_ENABLE
#    ifdef POINTING_DEVICE_ENABLE
#        error "Cannot enable both encoder and trackpad"
#    endif

#    define ENCODERS_PAD_A \
        { GP0 }
#    define ENCODERS_PAD_B \
        { GP1 }

#    define ENCODER_RESOLUTION 2
#endif

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

// #define DEBUG_MATRIX_SCAN_RATE 1