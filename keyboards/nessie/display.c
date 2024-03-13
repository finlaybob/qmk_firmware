// Copyright ©️ 2024 Neil Finlay

#include "display.h"
#include "color.h"
#include "drawing/nessie.qgf.h"
#include "drawing/logo.qgf.h"
#include "drawing/text.h"

#include "enums.h"
#include "quantum.h"

painter_device_t              nd_lcd;
painter_image_handle_t        nessie;
static painter_image_handle_t logo;
uint8_t                       nd_cur_layer;
uint8_t                       nd_mode;
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

    icon_animation_token = qp_animate(nd_lcd, X_MID - 20 - (logo->width), Y_MID - (logo->height / 2), logo);

    qp_drawtext(nd_lcd, X_MID + 30 - (qp_textwidth(font, "Nessie") / 2), Y_MID + 10 - font->line_height, font, "Nessie");

    // qp_close_image(icon);
    nessie = qp_load_image_mem(gfx_nessie);
}

uint32_t cleanup_animation(uint32_t trigger_time, void *cb_arg) {
    if (icon_animation_token) {
        qp_stop_animation(icon_animation_token);
        icon_animation_token = INVALID_DEFERRED_TOKEN;
    }
    qp_close_image(logo);
    return 0;
}

void display_startup(void) {
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

    qp_drawimage_recolor(nd_surf, X_MID - (nessie->width / 2), HEIGHT - (nessie->height), nessie, HSV_GREEN, HSV_BLACK);
    nd_dirty = true;
    qp_rect(nd_surf, 0, 0, x_max, 319, HSV_MAGENTA, false);

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
        qp_surface_draw(nd_surf, nd_lcd, 0, 0, false);
        nd_dirty = false;
    }

    if (first_run) {
        first_run = false;
    }
}