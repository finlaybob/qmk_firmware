// Copyright © 2025 Neil Finlay
// SPDX-License-Identifier: GPL-2.0-or-later

#include "widget.h"

widget_handle_t thsl_create_widget(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
                                   painter_image_handle_t icon, const char *label,
                                   bool border, painter_font_handle_t font,
                                   uint8_t hue, uint8_t sat, uint8_t val) {
    static widget_t widget = {0};
    widget.x      = x;
    widget.y      = y;
    widget.width  = width;
    widget.height = height;
    widget.icon   = icon;
    widget.label  = label;
    widget.border = border;
    widget.font   = font;
    widget.hue    = hue;
    widget.sat    = sat;
    widget.val    = val;

    return &widget;
}

void thsl_widget_destroy(widget_handle_t widget){
    // Currently, nothing to do here as we are using a static widget.
    // If dynamic memory allocation was used, this would free the memory.
    (void)widget; // Suppress unused parameter warning
}

void thsl_widget_draw(painter_device_t device, widget_handle_t widget) {
    // Draw the background rectangle
    qp_rect(device, widget->x, widget->y, widget->x + widget->width, widget->y + widget->height, HSV_WHITE, false);

    // Draw the icon on the left side of the widget
    if (widget->icon) {
        uint16_t icon_x = widget->x + 5;                         // 5 pixels padding
        uint16_t icon_y = widget->y + (widget->height - 24) / 2; // Center the icon vertically
        qp_drawimage(device, icon_x, icon_y, widget->icon);
    }
    // Draw the label text on the right side of the widget
    if (widget->label) {
        uint16_t text_x = widget->x + 40; // 40 pixels padding
        uint16_t text_y = widget->y + (widget->height - 16) / 2; // Center the text vertically
        qp_drawtext(device, text_x, text_y, widget->font, widget->label);
    }
}
