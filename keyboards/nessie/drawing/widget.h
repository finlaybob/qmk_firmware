// Copyright © 2025 Neil Finlay
// SPDX-License-Identifier: GPL-2.0-or-later

#include "color.h"
#include "qp.h"

#define MAX_WIDGETS 8

typedef struct widget_t {
    uint8_t                id;     // Unique ID for the widget
    uint16_t               x;      // X position of the widget
    uint16_t               y;      // Y position of the widget
    uint16_t               width;  // Width of the widget
    uint16_t               height; // Height of the widget
    painter_image_handle_t icon;   // Icon to display in the widget
    const char            *label;  // Label text for the widget
    bool                   border; // Whether to draw a border around the widget
    painter_font_handle_t font; // Font to use for the label text
    uint8_t                hue;    // Hue for the widget background
    uint8_t                sat;    // Saturation for the widget background
    uint8_t                val;    // Value for the widget background
} __attribute__((packed)) __attribute__((aligned(4))) widget_t;

typedef const widget_t *widget_handle_t;

widget_handle_t thsl_create_widget(uint16_t x, uint16_t y, uint16_t width, uint16_t height,painter_image_handle_t icon, const char *label,bool border, painter_font_handle_t font,uint8_t hue, uint8_t sat, uint8_t val);
void thsl_widget_destroy(widget_handle_t widget);
void thsl_widget_draw(painter_device_t device, widget_handle_t widget);
