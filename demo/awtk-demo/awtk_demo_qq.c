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
#include "scroll_view/scroll_bar.h"
#include "cJSON.h"

#define PORT (u_short)44965  
#define DEST_IP_ADDR "192.168.0.7"
#define DEFAULT_ITEM_HIGH  "70"

typedef struct _qq_msg_t {
  char *group_name;
  char *message;
  char *cur_time;
} qq_msg_t;

static widget_t *qq = NULL;

ret_t awtk_demo_qq_create_message()
{
  widget_t *msg = widget_lookup(qq, "msg", TRUE);

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

    int32_t child_count = widget_count_children(qq_view);

	  widget_t *new_list_item = list_item_create(qq_view, 0, 0, 32, 32);
    
    if (new_list_item != NULL) {
      log_debug("---------new_list_item NOT NULL---------------------------------------\r\n");
      
      /* 对新的 list_item 进行设置 */
      widget_use_style(new_list_item, "odd_clickable");
      char new_item_offset[16] = {0,};
      sprintf(new_item_offset, "%d", child_count * atoi(DEFAULT_ITEM_HIGH));
      widget_set_self_layout_params(new_list_item, "0", new_item_offset, "100%", "70");
      widget_layout(new_list_item);

      /* 创建一个新的view */
      widget_t *new_view1 = view_create(new_list_item, 0, 0, 0, 0);
      widget_set_self_layout_params(new_view1, "5", "5", "5%", "50");
      widget_layout(new_view1);

      widget_t *new_img1 = image_create(new_view1, 0, 0, 32, 32);
      widget_set_self_layout_params(new_img1, "5", "0", "100%", "50");
      widget_layout(new_img1);
      image_set_draw_type(new_img1, IMAGE_DRAW_ICON);
      image_set_image(new_img1, "a");

      widget_t *new_view2 = view_create(new_list_item, 0, 0, 0, 0);
      widget_set_self_layout_params(new_view2, "c", "0", "85%", "50");
      widget_layout(new_view2);

      widget_t *new_lab1 = label_create(new_view2, 0,0,0,0);
      widget_use_style(new_lab1, "qq_main_black");
      widget_set_self_layout_params(new_lab1, "r", "m:9", "100%", "50");
      widget_layout(new_lab1);
      widget_set_text_utf8(new_lab1, "AWTK使用交流 By Code");

      widget_t *new_lab2 = label_create(new_view2, 0,0,0,0);
      widget_use_style(new_lab2, "qq_black");
      widget_set_self_layout_params(new_lab2, "r", "m:17", "100%", "20");
      widget_layout(new_lab2);
      widget_set_text_utf8(new_lab2, "您有一条新消息!");

      widget_t *new_view3 = view_create(new_list_item, 0, 0, 0, 0);
      widget_set_self_layout_params(new_view3, "r", "0", "10%", "50");
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

      widget_t *qq_scroll_bar = widget_lookup(qq, "qq_scroll_bar", TRUE);
      value_t v;
      widget_get_prop(qq_scroll_bar, WIDGET_PROP_MAX, &v);
      uint16_t value = v.value.u16;
      value = value + atoi(DEFAULT_ITEM_HIGH);
      v.value.u16 = value;
      widget_set_prop(qq_scroll_bar, WIDGET_PROP_MAX, &v);
      scroll_bar_scroll_delta(qq_scroll_bar, atoi(DEFAULT_ITEM_HIGH));
    }
    
  }
}

ret_t awtk_demo_qq_init(void* ctx, event_t* e) 
{
  qq = window_open((const char *)ctx);
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

  awtk_demo_qq_create_message();
  awtk_demo_qq_create_message();
  awtk_demo_qq_create_message();
  awtk_demo_qq_create_message();
  awtk_demo_qq_create_message();
  awtk_demo_qq_create_message();
  awtk_demo_qq_create_message();
  awtk_demo_qq_create_message();
  awtk_demo_qq_create_message();
  awtk_demo_qq_create_message();

  cJSON * root =  cJSON_CreateObject();
  cJSON * item =  cJSON_CreateObject();
  cJSON * next =  cJSON_CreateObject();

  cJSON_AddItemToObject(root, "rc", cJSON_CreateNumber(0));//根节点下添加
  cJSON_AddItemToObject(root, "operation", cJSON_CreateString("CALL"));
  cJSON_AddItemToObject(root, "service", cJSON_CreateString("telephone"));
  cJSON_AddItemToObject(root, "text", cJSON_CreateString("打电话给张三"));
  cJSON_AddItemToObject(root, "semantic", item);//root节点下添加semantic节点
  cJSON_AddItemToObject(item, "slots", next);//semantic节点下添加item节点
  cJSON_AddItemToObject(next, "name", cJSON_CreateString("张三"));//添加name节点

  log_debug("%s\n", cJSON_Print(root));

  transport_open("180.97.33.108", 80);

  return RET_OK;
}
