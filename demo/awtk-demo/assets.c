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
#include "assets/inc/styles/system_bar.data"
#include "assets/inc/styles/tab_bottom.data"
#include "assets/inc/styles/window1.data"
#include "assets/inc/ui/gvs_main.data"
#include "assets/inc/ui/index.data"
#include "assets/inc/ui/loading.data"
#include "assets/inc/ui/qq.data"
#include "assets/inc/ui/system_bar.data"
#ifdef WITH_STB_IMAGE
#include "assets/inc/images/about.res"
#include "assets/inc/images/close.res"
#include "assets/inc/images/contact.res"
#include "assets/inc/images/contact_active.res"
#include "assets/inc/images/detailed.res"
#include "assets/inc/images/device.res"
#include "assets/inc/images/discovery.res"
#include "assets/inc/images/discovery_active.res"
#include "assets/inc/images/g_background.res"
#include "assets/inc/images/g_menuborder.res"
#include "assets/inc/images/g_page_number_off.res"
#include "assets/inc/images/g_page_number_on.res"
#include "assets/inc/images/logo.res"
#include "assets/inc/images/me.res"
#include "assets/inc/images/me_active.res"
#include "assets/inc/images/msg.res"
#include "assets/inc/images/msg_active.res"
#include "assets/inc/images/qq.res"
#include "assets/inc/images/setting.res"
#include "assets/inc/images/switch.res"
#include "assets/inc/images/update.res"
#include "assets/inc/images/weichat.res"
#else
#include "assets/inc/images/about.data"
#include "assets/inc/images/close.data"
#include "assets/inc/images/contact.data"
#include "assets/inc/images/contact_active.data"
#include "assets/inc/images/detailed.data"
#include "assets/inc/images/device.data"
#include "assets/inc/images/discovery.data"
#include "assets/inc/images/discovery_active.data"
#include "assets/inc/images/g_background.data"
#include "assets/inc/images/g_menuborder.data"
#include "assets/inc/images/g_page_number_off.data"
#include "assets/inc/images/g_page_number_on.data"
#include "assets/inc/images/logo.data"
#include "assets/inc/images/me.data"
#include "assets/inc/images/me_active.data"
#include "assets/inc/images/msg.data"
#include "assets/inc/images/msg_active.data"
#include "assets/inc/images/qq.data"
#include "assets/inc/images/setting.data"
#include "assets/inc/images/switch.data"
#include "assets/inc/images/weichat.data"
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
  assets_manager_add(rm, image_about);
  assets_manager_add(rm, image_close);
  assets_manager_add(rm, image_contact);
  assets_manager_add(rm, image_contact_active);
  assets_manager_add(rm, image_detailed);
  assets_manager_add(rm, image_device);
  assets_manager_add(rm, image_discovery);
  assets_manager_add(rm, image_discovery_active);
  assets_manager_add(rm, image_g_background);
  assets_manager_add(rm, image_g_menuborder);
  assets_manager_add(rm, image_g_page_number_off);
  assets_manager_add(rm, image_g_page_number_on);
  assets_manager_add(rm, image_logo);
  assets_manager_add(rm, image_me);
  assets_manager_add(rm, image_me_active);
  assets_manager_add(rm, image_msg);
  assets_manager_add(rm, image_msg_active);
  assets_manager_add(rm, image_qq);
  assets_manager_add(rm, image_setting);
  assets_manager_add(rm, image_switch);
  assets_manager_add(rm, image_weichat);
  assets_manager_add(rm, strings_en_US);
  assets_manager_add(rm, strings_ja_JP);
  assets_manager_add(rm, strings_ko_KR);
  assets_manager_add(rm, strings_zh_CN);
  assets_manager_add(rm, strings_zh_TW);
  assets_manager_add(rm, style_default);
  assets_manager_add(rm, style_main);
  assets_manager_add(rm, style_system_bar);
  assets_manager_add(rm, style_tab_bottom);
  assets_manager_add(rm, style_window1);
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
