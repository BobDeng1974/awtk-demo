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

#include "base/types_def.h"
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
#include "base/view.h"
#include "ui_loader/ui_builder_default.h"
#include "ext_widgets.h"
#include "scroll_view/list_item.h"

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

  widget_t *qq_pages = widget_lookup(qq, "qq_pages", TRUE);
  if (qq_pages == NULL) {
    log_debug("---------qq_pages NULL---------------------------------------\r\n");
    return RET_FAIL;
  }
  widget_t *qq_msg = widget_lookup(qq_pages, "qq_msg", TRUE);
  if (qq_msg == NULL) {
    log_debug("---------qq_msg NULL---------------------------------------\r\n");
    return RET_FAIL;
  }
 
  widget_t *qq_view = widget_lookup(qq_msg, "qq_view", TRUE);
  
  if (qq_view != NULL) {
    log_debug("---------qq_view NOT NULL---------------------------------------\r\n");

          // <list_item style="odd_clickable" y="5" h="50" layout="r1 c0 s2 m2">
          //   <view x="r:5" y="0" w="8%" h="50">
          //     <image draw_type="icon" x="r:5" y="0" w="100%" h="50" image="a"/>
          //   </view>
          //   <view x="r:10" w="82%">
          //     <label style="qq_main_black" x="r:5" y="m" w="100%" h="50" text="AWTK使用交流" />
          //     <label style="qq_black" x="r:5" y="m:13" w="100%" h="20" text="您有一条新消息!" />
          //   </view>
          //   <view x="r:10" w="10%">
          //     <label style="qq_black" x="r:10" y="m:-13" w="60" h="20" text="15:35" />
          //     <image draw_type="icon" x="r:10" y="m:11" w="60" h="20" image="red_circle"/>
          //     <label style="qq_num_index" x="r:10" y="m:11" w="60" h="20" text="3" />   
          //   </view>
          // </list_item>
          // <list_item style="odd_clickable" y="5" h="50" layout="r1 c0 s2 m2">
          //   <view x="r:5" y="0" w="8%" h="50">
          //     <image draw_type="icon" x="r:5" y="0" w="100%" h="50" image="a"/>
          //   </view>
          //   <view x="r:10" w="82%">
          //     <label style="qq_main_black" x="r:5" y="m" w="100%" h="50" text="致远QQ群" />
          //     <label style="qq_black" x="r:5" y="m:13" w="100%" h="20" text="大家好啊!" />
          //   </view>
          //   <view x="r:10" w="10%">
          //     <label style="qq_black" x="r:10" y="m:-13" w="60" h="20" text="15:35" />
          //     <image draw_type="icon" x="r:10" y="m:11" w="60" h="20" image="red_circle"/>
          //     <label style="qq_num_index" x="r:10" y="m:11" w="60" h="20" text="1" />   
          //   </view>
          // </list_item>

	  widget_t *new_list_item = list_item_create(qq_view, 0, 0, 32, 32);
    
    if (new_list_item != NULL) {
      log_debug("---------new_list_item NOT NULL---------------------------------------\r\n");
      widget_use_style(new_list_item, "odd_clickable");
      widget_set_self_layout_params(new_list_item, "0", "5", "100%", "70");
      widget_layout(new_list_item);
      // widget_set_children_layout_params(new_list_item, "r1 c0 s2 m2");
    
      widget_t *new_view1 = view_create(new_list_item, 0, 0, 0, 0);
      widget_set_self_layout_params(new_view1, "0", "0", "5%", "50");
      widget_layout(new_view1);

      widget_t *new_img1 = image_create(new_view1, 0, 0, 32, 32);
      widget_set_self_layout_params(new_img1, "r:5", "0", "100%", "50");
      widget_layout(new_img1);
      image_set_draw_type(new_img1, IMAGE_DRAW_ICON);
      image_set_image(new_img1, "a");

      widget_t *new_view2 = view_create(new_list_item, 0, 0, 0, 0);
      widget_set_self_layout_params(new_view2, "r:10", "0", "85%", "50");
      widget_layout(new_view2);

      widget_t *new_lab1 = label_create(new_view2, 0,0,0,0);
      widget_use_style(new_lab1, "qq_main_black");
      widget_set_self_layout_params(new_lab1, "0", "m:5", "100%", "50");
      widget_layout(new_lab1);
      widget_set_text_utf8(new_lab1, "AWTK使用交流");

      widget_t *new_lab2 = label_create(new_view2, 0,0,0,0);
      widget_use_style(new_lab2, "qq_black");
      widget_set_self_layout_params(new_lab2, "0", "m:13", "100%", "20");
      widget_layout(new_lab2);
      widget_set_text_utf8(new_lab2, "您有一条新消息!");

      widget_t *new_view3 = view_create(new_list_item, 0, 0, 0, 0);
      widget_set_self_layout_params(new_view3, "r:10", "0", "10%", "50");
      widget_layout(new_view3);

      widget_t *new_lab3 = label_create(new_view3, 0,0,0,0);
      widget_use_style(new_lab3, "qq_black");
      widget_set_self_layout_params(new_lab3, "r:10", "m:-13", "60", "20");
      widget_layout(new_lab3);
      widget_set_text_utf8(new_lab3, "15:36");

      widget_t *new_img2 = image_create(new_view3, 0, 0, 32, 32);
      widget_set_self_layout_params(new_img2, "r:10", "m:11", "60", "20");
      widget_layout(new_img2);
      image_set_draw_type(new_img2, IMAGE_DRAW_ICON);
      image_set_image(new_img2, "red_circle");

      widget_t *new_lab4 = label_create(new_view3, 0,0,0,0);
      widget_use_style(new_lab4, "qq_num_index");
      widget_set_self_layout_params(new_lab4, "r:10", "m:11", "60", "20");
      widget_layout(new_lab4);
      widget_set_text_utf8(new_lab4, "1");
    
    }
    
  }

  return RET_OK;
}
