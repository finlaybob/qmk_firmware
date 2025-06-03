// Copyright © 2025 Neil Finlay <finbsp@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "display.h"
#include "drawing/dimensions.h"
#include "enums.h"
#include "quantum.h"

painter_device_t              nd_lcd;
static lv_obj_t *tv;
static int cur_scr = 0;
static deferred_token update_display_token;


uint32_t update_display_callback(uint32_t trigger_time, void *cb_arg) {
    display_render();
    return 2000;
}

void lv_example_spinner_1(void)
{
    /*Create a spinner*/
    lv_obj_t * spinner = lv_spinner_create(lv_scr_act(), 1000, 60);
    lv_obj_set_size(spinner, 100, 100);
    lv_obj_center(spinner);
}

void lv_example_tileview_1(void)
{
    tv = lv_tileview_create(lv_scr_act());

    /*Tile1: just a label*/
    lv_obj_t * tile1 = lv_tileview_add_tile(tv, 0, 0, LV_DIR_BOTTOM);
    lv_obj_t * label = lv_label_create(tile1);
    lv_label_set_text(label, "Scroll down");
    lv_obj_center(label);


    /*Tile2: a button*/
    lv_obj_t * tile2 = lv_tileview_add_tile(tv, 0, 1, LV_DIR_TOP | LV_DIR_RIGHT);

    lv_obj_t * btn = lv_btn_create(tile2);

    label = lv_label_create(btn);
    lv_label_set_text(label, "Scroll up or right");

    lv_obj_set_size(btn, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_center(btn);

    /*Tile3: a list*/
    lv_obj_t * tile3 = lv_tileview_add_tile(tv, 1, 1, LV_DIR_LEFT);
    lv_obj_t * list = lv_list_create(tile3);
    lv_obj_set_size(list, LV_PCT(100), LV_PCT(100));

    lv_list_add_btn(list, NULL, "One");
    lv_list_add_btn(list, NULL, "Two");
    lv_list_add_btn(list, NULL, "Three");
    lv_list_add_btn(list, NULL, "Four");
    lv_list_add_btn(list, NULL, "Five");
    lv_list_add_btn(list, NULL, "Six");
    lv_list_add_btn(list, NULL, "Seven");
    lv_list_add_btn(list, NULL, "Nine");
    lv_list_add_btn(list, NULL, "Ten");

}

void display_render(void)
{
    if (tv == NULL) {
        return;
    }
    // Update the tileview to show the current screen
    // This is a placeholder for the actual logic to determine which screen to show
    // For example, you might want to switch screens based on a variable or user input
    // For now, we will just set the first tile as the current tile
    int row = 0;
    if (cur_scr == 0) {
        row = 0;
    } else if (cur_scr == 1) {
        row = 0;
    } else if (cur_scr == 2) {
        row = 1;
    } else {
        row = 1; // Default to the first tile
    }

    int col = 0;
    if(cur_scr == 0) {
        col = 0;
    } else if (cur_scr == 1) {
        col = 1;
    } else if (cur_scr == 2) {
        col = 1;
    } else {
        col = 0; // Default to the first tile
    }
    cur_scr = (cur_scr + 1) % 3; // Cycle through screens for demonstration

    // Set the tileview to the current tile
    lv_obj_set_tile_id(tv, row, col, LV_ANIM_ON);
}

void display_startup(void) {
    nd_lcd = qp_ili9341_make_spi_device(WIDTH, HEIGHT, DISP_CS_PIN, DISP_DC_PIN, DISP_RST_PIN, 4, 0);
    qp_init(nd_lcd, QP_ROTATION_0);

    if(qp_lvgl_attach(nd_lcd))
    {
        lv_example_tileview_1();
        update_display_token = defer_exec(UPDATE_TIMEOUT, update_display_callback, NULL);
    }
}

