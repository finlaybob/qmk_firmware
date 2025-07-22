// Copyright © 2025 Neil Finlay
// SPDX-License-Identifier: GPL-2.0-or-later

#include "widget.h"

static widget_t widget[MAX_WIDGETS];
static uint8_t  widget_count = 0;

widget_handle_t thsl_create_widget(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
                                   painter_image_handle_t icon, const char *label,
                                   bool border, painter_font_handle_t font,
                                   uint8_t hue, uint8_t sat, uint8_t val) {
    // static widget_t widget = {0};
    // widget.x      = x;
    // widget.y      = y;
    // widget.width  = width;
    // widget.height = height;
    // widget.icon   = icon;
    // widget.label  = label;
    // widget.border = border;
    // widget.font   = font;
    // widget.hue    = hue;
    // widget.sat    = sat;
    // widget.val    = val;

    // return &widget;

    if (widget_count >= 8) {
        return NULL; // No more widgets can be created
    }

    widget[widget_count].id     = widget_count; // Assign a unique ID
    widget[widget_count].x      = x;
    widget[widget_count].y      = y;
    widget[widget_count].width  = width;
    widget[widget_count].height = height;
    widget[widget_count].icon   = icon;
    widget[widget_count].label  = label;
    widget[widget_count].border = border;
    widget[widget_count].font   = font;
    widget[widget_count].hue    = hue;
    widget[widget_count].sat    = sat;
    widget[widget_count].val    = val;

    widget_count++;
    return &widget[widget_count - 1];
}

void thsl_widget_destroy(widget_handle_t widget){
    // Currently, nothing to do here as we are using a static widget.
    // If dynamic memory allocation was used, this would free the memory.
    if (widget == NULL) {
        return; // Nothing to destroy
    }
}

void thsl_widget_draw(painter_device_t device, widget_handle_t widget) {
    // Draw the background rectangle
    qp_rect(device, widget->x, widget->y, widget->x + widget->width, widget->y + widget->height, HSV_WHITE, false);

    // Draw the icon on the left side of the widget
    if (widget->icon) {
        uint16_t icon_x = widget->x + 5;
        uint16_t icon_y = widget->y + (widget->height / 2) - (widget->icon->height / 2);
        qp_drawimage_recolor(device, icon_x, icon_y, widget->icon, widget->hue, widget->sat, widget->val, HSV_BLACK);
    }

    if (widget->label) {
        uint16_t text_x = widget->x + 42;
        uint16_t text_y = widget->y + (widget->height / 2) - (widget->font->line_height / 2);
        qp_drawtext_recolor(device, text_x, text_y, widget->font, widget->label, widget->hue, widget->sat, widget->val, HSV_BLACK);
    }
}
