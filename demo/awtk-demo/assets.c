#include "awtk.h"
#include "base/assets_manager.h"
#ifndef WITH_FS_RES
#include "assets/inc/strings/en_US.data"
#include "assets/inc/strings/ja_JP.data"
#include "assets/inc/strings/ko_KR.data"
#include "assets/inc/strings/zh_CN.data"
#include "assets/inc/strings/zh_TW.data"
#include "assets/inc/styles/default.data"
#include "assets/inc/styles/main.data"
#include "assets/inc/styles/window1.data"
#include "assets/inc/ui/air_conditioning.data"
#include "assets/inc/ui/air_quality.data"
#include "assets/inc/ui/gvs_main.data"
#include "assets/inc/ui/hvac.data"
#include "assets/inc/ui/input_number.data"
#include "assets/inc/ui/make_color.data"
#include "assets/inc/ui/mulfuncchildwin.data"
#include "assets/inc/ui/mulfuncfour.data"
#include "assets/inc/ui/mulfuncone.data"
#include "assets/inc/ui/mulfuncthree.data"
#include "assets/inc/ui/mulfunctwo.data"
#include "assets/inc/ui/music.data"
#include "assets/inc/ui/newair_child.data"
#include "assets/inc/ui/new_air.data"
#include "assets/inc/ui/radfloor.data"
#include "assets/inc/ui/realtime_clock.data"
#include "assets/inc/ui/slide_view_h.data"
#include "assets/inc/ui/timeset.data"
#ifdef WITH_STB_IMAGE
#else
#endif/*WITH_STB_IMAGE*/
#ifdef WITH_VGCANVAS
#endif/*WITH_VGCANVAS*/
#ifdef WITH_STB_FONT
#ifdef WITH_MINI_FONT
#include "assets/inc/fonts/default.mini.res"
#else/*WITH_MINI_FONT*/
#include "assets/inc/fonts/default.res"
#endif/*WITH_MINI_FONT*/
#else/*WITH_STB_FONT*/
#endif/*WITH_STB_FONT*/
#endif/*WITH_FS_RES*/

ret_t assets_init(void) {
  assets_manager_t* rm = assets_manager();

#ifdef WITH_FS_RES
  assets_manager_load(rm, ASSET_TYPE_STYLE, "default");
  assets_manager_load(rm, ASSET_TYPE_FONT, "default");
#else
  assets_manager_add(rm, strings_en_US);
  assets_manager_add(rm, strings_ja_JP);
  assets_manager_add(rm, strings_ko_KR);
  assets_manager_add(rm, strings_zh_CN);
  assets_manager_add(rm, strings_zh_TW);
  assets_manager_add(rm, style_default);
  assets_manager_add(rm, style_main);
  assets_manager_add(rm, style_window1);
  assets_manager_add(rm, ui_air_conditioning);
  assets_manager_add(rm, ui_air_quality);
  assets_manager_add(rm, ui_gvs_main);
  assets_manager_add(rm, ui_hvac);
  assets_manager_add(rm, ui_input_number);
  assets_manager_add(rm, ui_make_color);
  assets_manager_add(rm, ui_mulfuncchildwin);
  assets_manager_add(rm, ui_mulfuncfour);
  assets_manager_add(rm, ui_mulfuncone);
  assets_manager_add(rm, ui_mulfuncthree);
  assets_manager_add(rm, ui_mulfunctwo);
  assets_manager_add(rm, ui_music);
  assets_manager_add(rm, ui_newair_child);
  assets_manager_add(rm, ui_new_air);
  assets_manager_add(rm, ui_radfloor);
  assets_manager_add(rm, ui_realtime_clock);
  assets_manager_add(rm, ui_slide_view_h);
  assets_manager_add(rm, ui_timeset);
#ifdef WITH_VGCANVAS
#endif/*WITH_VGCANVAS*/
#endif

  tk_init_assets();
  return RET_OK;
}
