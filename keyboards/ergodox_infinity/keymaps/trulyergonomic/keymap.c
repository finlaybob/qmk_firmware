#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE  0 // default layer
#define EXTRA 1 // extra

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |   1  |   2  |   3  |   4  |   5  | LGui |           | LGui |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  Del |           | Tab  |   Y  |   U  |   I  |   O  |   P  |   =    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | RShift |
 * |--------+------+------+------+------+------| Back |           | Back |------+------+------+------+------+--------|
 * | LCtrl  |   Z  |   X  |   C  |   V  |   B  | space|           | space|   N  |   M  |   ,  |   .  |   '  | RCtrl  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LAlt | Home | PgUp | PgDn |  End |                                       | Left |  Up  | Down | Rigth| RAlt |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.        ,-------------.
 *                                        |  ~   |   |  |        |   [  |   ]  |
 *                                 ,------|------|------|        |------+------+------.
 *                                 |      |      |  L1  |        | Grv  |      |      |
 *                                 | Space|Enter |------|        |------| Enter|Space |
 *                                 |      |      |  /   |        |   \  |      |      |
 *                                 `--------------------'        `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,    KC_1,      KC_2,      KC_3,      KC_4,     KC_5,   KC_LGUI,
        KC_TAB,    KC_Q,      KC_W,      KC_E,      KC_R,     KC_T,   KC_DEL,
        KC_LSFT,   KC_A,      KC_S,      KC_D,      KC_F,     KC_G,
        KC_LCTL,   KC_Z,      KC_X,      KC_C,      KC_V,     KC_B,   KC_BSPC,
        KC_LALT,   KC_HOME,   KC_PGUP,   KC_PGDN,   KC_END,
                                                    KC_TILD,  KC_PIPE,
                                                              TG(EXTRA),
                                         KC_SPC,    KC_ENT,   KC_SLSH,
        // right hand
             KC_LGUI,   KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,
             KC_TAB,    KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_EQL,
                        KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_RSFT,
             KC_BSPC,   KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_QUOT,   KC_RCTL,
                                   KC_LEFT,   KC_UP,     KC_DOWN,   KC_RGHT,   KC_RALT,
             KC_LBRC,   KC_RBRC,
             KC_GRV,
             KC_BSLS,   KC_ENT,    KC_SPC
    ),
/* Keymap 1: Extra Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           | PSCR |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Caps   |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |   0  |   ,  |   .  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |VolUp |VolDn |       | Prev | Next |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       | Stop |Bright|Bright|
 *                                 | Mute |Pause |------|       |------|ness- |ness+ |
 *                                 |      |      |      |       | Play |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[EXTRA] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_CAPS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_VOLU,KC_VOLD,
                                               KC_TRNS,
                               KC_MUTE,KC_PAUS,KC_TRNS,
       // right hand
       KC_PSCR, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_0,   KC_COMM, KC_DOT,  KC_EQL,  KC_TRNS,
       KC_MPRV, KC_MNXT,
       KC_STOP,
       KC_MPLY, RGB_VAD, RGB_VAI
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
