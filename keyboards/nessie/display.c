// Copyright © 2025 Neil Finlay <finbsp@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "display.h"
#include "color.h"
#include "drawing/nessie.qgf.h"
#include "drawing/nessie-text-logo.qgf.h"
#include "drawing/logo.qgf.h"
#include "drawing/text.h"

#include "drawing/dimensions.h"

#include "enums.h"
#include "quantum.h"

painter_device_t              nd_lcd;
painter_image_handle_t        nessie;
painter_image_handle_t        text_logo;
static painter_image_handle_t logo;
uint8_t                       nd_cur_layer;
uint8_t                       nd_mode;

uint8_t                       nd_hue;
uint8_t                       nd_sat;
uint8_t                       nd_val;

bool                          nd_dirty;
static deferred_token         nd_token;
static deferred_token         icon_animation_token;

static uint8_t framebuffer[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(WIDTH, HEIGHT, 16)];

uint32_t render_callback(uint32_t trigger_time, void *cb_arg) {
    display_render();
    return 16;
}

// Draw the splash screen directly to the LCD
void draw_splash(void) {
    qp_rect(nd_lcd, 0, 0, 239, 319, HSV_BLACK, true);
    qp_rect(nd_lcd, 0, 0, 239, 319, HSV_WHITE, false);

    logo = qp_load_image_mem(gfx_logo);
    text_logo = qp_load_image_mem(gfx_nessie_text_logo);

    icon_animation_token = qp_animate(nd_lcd, X_MID - (logo->width / 2 ), (Y_MID/2) - (logo->height / 2), logo);

    qp_drawimage(nd_lcd, X_MID - (text_logo->width / 2), y_max - (Y_MID/2) - (text_logo->height), text_logo);

    //qp_drawtext(nd_lcd, X_MID + 30 - (qp_textwidth(font, "Nessie") / 2), Y_MID + 10 - font->line_height, font, "Nessie");

}

uint32_t cleanup_animation(uint32_t trigger_time, void *cb_arg) {
    if (icon_animation_token) {
        qp_stop_animation(icon_animation_token);
        icon_animation_token = INVALID_DEFERRED_TOKEN;
    }
    qp_close_image(logo);

#ifdef BACKLIGHT_ENABLE
#   ifndef BL_ENABLE_ON_BOOT
    backlight_disable();
#   endif
#endif

    return 0;
}

void display_startup(void) {

#ifdef BACKLIGHT_ENABLE
    backlight_enable();
# ifdef BL_LEVEL_ON_BOOT
    backlight_level(BL_LEVEL_ON_BOOT);
# endif
#endif


    nd_hue = 30 / 360.0 * 255;
    nd_sat = 255;
    nd_val = 255;

    nd_lcd = qp_ili9341_make_spi_device(WIDTH, HEIGHT, DISP_CS_PIN, DISP_DC_PIN, DISP_RST_PIN, 4, 0);

    font = ndt_load_font();

    // Initialise the LCD
    qp_init(nd_lcd, QP_ROTATION_0);
    nd_surf = qp_make_rgb565_surface(WIDTH, HEIGHT, framebuffer);

    qp_init(nd_surf, QP_ROTATION_0);
    // Turn on the LCD and clear the display

    qp_power(nd_lcd, true);

    draw_splash();
    qp_flush(nd_lcd);






    wait_ms(100);
    nessie = qp_load_image_mem(gfx_nessie);
    //qp_drawimage_recolor(nd_surf, X_MID - (nessie->width / 2), HEIGHT - (nessie->height), nessie, HSV_GREEN, HSV_BLACK);
    qp_drawimage(nd_surf, X_MID - (text_logo->width / 2), y_max - (text_logo->height), text_logo);

    nd_dirty = true;

    ndt_cursor_reset();

    defer_exec(SPLASH_TIMEOUT, cleanup_animation, NULL);
    nd_token = defer_exec(SPLASH_TIMEOUT, render_callback, NULL);
}

void display_render(void) {
    // REMEMBER to draw as little as possible as few times as possible

    char    buf[64] = {0};
    uint8_t line    = 0;

    static uint32_t last_update = 0;
    static bool     first_run   = true;

    bool update_wpm = (timer_elapsed32(last_update) > UPDATE_TIMEOUT) || first_run;
    ndt_cursor_reset();

#ifdef WPM_ENABLE
    // Just update the WPM every second
    if (update_wpm) {
        snprintf(buf, sizeof(buf), "󰓅 %03hhu\n", get_current_wpm());
        ndt_print(buf, align_left, line);
        nd_dirty = true;
    }
    ndt_carraige_return();
    line++;

#endif

    static uint8_t last_layer = 0;
    if ((nd_cur_layer != last_layer) || first_run) {
        ndt_print("󰽘 ", align_left, line);
        switch (nd_cur_layer) {
            case _DEF:
            case _GME:
                ndt_print("BASE  ", align_left, line);
                break;
            case _LWR:
                ndt_print("LOWER ", align_left, line);
                break;
            case _RSE:
                ndt_print("RAISE ", align_left, line);
                break;
            case _ADJ:
                ndt_print("ADJUST", align_left, line);
                break;
            case _CFG:
                ndt_print("CONFIG", align_left, line);
                break;
        }
        nd_dirty   = true;
        last_layer = nd_cur_layer;
        ndt_carraige_return();
    }
    line++;

    static uint8_t last_mode = 0;
    if ((nd_mode != last_mode) || first_run) {
        ndt_print(" ", align_left, line);
        switch (nd_mode) {
            case _DEF:
                ndt_print("QWERTY  ", align_left, line);
                break;
            case _COL:
                ndt_print("COLEMAK ", align_left, line);
                break;
            case _GME:
                ndt_print("(GAME)  ", align_left, line);
        }
        nd_dirty  = true;
        last_mode = nd_mode;
        ndt_carraige_return();
    }
    line++;

#ifdef DEBUG_MATRIX_SCAN_RATE
    static uint32_t last_matrix_scan_rate = 0;
    if ((last_matrix_scan_rate != get_matrix_scan_rate()) || force_redraw) {
        snprintf(buf, sizeof(buf), "󰘨 %lu\n", get_matrix_scan_rate());
        ndt_print(buf, align_left, line);
        nd_dirty = true;
    }
    last_matrix_scan_rate = get_matrix_scan_rate();
    ndt_carraige_return();

    line++;
#endif

    if (update_wpm || first_run) {
        // reset the timer
        last_update = timer_read32();
    }

    // Swap buffers
    if (nd_dirty || first_run) {
        qp_rect(nd_surf, 0, 0, x_max, 319, nd_hue,nd_sat,nd_val, false);
        qp_surface_draw(nd_surf, nd_lcd, 0, 0, false);
        nd_dirty = false;
    }

    if (first_run) {
        first_run = false;
    }
}
