/**
 * File:   demo1_app.c
 * Author: AWTK Develop Team
 * Brief:  basic class of all widget
 *
 * Copyright (c) 2018 - 2018  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-02-16 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"
#include "base/mem.h"
#include "base/label.h"
#include "base/timer.h"
#include "base/button.h"
#include "base/dialog.h"
#include "base/image.h"
#include "base/utils.h"
#include "base/window.h"
#include "base/time_now.h"
#include "base/main_loop.h"
#include "base/locale_info.h"
#include "base/check_button.h"
#include "base/progress_bar.h"
#include "base/image_manager.h"
#include "base/window_manager.h"
#include "base/widget_factory.h"
#include "ui_loader/ui_builder_default.h"
#include "ext_widgets.h"

extern ret_t awtk_demo_index();

static ret_t on_locale_changed(void* ctx, event_t* e) {
  (void)ctx;
  (void)e;
  log_debug("test");
  log_debug("locale_infod change: %s_%s\n", locale_info()->language, locale_info()->country);

  return RET_OK;
}

ret_t demo_loading_timer_cb(const timer_info_t* timer)
{
  char text[64];
  widget_t* win = WIDGET(timer->ctx);
  widget_t* loading_bar = widget_lookup(win, "loading_bar", TRUE);
  
  static uint8_t timer_count = 0;
  timer_count ++;
  if(timer_count == 10) {
    tk_snprintf(text, sizeof(text), "Load: %d", timer_count * 10);
    widget_set_value(loading_bar, timer_count * 10);

    widget_t *loading_text = widget_lookup(win, "loading_text", TRUE);
    widget_set_text_utf8(loading_text, "加载完成");

    awtk_demo_index();
    return RET_REMOVE;
  }
  tk_snprintf(text, sizeof(text), "Load: %d", timer_count * 10);
  widget_set_value(loading_bar, timer_count * 10);

  return RET_REPEAT;
}

ret_t demo_loading_init()
{
  awtk_set_locale_simplified_chinese();
  widget_t *loading = window_open("loading");
  widget_t *loading_text = widget_lookup(loading, "loading_text", TRUE);
  /* 设置国际化的翻译回调 */
  widget_on(loading_text, EVT_LOCALE_CHANGED, on_locale_changed, loading);
  widget_set_tr_text(loading_text, "loading");

  timer_add(demo_loading_timer_cb, loading, 100);
}
