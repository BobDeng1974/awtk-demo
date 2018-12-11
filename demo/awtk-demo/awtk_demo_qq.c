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
  log_debug("------------------------------------------------\r\n");
  /* 为底部标题栏设置国际化 */
  widget_t *msg = widget_lookup(qq, "msg", TRUE);
  widget_set_tr_text(msg, "Message");

  widget_t *contact = widget_lookup(qq, "contact", TRUE);
  widget_set_tr_text(contact, "Contact");

  widget_t *discovery = widget_lookup(qq, "discovery", TRUE);
  widget_set_tr_text(discovery, "Discovery");

  widget_t *me = widget_lookup(qq, "me", TRUE);
  widget_set_tr_text(me, "Me");

  widget_t *device = widget_lookup(qq, "device", TRUE);
  widget_set_tr_text(device, "Device");

  widget_t *qq_pages = widget_lookup(msg, "qq_pages", TRUE);
  widget_t *qq_msg = widget_lookup(qq_pages, "qq_msg", TRUE);
  if (qq_msg == NULL) {
    log_debug("---------qq_msg NULL---------------------------------------\r\n");
  }

  widget_t *qq_view = widget_lookup(qq_msg, "qq_view", TRUE);
  

  if (qq_view != NULL) {
    widget_t *new_list_item = list_item_create(qq_view, 0, 0, 32, 32);
    if (new_list_item != NULL) {
      /* 设置  new_list_item  的style*/
      widget_use_style(new_list_item, "odd_clickable");
      
      widget_layout_t layout;
      widget_layout_parse(&layout, NULL, "t:5", NULL, "50");
      widget_set_self_layout(new_list_item, &layout);
    }
    log_debug("---------test2---------------------------------------\r\n");

    /* 创建聊天的对象图片 */
    widget_t *new_img = image_create(qq_view, 0, 0, 32, 32);
    image_set_draw_type(new_img, IMAGE_DRAW_ICON);
    image_set_image(new_img, "a");

    widget_add_child(new_list_item, new_img);

    // widget_layout_t *new_img_style = widget_layout_parse();
    
    // log_debug("test3");
    
  } else {
     log_debug("---------test3---------------------------------------\r\n");
  }

  return RET_OK;
}
