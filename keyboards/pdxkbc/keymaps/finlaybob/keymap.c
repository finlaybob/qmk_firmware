/* Copyright 2019 Franklin Harding
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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    GIT_STATUS = SAFE_RANGE,
    GIT_FETCH,
    GIT_CHECKOUT    
};

enum Layers
{
  DefaultLayer,
  SystemLayer,
  GitLayer  
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DefaultLayer] = LAYOUT(
      LT(SystemLayer, KC_MPLY),       LT(GitLayer, KC_MUTE),
      KC_VOLD,                      KC_VOLU,
      KC_MPRV,                      KC_MNXT
    ),

    [SystemLayer] = LAYOUT(
      KC_TRNS,        C(S(KC_M)),
      A(S(KC_F12)),   KC_ENT,
      C(G(KC_LEFT)),  C(G(KC_RGHT))
    ),

    [GitLayer] = LAYOUT(
      GIT_FETCH,    KC_TRNS,
      GIT_STATUS,   GIT_CHECKOUT,
      KC_TRNS,      KC_TRNS
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case GIT_STATUS:
      if (record->event.pressed) {
        SEND_STRING("git status" SS_TAP(X_ENTER));
      }
      break;
    
    case GIT_FETCH:
      if (record->event.pressed) {
        SEND_STRING("git fetch --all" SS_TAP(X_ENTER));
      }
      break;
    
    case GIT_CHECKOUT:
      if (record->event.pressed) {
        SEND_STRING("git checkout");
      }
      break;
    
  }

  return true;
}

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

void led_set_user(uint8_t usb_led) {}
