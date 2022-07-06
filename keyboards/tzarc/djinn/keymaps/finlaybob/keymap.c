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
#include "print.h"

#include <backlight.h>
#include <qp.h>

#include "debug.h"


#include "p.h"

#define MEDIA_KEY_DELAY 6


enum { _QWERTY,_GAME,_LOWER, _RAISE, _ADJUST, _PW };


enum
{
    KC_AF13 = SAFE_RANGE,
    KC_NXTWD,
    KC_PRVWD,
    KC_EMOJI,

    KC_GAME,
    KC_DEFAULT,

    KC_RSE,
    KC_LWR,
    KC_ADJ,

    KC_ARRW,

    KC_LTTH, //Left Thumb
    KC_RGTH,  //Right Thumb

    KC_PWDL,
    KC_PW1,
    KC_PW2,
    KC_PW3,
    KC_PW4,


};


int16_t KC_LTTH_KEY = KC_ENT;
int16_t KC_RGTH_KEY = KC_SPC;
int8_t thumb_mode = _QWERTY;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_all(
        KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,                           KC_DEL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,                          KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_BTN1,                          KC_PGUP, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_BTN2,                           KC_PGDN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                   KC_LGUI, KC_LALT, KC_LWR,  KC_LTTH,                          KC_RGTH,  KC_RSE, KC_RCTL, KC_EMOJI,
                                                                      KC_MPLY,         _______,
                                                     A(KC_UP),                                           KC_UP,
                                            KC_MS_BTN4, KC_SPC, KC_MS_BTN5,                     KC_LEFT, KC_SPC, KC_RIGHT,
                                                     A(KC_DOWN),                                          KC_DOWN
    ),
    [_LOWER] = LAYOUT_all(
        KC_BSLS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,                         _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______, KC_F12,
        _______, _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______, _______,
        _______, KC_EQL,  _______, _______, _______, _______, _______,                         _______, _______, _______, _______,  KC_ARRW, _______, _______,
                                   _______, _______, _______, _______,                         _______, _______, _______, _______,
                                                                     BL_DEC,             BL_INC,
                                                     _______,                                           RGB_MOD,
                                            _______, _______, _______,                         KC_MPRV, _______, KC_MNXT,
                                                     _______,                                           RGB_RMOD
    ),
    [_RAISE] = LAYOUT_all(
        KC_BSLS, KC_F1,   KC_F2,   KC_F3,   KC_F4  , KC_F5 , _______,                          _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, KC_INS,  KC_PSCR, KC_APP , KC_AF13 , KC_F14, KC_F15,                          _______, _______, KC_PRVWD,KC_UP  , KC_NXTWD, _______, KC_F12,
        _______, _______, _______, _______, _______, KC_UNDS, KC_NO,                           KC_NO,   KC_EQL,  KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,
        _______, _______, _______, _______, _______, KC_MINS, KC_NO,                           KC_NO,   KC_PLUS, KC_HOME, _______, KC_END, _______, _______,
                                   _______, _______, _______, _______,                         _______, _______, _______, _______,
                                                                     _______,           _______,
                                                     _______,                                           _______,
                                            _______, _______, _______,                         _______, _______, _______,
                                                     _______,                                           _______
    ),
    [_ADJUST] = LAYOUT_all(
        KC_NUBS, KC_CLCK, KC_NLCK, KC_SLCK, KC_F16, KC_F17, KC_F18,                            _______, _______, _______, _______, DEBUG,   EEP_RST, RESET,
        _______, _______, _______, _______, _______, _______, KC_DEFAULT,                      KC_GAME, _______, _______, _______, _______, KC_PWDL, _______,
        _______, _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______,                         _______, _______, _______, _______,
                                                                     _______,           _______,
                                                     _______,                                           _______,
                                            _______, _______, _______,                         _______, _______, _______,
                                                     _______,                                           _______
    ),
    [_PW] = LAYOUT_all(
        _______, KC_PW1, KC_PW2, KC_PW3, KC_PW4, _______, _______,                         _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______, _______,
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

    bool    is_raise = IS_LAYER_ON(_RAISE);


    if (is_shift) {
        if (index == 0) { /* First encoder */
            if (clockwise) {
                rgblight_increase_hue();
            } else {
                rgblight_decrease_hue();
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
        if (index == 1) { /* First encoder */
            if (clockwise) {
                tap_code16(KC_DOWN);
            } else {
                tap_code16(KC_UP);
            }
        } else if (index == 0) { /* Second encoder */
            if(is_raise){
                if (clockwise) {
                    tap_code(KC_RIGHT);
                } else {
                    tap_code(KC_LEFT);
                }
            }else{
                uint16_t held_keycode_timer = timer_read();
                uint16_t mapped_code        = 0;
                if (clockwise) {
                    mapped_code = KC_VOLU;
                } else {
                    mapped_code = KC_VOLD;
                }
                register_code(mapped_code);
                while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY)
                    ; /* no-op */
                unregister_code(mapped_code);
            }
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
    if (!is_keyboard_left()) {
        static uint32_t last_layer_state = 0;
        static uint16_t last_thumb_mode = 0;

        if (redraw_required
                || last_layer_state != layer_state
                || last_thumb_mode != thumb_mode
                ) {
            last_layer_state = layer_state;
            last_thumb_mode = thumb_mode;

            const char *layer_name = "unknown";
            switch (get_highest_layer(layer_state)) {
                case _QWERTY:
                    layer_name = "Default  ";
                    break;
                case _LOWER:
                    layer_name = "Lower    ";
                    break;
                case _RAISE:
                    layer_name = "Raise    ";
                    break;
                case _ADJUST:
                    layer_name = "Adjust   ";
                    break;
                case _PW:
                    layer_name = "PASSWORD!";
                    break;
            }

            const char *def_layer_name = "unknown";
            if (thumb_mode == _QWERTY) {
                def_layer_name = "Default ";
            }
            else
            {
                def_layer_name = "  GAME  ";
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
            
            dprintf("Doing redraw");
            
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

        static led_t last_led_state = {0};
        if (redraw_required || last_led_state.raw != host_keyboard_led_state().raw) {
            last_led_state.raw = host_keyboard_led_state().raw;
            qp_drawimage_recolor(lcd, (32 * 0), 319-32, last_led_state.caps_lock ? gfx_lock_caps_ON : gfx_lock_caps_OFF, curr_hue, 255, last_led_state.caps_lock ? 255 : 32);
            qp_drawimage_recolor(lcd, (32 * 1), 319-32, last_led_state.num_lock ? gfx_lock_num_ON : gfx_lock_num_OFF, curr_hue, 255, last_led_state.num_lock ? 255 : 32);
            qp_drawimage_recolor(lcd, (32 * 2), 319-32, last_led_state.scroll_lock ? gfx_lock_scrl_ON : gfx_lock_scrl_OFF, curr_hue, 255, last_led_state.scroll_lock ? 255 : 32);
        }
    }

    // Show LED lock indicators on the right side
    

    
}



float songDef[][2] = SONG(AUDIO_OFF_SOUND);
float songGame[][2] = SONG(AUDIO_ON_SOUND);
float songPw[][2] = SONG(S__NOTE(_C4), S__NOTE(_C5),);
float songPwLayer[][2] = SONG(E__NOTE(_A2), E__NOTE(_C3),E__NOTE(_DS3),E__NOTE(_A3),E__NOTE(_DS3),);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {

        case KC_LTTH:
        if(record->event.pressed)
        {
            register_code(KC_LTTH_KEY);
        }
        else
        {
            unregister_code(KC_LTTH_KEY);
        }
        return false;

        case KC_RGTH:
        if(record->event.pressed)
        {
            register_code(KC_RGTH_KEY);
        }
        else
        {
            unregister_code(KC_RGTH_KEY);
        }
        return false;

        case KC_ARRW:
        if(record->event.pressed){
            tap_code(KC_EQL);
            register_mods(mod_config(MOD_LSFT));
            tap_code(KC_DOT);
            unregister_mods(mod_config(MOD_LSFT));
        }
        return false;

        case KC_EMOJI:
        if (record->event.pressed){
            tap_code16(G(KC_DOT));
        }
        return false;

        case KC_AF13:
        if(record->event.pressed){
            tap_code16(A(KC_F13));

        }
        break;
        
        case KC_PWDL:
        if (record->event.pressed){
            layer_on(_PW);
            PLAY_SONG(songPwLayer);
        } else {
            layer_off(_PW);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        
        
        case KC_PW1:
        if (record->event.pressed){
            PLAY_SONG(songPw);
            send_string(PASSWD1);
        }
        return false;

        case KC_PW2:
        if (record->event.pressed){
            PLAY_SONG(songPw);
            send_string(PASSWD2);
        }
        return false;

        case KC_PW3:
        if (record->event.pressed){
            PLAY_SONG(songPw);
            send_string(PASSWD3);
        }
        return false;
        case KC_PW4:
        if (record->event.pressed){
            PLAY_SONG(songPw);
            send_string(PASSWD4);
        }
        return false;

        case KC_DEFAULT:
            if (record->event.pressed) {
                KC_LTTH_KEY = KC_ENT;
                KC_RGTH_KEY = KC_SPC;
                thumb_mode = _QWERTY;
                request_update = true;
                PLAY_SONG(songDef);
            }
            return false;

        case KC_GAME:
            if (record->event.pressed) {
                KC_LTTH_KEY = KC_SPC;
                KC_RGTH_KEY = KC_ENT;
                thumb_mode = _GAME;
                request_update = true;
                PLAY_SONG(songGame);
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

extern void kb_state_sync(void);

void suspend_power_down_user() {
    kb_state.lcd_power = 0;
    qp_power(lcd,0);
    backlight_disable();
    kb_state_sync();
    wait_ms(50);
}

void suspend_wakeup_init_user(){
    kb_state.lcd_power = 1;
    qp_power(lcd,1);
    backlight_enable();
    kb_state_sync();
    wait_ms(50);
}
