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


ret_t awtk_demo_qq_init(void* ctx, event_t* e) 
{
  widget_t *qq = window_open((const char *)ctx);
  widget_t *msg = widget_lookup(qq, "msg", TRUE);
  widget_set_tr_text(msg, "Message");

  widget_t *contact = widget_lookup(qq, "contact", TRUE);
  widget_set_tr_text(contact, "Contact");

  widget_t *discovery = widget_lookup(qq, "discovery", TRUE);
  widget_set_tr_text(discovery, "Discovery");

  widget_t *me = widget_lookup(qq, "me", TRUE);
  widget_set_tr_text(me, "Me");
  return RET_OK;
}
