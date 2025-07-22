// Copyright © 2025 Neil Finlay <finbsp@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "display.h"
#include "color.h"
#include "drawing/icons/all.h"
#include "drawing/nessie.qgf.h"
#include "drawing/nessie-text-logo.qgf.h"
#include "drawing/logo.qgf.h"
#include "drawing/nessie_scene.qgf.h"
#include "drawing/text.h"
#include "icons.h"
#include "drawing/widget.h"

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

static uint8_t layer_widget_y = 50;

static widget_handle_t test_widgets[2];

static uint8_t layer_spacing = 25;

static uint8_t framebuffer[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(WIDTH, HEIGHT, 16)];

uint32_t render_callback(uint32_t trigger_time, void *cb_arg) {
    display_render();
    return 16;
}



// Draw the splash screen directly to the LCD
void draw_splash(void) {
    // qp_rect(nd_lcd, 0, 0, 239, 319, HSV_BLACK, true);
    // qp_rect(nd_lcd, 0, 0, 239, 319, HSV_WHITE, false);

    logo = qp_load_image_mem(gfx_nessie_scene);

    // text_logo = qp_load_image_mem(gfx_nessie_text_logo);

    // icon_animation_token = qp_animate(nd_lcd, X_MID - (logo->width / 2 ), (Y_MID/2) - (logo->height / 2), logo);

    // qp_drawimage(nd_lcd, X_MID - (text_logo->width / 2), y_max - (Y_MID/2) - (text_logo->height), text_logo);
    qp_drawimage(nd_surf, 0, 0, logo);
    qp_surface_draw(nd_surf, nd_lcd, 0, 0, false);

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
    // nessie = qp_load_image_mem(gfx_nessie);
    // qp_drawimage_recolor(nd_surf, X_MID - (nessie->width / 2), HEIGHT - (nessie->height), nessie, HSV_GREEN, HSV_BLACK);
    // qp_drawimage(nd_surf, X_MID - (text_logo->width / 2), y_max - (text_logo->height), text_logo);

    // unload the splash screen, it's massive and we don't need it anymore
    qp_close_image(logo);

    // load the icons
    icons_init();

    nd_dirty = true;

    ndt_cursor_reset();

    test_widgets[0] = thsl_create_widget(0, 200, 140, 40, icons.heart, "Widget Test", false, font, HSV_GREEN);

    test_widgets[1] = thsl_create_widget(0, 250, 240, 40, icons.encoder, "Widget Test 2", false, font, HSV_GREEN);

    defer_exec(SPLASH_TIMEOUT, cleanup_animation, NULL);
    nd_token = defer_exec(SPLASH_TIMEOUT, render_callback, NULL);
}

void clear_screen(void) {
    qp_rect(nd_surf, 0, 0, WIDTH - 1, HEIGHT - 1, HSV_BLACK, true);
    nd_dirty = true;
    ndt_cursor_reset();
}

void display_render(void) {
    // REMEMBER to draw as little as possible as few times as possible

    char buf[64] = {0};

    static uint32_t last_update = 0;
    static bool     first_run   = true;

    if (first_run) {
        clear_screen();

        thsl_widget_draw(nd_surf, test_widgets[0]);
        thsl_widget_draw(nd_surf, test_widgets[1]);

        // Draw the Nessie logo
        // Draw 24 tall by 48 wide ractangle in the top left corner
        qp_rect(nd_surf, 0, 0, x_min + ndt_width_of("Nessie"), y_min + font->line_height * 2, HSV_WHITE, false);
        // Write nessie and v1.1 inside the rectangle
        ndt_println("Nessie", align_left);
        ndt_crlf();
        ndt_println("v2.0", align_left);
        ndt_cursor_reset();
    }

    bool update_wpm = (timer_elapsed32(last_update) > UPDATE_TIMEOUT) || first_run;
    ndt_cursor_reset();

#ifdef WPM_ENABLE
    // Just update the WPM every second
    if (update_wpm) {
        qp_drawimage(nd_surf, 180, 180, icons.layout);
        snprintf(buf, sizeof(buf), "%03hhu\n", get_current_wpm());
        ndt_println(buf, align_right);
        nd_dirty = true;
    }
    ndt_crlf();

#endif

    static uint8_t last_layer = 0;
    if ((nd_cur_layer != last_layer) || first_run) {
        // clear the area where the layer icon will be drawn
        qp_rect(nd_surf, x_min, layer_widget_y, x_min + layer_spacing + 2, layer_widget_y + (layer_spacing * 5), HSV_BLACK, true);
        qp_rect(nd_surf, x_min, layer_widget_y, x_min + layer_spacing + 2, layer_widget_y + (layer_spacing * 5), HSV_WHITE, false);

        static uint8_t position = 0;

        switch (nd_cur_layer) {
            case _DEF:
            case _GME:
                position = 0;
                ndt_println("BASE  ", align_right);
                ndt_crlf();
                break;
            case _LWR:
                position = 1;
                ndt_println("LOWER ", align_right);
                ndt_crlf();
                break;
            case _RSE:
                position = 2;
                ndt_println("RAISE ", align_right);
                ndt_crlf();
                break;
            case _ADJ:
                position = 3;
                ndt_println("ADJUST", align_right);
                ndt_crlf();
                break;
            case _CFG:
                position = 4;
                ndt_println("CONFIG", align_right);
                ndt_crlf();
                break;
        }

        qp_drawimage_recolor(nd_surf, x_min + 5, layer_widget_y + (position * layer_spacing), icons.arrow_left, nd_hue, nd_sat, nd_val, HSV_BLACK);

        ndt_crlf();
        nd_dirty   = true;
        last_layer = nd_cur_layer;
    }

    static uint8_t last_mode = 0;
    if ((nd_mode != last_mode) || first_run) {
        // Draw the mode icon
        qp_drawimage_recolor(nd_surf, 100, 100, icons.layout, nd_hue, nd_sat, nd_val, HSV_BLACK);

        // Print the mode
        switch (nd_mode) {
            case _DEF:
                ndt_println("QWERTY  ", align_right);
                ndt_crlf();
                break;
            case _COL:
                ndt_println("COLEMAK ", align_right);
                ndt_crlf();
                break;
            case _GME:
                ndt_println("(GAME)  ", align_right);
                ndt_crlf();
        }
        ndt_crlf();
        nd_dirty  = true;
        last_mode = nd_mode;
    }

#ifdef DEBUG_MATRIX_SCAN_RATE
    static uint32_t last_matrix_scan_rate = 0;
    if ((last_matrix_scan_rate != get_matrix_scan_rate()) || force_redraw) {
        snprintf(buf, sizeof(buf), "Scan   %lu\n", get_matrix_scan_rate());
        ndt_print(buf, align_right);
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

