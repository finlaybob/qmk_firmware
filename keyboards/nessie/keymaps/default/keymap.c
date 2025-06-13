// Copyright ©️ 2024 Neil Finlay
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#include "../../enums.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DEF] = LAYOUT(
        KC_ESC,        KC_1,    KC_2,     KC_3,    KC_4,     KC_5,     KC_6,     KC_7,      KC_8,             KC_9,             KC_0,         KC_MINUS,
        KC_TAB,        KC_Q,    KC_W,     KC_E,    KC_R,     KC_T,     KC_Y,     KC_U,      KC_I,             KC_O,             KC_P,         KC_BACKSPACE,
        KC_LEFT_CTRL,  KC_A,    KC_S,     KC_D,    KC_F,     KC_G,     KC_H,     KC_J,      KC_K,             KC_L,             KC_SEMICOLON, KC_QUOTE,
        KC_LEFT_SHIFT, KC_Z,    KC_X,     KC_C,    KC_V,     KC_B,     KC_N,     KC_M,      KC_COMMA,         KC_DOT,           KC_SLASH,     KC_RIGHT_SHIFT,
                           KC_DEL,  KC_LGUI,  KC_LALT, TL_LOWR,  KC_ENTER, KC_SPACE, TL_UPPR,   KC_LEFT_BRACKET,  KC_RIGHT_BRACKET, KC_DELETE,
                                                                                        KC_MUTE
                 ),
    [_GME] = LAYOUT(
        KC_ESC,        KC_1,    KC_2,     KC_3,    KC_4,     KC_5,     KC_6,     KC_7,      KC_8,             KC_9,             KC_0,         KC_MINUS,
        KC_TAB,        KC_Q,    KC_W,     KC_E,    KC_R,     KC_T,     KC_Y,     KC_U,      KC_I,             KC_O,             KC_P,         KC_BACKSPACE,
        KC_LEFT_CTRL,  KC_A,    KC_S,     KC_D,    KC_F,     KC_G,     KC_H,     KC_J,      KC_K,             KC_L,             KC_SEMICOLON, KC_QUOTE,
        KC_LEFT_SHIFT, KC_Z,    KC_X,     KC_C,    KC_V,     KC_B,     KC_N,     KC_M,      KC_COMMA,         KC_DOT,           KC_SLASH,     KC_RIGHT_SHIFT,
                           KC_DEL,  KC_LGUI,  KC_LALT, TL_LOWR,  KC_SPACE, KC_ENTER, TL_UPPR,   KC_LEFT_BRACKET,  KC_RIGHT_BRACKET, KC_DELETE,
                                                                                        KC_MUTE
                 ),
    [_COL] = LAYOUT(
        KC_ESC,        KC_1,    KC_2,     KC_3,    KC_4,     KC_5,     KC_6,     KC_7,      KC_8,             KC_9,             KC_0,         KC_MINUS,
        KC_TAB,        KC_Q,    KC_W,     KC_F,    KC_P,     KC_B,     KC_J,     KC_L,      KC_U,             KC_Y,             KC_SEMICOLON,         KC_BACKSPACE,
        KC_LEFT_CTRL,  KC_A,    KC_R,     KC_S,    KC_T,     KC_G,     KC_M,     KC_N,      KC_E,             KC_I,             KC_O, KC_QUOTE,
        KC_LEFT_SHIFT, KC_Z,    KC_X,     KC_C,    KC_D,     KC_V,     KC_K,     KC_H,      KC_COMMA,         KC_DOT,           KC_SLASH,     KC_RIGHT_SHIFT,
                           KC_DEL,  KC_LGUI,  KC_LALT, TL_LOWR,  KC_ENTER, KC_SPACE, TL_UPPR,   KC_LEFT_BRACKET,  KC_RIGHT_BRACKET, KC_DELETE,
                                                                                        KC_MUTE
                 ),
    [_LWR] = LAYOUT(
        KC_NUBS,    KC_F1,      KC_F2,       KC_F3,      KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_GRAVE,   _______,    KC_VOLU,     _______,    _______, _______, _______, _______, _______, _______, _______, KC_F12,
        _______,    KC_MPRV,    KC_VOLD,     KC_MNXT,    _______, _______, _______, _______, _______, _______, _______, _______,
        _______,    KC_EQUAL,   _______,     C(KC_C),    C(KC_V), _______, KC_EQUAL,_______, _______, _______, _______, _______,
        _______,    _______,    _______,     _______,    KC_MPLY, _______, _______, _______, _______, _______,
                                                                               _______
                ),
    [_RSE] = LAYOUT(
        KC_NUBS,    KC_F1,      KC_F2,       KC_F3,    KC_F4,     KC_F5,    KC_F6,    KC_F7,       KC_F8,    KC_F9,        KC_F10,  KC_F11,
        KC_GRAVE,   KC_INS,     KC_PSCR,     KC_APP,   A(KC_F13), KC_F14,   KC_PGUP,  C(KC_LEFT),  KC_UP,    C(KC_RIGHT),  _______, KC_F12,
        _______,    _______,    _______,     _______,  _______,   _______,  KC_PGDN,  KC_LEFT,     KC_DOWN,  KC_RGHT,      _______, _______,
        _______,    KC_EQUAL,   _______,     C(KC_C),  C(KC_V),   _______,  KC_EQUAL, KC_HOME,     _______,  KC_END,       _______, _______,
                        _______,    _______,     _______,  _______,   _______,  _______,  _______,     _______,  _______,      _______,
                                                                               _______
                ),
    [_ADJ] = LAYOUT(
        _______, BL_TOGG,    BL_STEP,BL_BRTG,_______,_______,_______,     _______,   _______, _______,_______,   QK_BOOT,
        _______,    KC_HUP,KC_HDN, _______,_______,_______,_______,     _______,   _______, _______,OSL(_CFG), _______,
        _______,    _______,_______, _______,_______,DF(_GME),DF(_DEF),   JIGGLE,    _______, _______,_______,   _______,
        _______,    _______,_______,DF(_COL),_______,_______,_______,     _______,   _______, _______,_______,   _______,
                        _______,_______, _______,_______,_______,_______,     _______,   _______, _______,_______,
                                                                               _______
                ),
    [_CFG] = LAYOUT(
        _______,   KC_CKCP,   _______,     _______,    _______, _______, _______, _______, _______, _______,_______, _______,
        _______,   _______,    _______,     _______,    _______, _______, _______, _______, _______, _______,_______, _______,
        _______,   _______,    _______,     _______,    _______, _______, _______, _______, _______, _______,_______, _______,
        _______,   _______,    _______,     _______,    _______, _______, _______, _______, _______, _______,_______, _______,
                       _______,    _______,     _______,    _______, _______, _______, _______, _______, _______,_______,
                                                                               _______
                )
};


#ifdef ENCODER_ENABLE
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_DEF] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [_GME] = { ENCODER_CCW_CW(KC_MS_LEFT, KC_MS_RIGHT) },
    [_LWR] = { ENCODER_CCW_CW(KC_HUP, KC_HDN) },
    [_RSE] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_ADJ] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_CFG] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
};
#endif
#endif
// clang-format on
