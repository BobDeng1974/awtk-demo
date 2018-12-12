#include "awtk.h"
#include "base/assets_manager.h"
#ifndef WITH_FS_RES
#include "assets/inc/ui/gvs_main.data"
#include "assets/inc/ui/index.data"
#include "assets/inc/ui/loading.data"
#include "assets/inc/ui/qq.data"
#include "assets/inc/ui/system_bar.data"
#ifdef WITH_STB_IMAGE
#else
#endif/*WITH_STB_IMAGE*/
#ifdef WITH_VGCANVAS
#endif/*WITH_VGCANVAS*/
#ifdef WITH_STB_FONT
#ifdef WITH_MINI_FONT
#else/*WITH_MINI_FONT*/
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
  assets_manager_add(rm, ui_gvs_main);
  assets_manager_add(rm, ui_index);
  assets_manager_add(rm, ui_loading);
  assets_manager_add(rm, ui_qq);
  assets_manager_add(rm, ui_system_bar);
#ifdef WITH_VGCANVAS
#endif/*WITH_VGCANVAS*/
#endif

  tk_init_assets();
  return RET_OK;
}
