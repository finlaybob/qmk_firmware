#ifndef ICONS_H
#define ICONS_H

#include "quantum/painter/qp.h" // for painter_image_handle_t

// Icon handles structure
typedef struct {
    painter_image_handle_t caps_on;
    painter_image_handle_t caps_off;
    painter_image_handle_t num_on;
    painter_image_handle_t num_off;
    painter_image_handle_t scrl_on;
    painter_image_handle_t scrl_off;
    painter_image_handle_t cog;
    painter_image_handle_t layer;
    painter_image_handle_t layout;
    painter_image_handle_t light;
    painter_image_handle_t mac;
    painter_image_handle_t matrix;
    painter_image_handle_t mouse;
    painter_image_handle_t power;
    painter_image_handle_t rot;
    painter_image_handle_t win;
    painter_image_handle_t trackpad;
    painter_image_handle_t encoder;
    painter_image_handle_t heart;
    painter_image_handle_t arrow_left;
    painter_image_handle_t game;
    painter_image_handle_t speed;
    painter_image_handle_t time;
    painter_image_handle_t screen;

} icons_t;

extern icons_t icons;

void icons_init(void);

#endif // ICONS_H
