// Copyright © 2025 Neil Finlay
// SPDX-License-Identifier: GPL-2.0-or-later

#include "text.h"
#include <display.h>
#include "drawing/dimensions.h"

painter_font_handle_t font;
uint16_t              ndt_cursor_x;
uint16_t              ndt_cursor_y;
painter_device_t      nd_surf;

void ndt_cursor_reset(void) {
    ndt_cursor_x = x_min;
    ndt_cursor_y = y_min;
}

void ndt_cr(void) {
    ndt_cursor_x = x_min;
}

void ndt_lf(void) {
    ndt_cursor_y = ndt_cursor_y + (font->line_height);

    if (ndt_cursor_y >= HEIGHT) {
        return;
    }
}

void ndt_crlf() {
    ndt_cr();
    ndt_lf();
}

uint16_t ndt_width_of(const char* str) {
    return qp_textwidth(font, str);
}

bool has_newline(const char* s) {
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == '\n') {
            return true;
        }
    }
    return false;
}

void ndt_print(const char* str, enum HorizontalAlignment align, uint8_t line) {
    if (ndt_cursor_y >= HEIGHT) {
        return;
    }
    uint16_t str_width = ndt_width_of(str);

    switch (align) {
        case align_left:
            qp_drawtext(nd_surf, ndt_cursor_x, ndt_cursor_y, font, str);
            break;
        case align_centre:
            qp_drawtext(nd_surf, X_MID - (str_width / 2), ndt_cursor_y, font, str);
            break;
        case align_right:
            qp_drawtext(nd_surf, WIDTH - str_width - 1, ndt_cursor_y, font, str);
            break;
    }

    ndt_cursor_x += str_width + 1;
}

painter_font_handle_t ndt_load_font(void) {
    font = qp_load_font_mem(font_default);
    return font;
}
