// Copyright © 2025 Neil Finlay / thslkeys
// SPDX-License-Identifier: GPL-2.0-or-later

#include "widget.h"

static widget_t widget[MAX_WIDGETS];
static uint8_t  widget_count = 0;

widget_t *thsl_create_widget(uint16_t x, uint16_t y, uint16_t width, uint16_t height, painter_image_handle_t icon, const char *label, bool border, painter_font_handle_t font, uint8_t hue, uint8_t sat, uint8_t val, bool fixed_size) {
    if (widget_count >= MAX_WIDGETS) {
        return NULL; // No more widgets can be created
    }

    widget[widget_count].id     = widget_count; // Assign a unique ID
    widget[widget_count].x      = x;
    widget[widget_count].y      = y;
    if (width == 0) {
        widget[widget_count].width = qp_textwidth(font, label) + 42; // Update width based on text length
    } else {
        widget[widget_count].width = width;
    }
    widget[widget_count].height = height;
    widget[widget_count].icon   = icon;
    widget[widget_count].label  = label;
    widget[widget_count].border = border;
    widget[widget_count].font   = font;
    widget[widget_count].hue    = hue;
    widget[widget_count].sat    = sat;
    widget[widget_count].val    = val;
    widget[widget_count].dirty  = true; // Mark the widget as dirty for redrawing
    widget[widget_count].fixed_size = fixed_size;

    widget_count++;
    return &widget[widget_count - 1];
}

void thsl_widget_destroy(widget_t *widget) {
    // This needs to be implemented better with dynamic memory management
    // For now, we just reset the widget count and mark the widget as NULL

    if (widget == NULL) {
        return; // Nothing to destroy
    }

    widget_count--;
    widget = NULL;
}

void thsl_widget_draw(painter_device_t device, widget_t *widget) {
    qp_rect(device, widget->x, widget->y, widget->x + widget->width, widget->y + widget->height, HSV_WHITE, false);
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

    widget->dirty = false; // Mark the widget as clean after drawing
}

void thsl_widget_set_label(widget_t *widget, const char *label) {
    if (widget == NULL || label == NULL) {
        return;
    }

    if (widget) {
        widget->label = label;
    }

    // Mark the widget as dirty for redrawing
    widget->dirty = true;

    // If the widget has a fixed size, do not update width
    if (widget->fixed_size) {
        return;
    }
    // Update width based on text length
    widget->width = qp_textwidth(widget->font, label) + 42;
}
