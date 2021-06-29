/* Copyright 2021 Nick Brassel (@tzarc)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include <string.h>
#include <printf.h>
#include "Print.h"
#include <backlight.h>
#include <qp.h>

#define MEDIA_KEY_DELAY 4


enum { _QWERTY,_GAME, _LOWER, _RAISE, _ADJUST };


enum
{
    PT_RUN = SAFE_RANGE,
    KC_NXTWD,
    KC_PRVWD,
    KC_EMOJI,

    KC_GAME,
    KC_DEFAULT,

    KC_RSE,
    KC_LWR,
    KC_ADJ

};


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_all(
        KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,                           KC_DEL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,                          KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME,                          KC_PGUP, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_END,                           KC_PGDN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_EMOJI,
                                   KC_LGUI, KC_LALT, KC_LWR,  KC_ENT,                            KC_SPC,  KC_RSE, KC_RCTL, KC_LALT,
                                                                      KC_MPLY,         _______,
                                                     KC_UP,                                              KC_UP,
                                            KC_PRVWD, _______, KC_NXTWD,                         KC_LEFT, _______, KC_RIGHT,
                                                     KC_DOWN,                                            KC_DOWN
    ),
    [_GAME] = LAYOUT_all(
        KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,                           KC_DEL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,                          KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME,                          KC_PGUP, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_END,                           KC_PGDN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_EMOJI,
                                   KC_LGUI, KC_LALT, KC_LWR,  KC_SPC,                            KC_ENT,  KC_RSE, KC_RCTL, KC_LALT,
                                                                      KC_MPLY,         _______,
                                                     KC_UP,                                              KC_UP,
                                            KC_PRVWD, _______, KC_NXTWD,                         KC_LEFT, _______, KC_RIGHT,
                                                     KC_DOWN,                                            KC_DOWN
    ),
    [_LOWER] = LAYOUT_all(
        KC_BSLS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,                         _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______, KC_F12,
        _______, _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______, _______,
        _______, KC_EQL, _______, _______, _______, _______, _______,                         _______, _______, _______, _______,  _______, _______, _______,
                                   _______, _______, _______, _______,                         _______, _______, _______, _______,
                                                                     BL_DEC,             BL_INC,
                                                     _______,                                           KC_MPLY,
                                            _______, _______, _______,                         KC_MPRV, _______, KC_MNXT,
                                                     _______,                                           _______
    ),
    [_RAISE] = LAYOUT_all(
        KC_NUBS, KC_F1,   KC_F2,   KC_F3,   KC_F4  , KC_F5 , _______,                          _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        CK_TOGG, KC_INS,  KC_PSCR, KC_APP , PT_RUN , KC_F14, _______,                          _______, _______, KC_PRVWD,KC_UP  , KC_NXTWD, _______, KC_F12,
        _______, _______, _______, _______, _______, KC_UNDS, KC_NO,                           KC_NO,   KC_EQL,  KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,
        _______, KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, KC_MINS, KC_NO,                           KC_NO,   KC_PLUS, KC_HOME, _______, KC_END, _______, _______,
                                   _______, _______, _______, _______,                         _______, _______, _______, _______,
                                                                     _______,           _______,
                                                     _______,                                           _______,
                                            RGB_RMOD, _______, RGB_MOD,                         _______, _______, _______,
                                                     _______,                                           _______
    ),
    [_ADJUST] = LAYOUT_all(
        _______, KC_CLCK, KC_NLCK, KC_SLCK, _______, _______, _______,                         _______, _______, _______, _______, DEBUG,   EEP_RST, RESET,
        _______, _______, _______, _______, _______, _______, KC_DEFAULT,                      KC_GAME, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______,                         _______, _______, _______, _______,
                                                                     _______,           _______,
                                                     _______,                                           _______,
                                            _______, _______, _______,                         _______, _______, _______,
                                                     _______,                                           _______
    )




};
// clang-format on

static bool request_update = false;

void encoder_update_user(int8_t index, bool clockwise) {
    uint8_t temp_mod = get_mods();
    uint8_t temp_osm = get_oneshot_mods();
    bool    is_ctrl  = (temp_mod | temp_osm) & MOD_MASK_CTRL;
    bool    is_shift = (temp_mod | temp_osm) & MOD_MASK_SHIFT;

    if (is_shift) {
        if (index == 0) { /* First encoder */
            if (clockwise) {
                unregister_mods(mod_config(MOD_LSFT));
                tap_code16(KC_MS_WH_DOWN);
                register_mods(mod_config(MOD_LSFT));

            } else {
                unregister_mods(mod_config(MOD_LSFT));
                tap_code16(KC_MS_WH_UP);
                register_mods(mod_config(MOD_LSFT));
            }
        } else if (index == 1) { /* Second encoder */
            if (clockwise) {
                rgblight_decrease_sat();
            } else {
                rgblight_increase_sat();
            }
        }
    } else if (is_ctrl) {
        if (index == 0) { /* First encoder */
            if (clockwise) {
                rgblight_increase_val();
            } else {
                rgblight_decrease_val();
            }
        } else if (index == 1) { /* Second encoder */
            if (clockwise) {
                rgblight_increase_speed();
            } else {
                rgblight_decrease_speed();
            }
        }
    } else {
        if (index == 0) { /* First encoder */
            if (clockwise) {
                rgblight_increase_hue();
            } else {
                rgblight_decrease_hue();
            }
        } else if (index == 1) { /* Second encoder */
            uint16_t held_keycode_timer = timer_read();
            uint16_t mapped_code        = 0;
            if (clockwise) {
                mapped_code = KC_VOLD;
            } else {
                mapped_code = KC_VOLU;
            }
            register_code(mapped_code);
            while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY)
                ; /* no-op */
            unregister_code(mapped_code);
        }
    }
}

//----------------------------------------------------------
// Display

// #include "graphics/src/djinn.c"

#include "graphics/src/bg.c"
#include "graphics/src/lock-caps-ON.c"
#include "graphics/src/lock-scrl-ON.c"
#include "graphics/src/lock-num-ON.c"
#include "graphics/src/lock-caps-OFF.c"
#include "graphics/src/lock-scrl-OFF.c"
#include "graphics/src/lock-num-OFF.c"
#include "graphics/src/uni.c"

void draw_ui_user(void) {
    bool            redraw_required = false;
    static uint16_t last_hue        = 0xFFFF;
    uint8_t         curr_hue        = rgblight_get_hue();
    if (last_hue != curr_hue) {
        last_hue        = curr_hue;
        redraw_required = true;
    }

    if (redraw_required) {
        qp_drawimage(lcd, 0, 0, gfx_bg);
    }

    // Show layer info on the left side
    if (is_keyboard_left()) {
        static uint32_t last_layer_state = 0;
        static uint32_t last_default_layer_state = 0;

        if (redraw_required
                || last_layer_state != layer_state
                || last_default_layer_state != default_layer_state
                ) {
            last_layer_state = layer_state;
            last_default_layer_state = default_layer_state;

            const char *layer_name = "unknown";
            switch (get_highest_layer(layer_state)) {
                case _QWERTY:
                case _GAME:
                    layer_name = "Default";
                    break;
                case _LOWER:
                    layer_name = "Lower";
                    break;
                case _RAISE:
                    layer_name = "Raise";
                    break;
                case _ADJUST:
                    layer_name = "Adjust";
                    break;
            }

            const char *def_layer_name = "unknown";
            switch (get_highest_layer(default_layer_state)) {
                case _QWERTY:
                    def_layer_name = "Default";
                    break;
                case _GAME:
                    def_layer_name = "GAME";
                    break;
            }


            static int max_xpos = 0;
            int        xpos     = 16;
            int        ypos     = 4;
            char       buf[32]  = {0};

            snprintf_(buf, sizeof(buf), "Layer: %s", layer_name);
            xpos = qp_drawtext_recolor(lcd, xpos, ypos, font_uni, buf, curr_hue, 255, 255, curr_hue, 255, 0);


            if (max_xpos < xpos) {
                max_xpos = xpos;
            }
            ypos += 4 + font_uni->glyph_height;
            xpos = 16;

            snprintf_(buf, sizeof(buf), "Mode: %s", def_layer_name);
            xpos = qp_drawtext_recolor(lcd, xpos, ypos, font_uni, buf, curr_hue, 255, 255, curr_hue, 255, 0);

            if (max_xpos < xpos) {
                max_xpos = xpos;
            }
            ypos += 4 + font_uni->glyph_height;
        }

        static uint32_t last_screen_update = 0;
        if (redraw_required || timer_elapsed32(last_screen_update) > 250) {
            last_screen_update = timer_read32();

            static int max_xpos = 0;
            int        xpos     = 16;
            int        ypos     = 4+(4+font_uni->glyph_height)*2;
            char       buf[32]  = {0};

            snprintf_(buf, sizeof(buf), "Power: %s", usbpd_str(kb_state.current_setting));
            xpos = qp_drawtext_recolor(lcd, xpos, ypos, font_uni, buf, curr_hue, 255, 255, curr_hue, 255, 0);

            if (max_xpos < xpos) {
                max_xpos = xpos;
            }
            ypos += 4 + font_uni->glyph_height;

            xpos = 16;
            snprintf_(buf, sizeof(buf), "WPM: %03u", (int)get_current_wpm());
            xpos = qp_drawtext_recolor(lcd, xpos, ypos, font_uni, buf, curr_hue, 255, 255, curr_hue, 255, 0);

            if (max_xpos < xpos) {
                max_xpos = xpos;
            }
            ypos += 4 + font_uni->glyph_height;
        }
    }

    // Show LED lock indicators on the right side
    if (!is_keyboard_left()) {
        static led_t last_led_state = {0};
        if (redraw_required || last_led_state.raw != host_keyboard_led_state().raw) {
            last_led_state.raw = host_keyboard_led_state().raw;
            qp_drawimage_recolor(lcd, 239 - 12 - (32 * 3), 0, last_led_state.caps_lock ? gfx_lock_caps_ON : gfx_lock_caps_OFF, curr_hue, 255, last_led_state.caps_lock ? 255 : 32);
            qp_drawimage_recolor(lcd, 239 - 12 - (32 * 2), 0, last_led_state.num_lock ? gfx_lock_num_ON : gfx_lock_num_OFF, curr_hue, 255, last_led_state.num_lock ? 255 : 32);
            qp_drawimage_recolor(lcd, 239 - 12 - (32 * 1), 0, last_led_state.scroll_lock ? gfx_lock_scrl_ON : gfx_lock_scrl_OFF, curr_hue, 255, last_led_state.scroll_lock ? 255 : 32);
        }
    }
}



float songQwerty[][2] = SONG(QWERTY_SOUND);
float songWorkman[][2] = SONG(WORKMAN_SOUND);


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        case KC_EMOJI:
        if (record->event.pressed){
            tap_code16(G(KC_DOT));
        }
        return false;

        case PT_RUN:
        if(record->event.pressed){
            tap_code16(A(KC_F13));
        }
        break;

        case KC_DEFAULT:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
                request_update = true;
                PLAY_SONG(songQwerty);

            }
            return false;

        case KC_GAME:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_GAME);
                request_update = true;
                PLAY_SONG(songWorkman);
            }
            return false;
        case KC_LWR:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RSE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_ADJ:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case KC_COPY:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
        case KC_PASTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
            }
            return false;
        case KC_CUT:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
            break;
        case KC_UNDO:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;


        case KC_PRVWD:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_LEFT);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_LEFT);
            }
            break;
        case KC_NXTWD:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_RIGHT);

            } else {

                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_RIGHT);

            }
            break;
    }

    return true;
}
