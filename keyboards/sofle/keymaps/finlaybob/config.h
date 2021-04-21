#pragma once
#define MASTER_RIGHT
#ifdef RGBLIGHT_ENABLE
    #define RGB_DI_PIN D3
    #define RGBLIGHT_SPLIT

    #define RGBLED_NUM 8
    #define RGBLIGHT_HUE_STEP 1
    #define RGBLIGHT_SAT_STEP 9
    #define RGBLIGHT_VAL_STEP 9

    #define RGBLIGHT_SLEEP
#endif

// #define RGBLIGHT_LAYERS
// #define RGBLIGHT_MAX_LAYERS 5
// #define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
