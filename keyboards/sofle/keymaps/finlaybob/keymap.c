#include QMK_KEYBOARD_H

#ifdef OLED_DRIVER_ENABLE
#include <stdio.h>
#endif

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _DEFAULT,
    _GAME,
    _LOWER,
    _RAISE,
    _ADJUST,
};


enum custom_keycodes {
    KC_DEFAULT = SAFE_RANGE,
    KC_GAME,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
    KC_PRVWD,
    KC_NXTWD,
    KC_DLINE,

    G_STA,
    G_CHK,
    G_COM,

    REM_BUTTON,
    ALT_TAB,
    CTRL_TAB,
    PT_RUN,

};

enum light_layers{
    LL_CAPS,
    LL_LOWER,
    LL_RAISE,
    LL_ADJ,
};
enum RGB_EDIT_MODE {
    REM_MODE,
    REM_HUE,
    REM_SAT,
    REM_VAL
};


static uint8_t current_rem_mode = REM_MODE;

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool is_ctrl_tab_active = false;
uint16_t ctrl_tab_timer = 0;


#ifdef WPM_ENABLE
uint16_t wpm_graph_timer = 0;
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_DEFAULT] = LAYOUT( \
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_MINS, \
  KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC, \
  KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MPLY,     REM_BUTTON,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT, \
                 KC_LGUI,KC_LALT,KC_LCTRL, KC_LOWER, KC_ENT,      KC_SPC,  KC_RAISE, KC_RCTRL, KC_RALT, KC_RGUI \
),
/*
 * GAMES
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Space  /       \Enter \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_GAME] = LAYOUT( \
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,   KC_8,    KC_9,    KC_0,  KC_MINS, \
  KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC, \
  KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MPLY,     REM_BUTTON,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT, \
                 KC_LGUI,KC_LALT,KC_LCTRL,KC_LOWER, KC_SPC,      KC_ENT,  KC_RAISE, KC_RCTRL, KC_RALT, KC_RGUI \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |KC_DEL|  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   |  |
 * |------+------+------+------+------+------|  PLAY |    |       |------+------+------+------+------+------|
 * | Shift|  =   |  -  |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   \  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'@
 */
[_LOWER] = LAYOUT( \
  KC_DEL,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,\
  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_F12, \
  _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, \
  _______,  KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, KC_F12,       _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______, \
                       _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______\
),
/* RAISE
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  | Ins  | Pscr | Menu |      |      |                    |      | PWrd |  Up  | NWrd | DLine| Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | LAlt | LCtl |LShift|      | Caps |-------.    ,-------|      | Left | Down | Rigth|  Del | Bspc |
 * |------+------+------+------+------+------|  PLAY |    |       |------+------+------+------+------+------|
 * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------|      | LStr |      | LEnd |      | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT( \
  _______, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ ,KC_EQL, \
  _______,  KC_INS,  KC_PSCR,   KC_APP,  PT_RUN, KC_F14,                        KC_PGUP, KC_PRVWD,   KC_UP, KC_NXTWD,KC_DLINE, KC_BSPC, \
  _______, KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX, KC_CAPS,                       KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL, KC_BSPC, \
  _______,KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, XXXXXXX,  _______,       _______,  XXXXXXX, KC_HOME, XXXXXXX, KC_END,   XXXXXXX, _______, \
                         _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______ \
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      | G_STA| G_CHK| G_COM|      |      |                    | RGB |  RGB+ |HUE+  |SAT+  |VAL+  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | RESET|      |QWERTY| GAME |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      | VOLDO| MUTE | VOLUP|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX , G_STA,  G_CHK ,    G_COM , XXXXXXX, XXXXXXX,                     RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, REM_BUTTON, \
  RESET   , XXXXXXX,KC_DEFAULT,KC_GAME,XXXXXXX,XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX , XXXXXXX,XXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX,                     XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX, \
  _______ , XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, _______, \
                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______ \
  )
};

const rgblight_segment_t PROGMEM BL_caps[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_RED}       // Light 1 LEDs, starting with LED 0
);

const rgblight_segment_t PROGMEM BL_adj[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 2, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM BL_raise[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 2, 4,255,255}
);

const rgblight_segment_t PROGMEM BL_lower[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 2, HSV_GREEN}
);


#ifdef RGBLIGHT_LAYERS

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    BL_caps,
    BL_lower,
    BL_raise,
    BL_adj
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}


bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(LL_CAPS, led_state.caps_lock);
    return true;
}


layer_state_t layer_state_set_user(layer_state_t state) {
    bool b = layer_state_cmp(state, _ADJUST);
    rgblight_set_layer_state(LL_ADJ, b);

    if(b) {
        return state;
    };

    rgblight_set_layer_state(LL_LOWER, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(LL_RAISE, layer_state_cmp(state, _RAISE));
    return state;
}
#endif

#ifdef OLED_DRIVER_ENABLE


static uint8_t wpm_graph_interval = 250;

static void render_wpm_graph(void) {
    static uint8_t zero_bar_count = 0;
    static uint8_t bar_count = 0;
    uint8_t bar_height = 0;
    uint8_t bar_segment = 0;

    if (wpm_graph_timer == 0) {
	wpm_graph_timer = timer_read();
	return;
    }
    if(timer_elapsed(wpm_graph_timer) > wpm_graph_interval) {
        wpm_graph_timer = timer_read();

        if(OLED_DISPLAY_HEIGHT == 64)
            bar_height = get_current_wpm() / 2;
        if(OLED_DISPLAY_HEIGHT == 32)
            bar_height = get_current_wpm() / 4;
        if(bar_height > OLED_DISPLAY_HEIGHT)
            bar_height = OLED_DISPLAY_HEIGHT;

        if(bar_height == 0) {
            // keep track of how many zero bars we have drawn.  If
            // there is a whole screen worth, turn the display off and
            // wait until there is something to do
            if (zero_bar_count > OLED_DISPLAY_WIDTH) {
            oled_off();
            return;
            }
            zero_bar_count++;
        } else
            zero_bar_count=0;

        oled_pan(false);
        bar_count++;
        for (uint8_t i = (OLED_DISPLAY_HEIGHT / 8); i > 0; i--) {
            if (bar_height > 7) {
            if (i % 2 == 1 && bar_count % 3 == 0)
                bar_segment = 254;
            else
                bar_segment = 255;
            bar_height -= 8;
            } else {
            switch (bar_height) {
                case 0:
                bar_segment = 0;
                break;

                case 1:
                bar_segment = 128;
                break;

                case 2:
                bar_segment = 192;
                break;

                case 3:
                bar_segment = 224;
                break;

                case 4:
                bar_segment = 240;
                break;

                case 5:
                bar_segment = 248;
                break;

                case 6:
                bar_segment = 252;
                break;

                case 7:
                bar_segment = 254;
                break;
            }
            bar_height = 0;

            if (i % 2 == 1 && bar_count % 3 == 0)
                bar_segment++;
            }
            oled_write_raw_byte(bar_segment, (i-1) * OLED_DISPLAY_WIDTH);
        }
    }
}



static void write_rgb_edit_mode(void){

    oled_write_P(PSTR("-----"), false);
    oled_write_P(PSTR(" RGB "), false);
    switch (current_rem_mode)
    {
    case REM_MODE:
        oled_write_P(PSTR(" MOD "), false);
        break;
    case REM_HUE:
        oled_write_P(PSTR(" HUE "), false);
        break;
    case REM_SAT:
        oled_write_P(PSTR(" SAT "), false);
        break;
    case REM_VAL:
        oled_write_P(PSTR(" VAL "), false);
        break;

    default:
        break;
    }
}


static void write_wpm(void) {
    oled_write_P(PSTR("-----"), false);
    oled_write_P(PSTR(" WPM "), false);
    static char str[6];
    sprintf(str," %03u ",get_current_wpm());
    oled_write(str, false);
}

static void write_lock_state(void){

    oled_write_P(PSTR("-----"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(PSTR(" NUM "), led_usb_state.num_lock);
    oled_write_P(PSTR(" CAP "), led_usb_state.caps_lock);
    oled_write_P(PSTR(" SCR "), led_usb_state.scroll_lock);
}

static void write_layer_state(void){

    oled_write_P(PSTR("-----"), false);
    switch (get_highest_layer(layer_state))
    {
        case _GAME:
        case _DEFAULT:
            oled_write_P(PSTR(" Def "), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR(" Adj "), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }

}

static void write_layer_mode_state(void){

    switch (get_highest_layer(default_layer_state)) {
        case _DEFAULT:
            oled_write_P(PSTR("Norm "), false);
            break;
        case _GAME:
            oled_write_P(PSTR("Game "), true);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
}

static void print_status_primary(void) {

    write_layer_mode_state();

    write_layer_state();

    write_lock_state();

    write_wpm();

    write_rgb_edit_mode();

}






oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()){
        return rotation;
    }else{
        return OLED_ROTATION_270;
    }
}

void oled_task_user(void) {
    if (is_keyboard_master()){
        print_status_primary();
    }else{
        render_wpm_graph();
    }

}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {


        case PT_RUN:
        if(record->event.pressed){
            if (record->event.pressed) {
                tap_code16(A(KC_F13));
            }
        }
        break;
        case REM_BUTTON:
        if(record->event.pressed){
            if(current_rem_mode==REM_VAL){
                current_rem_mode=REM_MODE;
            }else{
                current_rem_mode++;
            }
        }
        break;


        case G_STA:
        if (record->event.pressed)
        {
            SEND_STRING("git status --short" SS_TAP(X_ENTER));
        }
        break;

        case G_CHK:
        if (record->event.pressed)
        {
            SEND_STRING("git checkout ");
        }
        break;

        case G_COM:
        if (record->event.pressed)
        {
            SEND_STRING("git commit" SS_TAP(X_ENTER));
        }
        break;


        case KC_DEFAULT:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DEFAULT);
            }
            return false;
        case KC_GAME:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_GAME);
            }
            return false;
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_ADJUST:
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
        case KC_DLINE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_BSPC);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_BSPC);
            }
            break;
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
    }

    return true;
}



#ifdef ENCODER_ENABLE

enum encoder_side {LEFT,RIGHT};

void encoder_rgb_edit_tap(bool cw){

    switch (current_rem_mode)
    {
    case REM_MODE:
        if(cw){
            rgblight_step();
        } else {
            rgblight_step_reverse();
        }
        break;
    case REM_HUE:
        if(cw){
            rgblight_increase_hue();
        } else {
            rgblight_decrease_hue();
        }
        break;
    case REM_SAT:
        if(cw){
            rgblight_increase_sat();
        } else {
            rgblight_decrease_sat();
        }
        break;
    case REM_VAL:
        if(cw){
            rgblight_increase_val();
        } else {
            rgblight_decrease_val();
        }
        break;

    default:
        break;
    }

}

void encoder_update_super_alttab(bool cw){

    if (!is_alt_tab_active) {
        is_alt_tab_active = true;
        register_code(KC_LALT);
    }

    if (cw) {
        alt_tab_timer = timer_read();
        tap_code16(KC_TAB);
    } else {
        alt_tab_timer = timer_read();
        tap_code16(S(KC_TAB));
    }

}


void encoder_update_super_ctrltab(bool cw){
    if (!is_ctrl_tab_active) {
        is_ctrl_tab_active = true;
        register_code(KC_LCTL);
    }

    if (cw) {
        ctrl_tab_timer = timer_read();
        tap_code16(KC_TAB);
    } else {
        ctrl_tab_timer = timer_read();
        tap_code16(S(KC_TAB));
    }
}

void enc_update_default(uint8_t index, bool cw){
    if (index == LEFT) {
        if (cw) {
            tap_code(KC_VOLU);
    } else {
            tap_code(KC_VOLD);
        }
    } else if (index == RIGHT) {
        encoder_rgb_edit_tap(cw);

    }
}

void enc_update_raised(uint8_t index, bool cw){

    if (index == LEFT) {

        encoder_update_super_ctrltab(cw);

    } else if (index == RIGHT) {

    }
}

void enc_update_lowered(uint8_t index, bool cw){

    if (index == LEFT) {
        if (cw) {
            tap_code(KC_PGDOWN);
        } else {
            tap_code(KC_PGUP);

        }
    } else if (index == RIGHT) {
        encoder_update_super_alttab(cw);
    }
}

void enc_update_adjust(uint8_t index, bool cw){
    return;
}

void encoder_update_user(uint8_t index, bool clockwise)
{
    switch (get_highest_layer(layer_state))
    {
        case _ADJUST:
            enc_update_adjust(index,clockwise);
            break;
        case _RAISE:
            enc_update_raised(index,clockwise);
            break;
        case _LOWER:
            enc_update_lowered(index,clockwise);
            break;
        default:
            enc_update_default(index,clockwise);
    }
}

#endif

void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
    if (is_ctrl_tab_active) {
        if (timer_elapsed(ctrl_tab_timer) > 1000) {
            unregister_code(KC_LCTL);
            is_ctrl_tab_active = false;
        }
    }
}
