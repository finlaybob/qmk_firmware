// Copyright © 2025 Neil Finlay / thslkeys <finbsp@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "display.h"

#include "enums.h"
#include "quantum.h"

painter_device_t              nd_lcd;
painter_image_handle_t        nessie;
painter_image_handle_t        text_logo;
static painter_image_handle_t logo, text;
uint8_t                       nd_cur_layer;
uint8_t                       nd_mode;
bool                          nd_dirty;
static deferred_token         nd_render_token;

painter_font_handle_t font;
painter_device_t      nd_surf;

typedef enum {
    TITLE,
    LAYER,
    MODE,
#ifdef DEBUG_MATRIX_SCAN_RATE
    MATRIX,
#endif

#ifdef WPM_ENABLE
    WPM,
#endif

    COUNT
} widget_id_t;

static widget_t *widgets[COUNT];

static uint8_t layer_spacing = 25;
static uint8_t layer_widget_y = 45;
static uint8_t widget_spacing = 42;

static uint8_t framebuffer[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(WIDTH, HEIGHT, 16)];

uint32_t render_callback(uint32_t trigger_time, void *cb_arg) {
    display_render();
    return 16;
}

// Draw the splash screen directly to the LCD
void draw_splash(void) {
    text = qp_load_image_mem(gfx_splash_text);
    logo = qp_load_image_mem(gfx_splash_logo);

    qp_rect(nd_surf, 0, 0, WIDTH, HEIGHT, ND_THEME_ACCENT_A, true);
    qp_drawimage(nd_surf, X_MID - (text->width / 2), 10, text);
    qp_drawimage(nd_surf, X_MID - (logo->width / 2), y_max - logo->height - 2, logo);
    qp_surface_draw(nd_surf, nd_lcd, 0, 0, false);
}

uint32_t splash_cleanup(uint32_t trigger_time, void *cb_arg) {
    qp_close_image(logo);
#ifdef BACKLIGHT_ENABLE
#    ifdef BL_LEVEL_ON_BOOT
    backlight_level(BL_LEVEL_ON_BOOT);
#    endif
#endif
    return 0;
}

void display_startup(void) {

#ifdef BACKLIGHT_ENABLE
    // always enable the backlight on startup for splash screen
    backlight_enable();
    backlight_level(BACKLIGHT_LEVELS);
#endif

    nd_lcd = qp_ili9341_make_spi_device(WIDTH, HEIGHT, DISP_CS_PIN, DISP_DC_PIN, DISP_RST_PIN, 4, 0);
    font   = qp_load_font_mem(font_default);

    // Initialise the LCD
    qp_init(nd_lcd, QP_ROTATION_0);
    nd_surf = qp_make_rgb565_surface(WIDTH, HEIGHT, framebuffer);

    qp_init(nd_surf, QP_ROTATION_0);
    // Turn on the LCD and clear the display

    qp_power(nd_lcd, true);
    draw_splash();
    qp_flush(nd_lcd);

    wait_ms(100);

    qp_close_image(logo);

    icons_init();
    nd_dirty = true;

    uint8_t next_y_position = 0;

    widgets[TITLE] = thsl_create_widget(0, next_y_position + 1, WIDTH, 32, icons.screen, "Nessie v2", false, font, ND_THEME_FG, true);
    next_y_position += widget_spacing;

    uint8_t xpos = 45;

    widgets[LAYER] = thsl_create_widget(xpos, next_y_position, 240 - xpos, 32, icons.cog, "Mode", false, font, ND_THEME_FG, true);
    next_y_position += widget_spacing;

    widgets[MODE] = thsl_create_widget(xpos, next_y_position, 240 - xpos, 32, icons.layout, "QWERTY", false, font, ND_THEME_FG, true);
    next_y_position += widget_spacing;

#ifdef DEBUG_MATRIX_SCAN_RATE
    widgets[MATRIX] = thsl_create_widget(xpos, next_y_position, 240 - xpos, 32, icons.matrix, "Matrix Scan Rate", false, font, ND_THEME_FG, true);
    next_y_position += widget_spacing;
#endif

#ifdef WPM_ENABLE
    widgets[WPM] = thsl_create_widget(xpos, next_y_position, 240 - xpos, 32, icons.speed, "WPM", false, font, ND_THEME_FG, true);
    next_y_position += widget_spacing;
#endif

    defer_exec(SPLASH_TIMEOUT, splash_cleanup, NULL);
    nd_render_token = defer_exec(SPLASH_TIMEOUT, render_callback, NULL);
}

void clear_screen(void) {
    qp_rect(nd_surf, 0, 0, WIDTH - 1, HEIGHT - 1, ND_THEME_BG, true);
    nd_dirty = true;
}

void display_render(void) {
    // REMEMBER to draw as little as possible as few times as possible

    char buf[64];
    buf[0] = '\0';

    static uint32_t last_update = 0;
    static bool     first_run   = true;

    if (first_run) {
        clear_screen();
    }

    bool update_wpm = (timer_elapsed32(last_update) > UPDATE_TIMEOUT) || first_run;

#ifdef WPM_ENABLE
    // Just update the WPM every second
    if (update_wpm) {
        snprintf(buf, sizeof(buf), "%03hhu wpm ", get_current_wpm());
        thsl_widget_set_label(widgets[WPM], buf);
    }
#endif

    static uint8_t last_layer = 0;
    if ((nd_cur_layer != last_layer) || first_run) {
        // clear the area where the layer bar will be drawn
        qp_rect(nd_surf, x_min, layer_widget_y, x_min + layer_spacing + 2, layer_widget_y + (layer_spacing * 5), ND_THEME_BG, true);
        qp_line(nd_surf, x_min, layer_widget_y + (layer_spacing / 2), x_min, layer_widget_y + (layer_spacing * 5) + (layer_spacing / 2), ND_THEME_ACCENT_A);

        static uint8_t position = 0;

        switch (nd_cur_layer) {
            case _DEF:
            case _GME:
                position = 0;
                thsl_widget_set_label(widgets[LAYER], "BASE   ");
                break;
            case _LWR:
                position = 1;
                thsl_widget_set_label(widgets[LAYER], "LOWER  ");
                break;
            case _RSE:
                position = 2;
                thsl_widget_set_label(widgets[LAYER], "RAISE  ");
                break;
            case _ADJ:
                position = 3;
                thsl_widget_set_label(widgets[LAYER], "ADJUST ");
                break;
            case _CFG:
                position = 4;
                thsl_widget_set_label(widgets[LAYER], "CONFIG ");
                break;
        }

        // draw the layer notches
        for (uint8_t i = 0; i < 5; i++) {
            uint8_t y = layer_widget_y + (i * layer_spacing) + (layer_spacing / 2);
            qp_line(nd_surf, x_min, y, x_min + 2, y, ND_THEME_ACCENT_A);
        }
        qp_drawimage_recolor(nd_surf, x_min + 5, layer_widget_y + (position * layer_spacing), icons.arrow_left, ND_THEME_ACCENT_A, ND_THEME_BG);

        nd_dirty   = true;
        last_layer = nd_cur_layer;
    }

    static uint8_t last_mode = 0;
    if ((nd_mode != last_mode) || first_run) {
        // Print the mode
        switch (nd_mode) {
            case _DEF:
                thsl_widget_set_label(widgets[MODE], "QWERTY  ");
                break;
            case _COL:
                thsl_widget_set_label(widgets[MODE], "COLEMAK ");
                break;
            case _GME:
                thsl_widget_set_label(widgets[MODE], "(GAME)  ");
        }
        last_mode = nd_mode;
    }

#ifdef DEBUG_MATRIX_SCAN_RATE
    static uint32_t last_matrix_scan_rate = 0;
    if ((last_matrix_scan_rate != get_matrix_scan_rate())) {
        snprintf(buf, sizeof(buf), "%luhz ", get_matrix_scan_rate());
        thsl_widget_set_label(widgets[MATRIX], buf);
    }
    last_matrix_scan_rate = get_matrix_scan_rate();
#endif

    if (update_wpm || first_run) {
        // reset the timer
        last_update = timer_read32();
    }

    // Draw the widgets
    for (uint8_t i = 0; i < COUNT; i++) {
        if (widgets[i] && widgets[i]->dirty) {
            // if any widget is dirty, we need to redraw the screen
            nd_dirty = true;

            // Draw the widget
            thsl_widget_draw(nd_surf, widgets[i]);
        }
    }

    // Swap buffers
    if (nd_dirty || first_run) {
        qp_rect(nd_surf, 0, 0, x_max, 319, ND_THEME_FG, false);
        qp_surface_draw(nd_surf, nd_lcd, 0, 0, false);
        nd_dirty = false;
    }

    if (first_run) {
        first_run = false;
    }
}

