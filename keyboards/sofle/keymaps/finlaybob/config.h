#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/

#define RGB_DI_PIN D3
#define RGBLIGHT_SPLIT
#ifdef RGB_DI_PIN
    // #define RGBLIGHT_ANIMATIONS
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLED_NUM 8
    #define RGBLIGHT_HUE_STEP 4
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8

    #define RGBLIGHT_SLEEP
#endif

#define RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 4
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF

