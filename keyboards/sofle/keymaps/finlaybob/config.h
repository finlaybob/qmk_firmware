#pragma once

#define MASTER_RIGHT

#define RGB_DI_PIN D3

#ifdef RGB_DI_PIN
    #define RGBLIGHT_SPLIT

    // #define RGBLIGHT_ANIMATIONS
    #define RGBLIGHT_EFFECT_TWINKLE
    #define RGBLED_NUM 8
    #define RGBLIGHT_HUE_STEP 1
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17

    #define RGBLIGHT_SLEEP
#endif

#define RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 4
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
