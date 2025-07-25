// Copyright © 2025 Neil Finlay <finbsp@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "qp.h"
#include "qp_surface.h"

#include "color.h"
#include "drawing/splash_logo.qgf.h"
#include "drawing/splash_text.qgf.h"

#include "icons.h"
#include "drawing/widget.h"
#include "drawing/dimensions.h"
#include "fonts/default.qff.h"

#include "drawing/theme.h"

extern painter_device_t      nd_lcd;
extern painter_device_t      nd_surf;
extern painter_font_handle_t font;
extern uint8_t               nd_cur_layer;
extern uint8_t               nd_mode;
bool                         nd_dirty;

#define UPDATE_TIMEOUT 1000
#define SPLASH_TIMEOUT 2000
#define DISP_TIMEOUT 30000
#define HUE_STEP 4

void display_startup(void);
void display_render(void);


