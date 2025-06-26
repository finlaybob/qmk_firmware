#include "icons.h"
// Include all QGF icon headers
#include "drawing/icons/caps-off.qgf.h"
#include "drawing/icons/caps-on.qgf.h"
#include "drawing/icons/cogs.qgf.h"
#include "drawing/icons/layer.qgf.h"
#include "drawing/icons/layout.qgf.h"
#include "drawing/icons/light.qgf.h"
#include "drawing/icons/mac.qgf.h"
#include "drawing/icons/matrix.qgf.h"
#include "drawing/icons/num-off.qgf.h"
#include "drawing/icons/num-on.qgf.h"
#include "drawing/icons/power.qgf.h"
#include "drawing/icons/scrl-off.qgf.h"
#include "drawing/icons/scrl-on.qgf.h"
#include "drawing/icons/win.qgf.h"
#include "drawing/icons/trackpad.qgf.h"
#include "drawing/icons/encoder.qgf.h"
#include "drawing/icons/heart.qgf.h"
#include "drawing/icons/arrow-left.qgf.h"
#include "drawing/icons/game.qgf.h"
#include "drawing/icons/speed.qgf.h"
#include "drawing/icons/time.qgf.h"
#include "drawing/icons/screen.qgf.h"

icons_t icons;

void icons_init(void) {
    icons.caps_on    = qp_load_image_mem(gfx_caps_on);
    icons.caps_off   = qp_load_image_mem(gfx_caps_off);
    icons.num_on     = qp_load_image_mem(gfx_num_on);
    icons.num_off    = qp_load_image_mem(gfx_num_off);
    icons.scrl_on    = qp_load_image_mem(gfx_scrl_on);
    icons.scrl_off   = qp_load_image_mem(gfx_scrl_off);
    icons.cog        = qp_load_image_mem(gfx_cogs);
    icons.layer      = qp_load_image_mem(gfx_layer);
    icons.layout     = qp_load_image_mem(gfx_layout);
    icons.light      = qp_load_image_mem(gfx_light);
    icons.mac        = qp_load_image_mem(gfx_mac);
    icons.matrix     = qp_load_image_mem(gfx_matrix);
    icons.power      = qp_load_image_mem(gfx_power);
    icons.win        = qp_load_image_mem(gfx_win);
    icons.trackpad   = qp_load_image_mem(gfx_trackpad);
    icons.encoder    = qp_load_image_mem(gfx_encoder);
    icons.heart      = qp_load_image_mem(gfx_heart);
    icons.arrow_left = qp_load_image_mem(gfx_arrow_left);
    icons.game       = qp_load_image_mem(gfx_game);
    icons.speed      = qp_load_image_mem(gfx_speed);
    icons.time       = qp_load_image_mem(gfx_time);
    icons.screen     = qp_load_image_mem(gfx_screen);
}
