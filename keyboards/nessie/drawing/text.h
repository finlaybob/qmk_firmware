// Copyright ©️ 2024 Neil Finlay

#pragma once
#include "fonts/agave.qff.h"

extern uint16_t         ndt_cursor_y;
extern painter_device_t nd_surf;
enum HorizontalAlignment { align_left, align_centre, align_right };

// Some utils to make drawing text a bit simpler

uint16_t              ndt_width_of(const char* str);
painter_font_handle_t ndt_load_font(void);
void                  ndt_print(const char* str, enum HorizontalAlignment align, uint8_t line);
void                  ndt_cursor_reset(void);
void                  ndt_carraige_return(void);