/* Copyright 2019 Louwii
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

enum custom_keycodes
{
    ACTION_OPEN_WT = SAFE_RANGE,
    ACTION_EXIT_TERM,
    GIT_STA,
    GIT_COD,
};

enum Layer
{
  BASE_LAYER,
  FUNC_COLOUR,
  GIT_LAYER
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [BASE_LAYER] = LAYOUT_tkl_iso(
          KC_ESC,   KC_RGUI,    KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,    KC_F10,     KC_F11,   KC_F12,       KC_PSCR,  KC_SLCK,  KC_PAUS,

          KC_GRV,   KC_1,     KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,     KC_0,       KC_MINS,  KC_EQL,   KC_BSPC,    KC_INS,   KC_HOME,  KC_PGUP,
          KC_TAB,   KC_Q,     KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,     KC_P,       KC_LBRC,  KC_RBRC,              KC_DEL,   KC_END,   KC_PGDN,
          KC_CAPS,  KC_A,     KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,     KC_SCLN,    KC_QUOT,  KC_NUHS,  KC_ENT,
          KC_LSFT,  KC_NUBS,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,  KC_DOT,     KC_SLSH,  KC_RSFT,              ACTION_EXIT_TERM,   KC_UP,   ACTION_OPEN_WT,
          KC_LCTL,  KC_LGUI,  KC_LALT,                        KC_SPC,                           KC_RALT,    MO(1),  KC_APP,    KC_RCTL,    KC_LEFT,  KC_DOWN,  KC_RGHT
          ),

        [FUNC_COLOUR] = LAYOUT_tkl_iso(
          _______,KC_RGUI,KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24,                                KC_SLEP, _______,   RESET,

          BL_TOGG,        BL_DEC, BL_INC, BL_BRTG, _______, _______, _______, _______, _______, _______, _______, _______, _______, VLK_TOG ,      _______, _______, _______,
          OSL(GIT_LAYER), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______,
          _______,        RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_M_P, RGB_M_R, RGB_M_SN, RGB_M_X, _______, _______, _______, KC_MPLY,
          _______,        RGB_TOG, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, RGB_M_B, RGB_M_SW, RGB_M_K, RGB_M_G, _______, _______,             KC_RGUI,KC_VOLU,KC_RGUI,
          _______,        _______, _______,           A(KC_F14),                _______, _______, _______, _______,                                  KC_MPRV, KC_VOLD, KC_MNXT
          ),

        [GIT_LAYER] = LAYOUT_tkl_iso(
          _______, _______, GIT_STA, GIT_COD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______,

          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______,
          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______,
          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______,
          _______, _______, _______,          _______,                   _______, _______, _______, _______,                                _______, _______, _______
          ),

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ACTION_OPEN_WT:
      if (record->event.pressed)
      {
        SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_R) SS_UP(X_LGUI) SS_DELAY(50) "wt" SS_TAP(X_ENTER));
      }
      break;
    case ACTION_EXIT_TERM:
      if (record->event.pressed)
      {
        SEND_STRING("exit" SS_TAP(X_ENTER));
      }
      break;

    case GIT_STA:
      if (record->event.pressed)
      {
        SEND_STRING("git status --short" SS_TAP(X_ENTER));
      }
      break;

    case GIT_COD:
      if (record->event.pressed)
      {
        SEND_STRING("git checkout dev" SS_TAP(X_TAB) SS_TAP(X_ENTER));
      }
      break;

  }

  return true;
}

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

void led_set_user(uint8_t usb_led) {}
