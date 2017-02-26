#include <pebble.h>
#include "num_sets.h"
#include "master.h"
#include "ftoa.h"
#include "sets.h"

TextLayer *time_layer;
TextLayer *text_layer;
TextLayer *sets_layer;

static GBitmap *res_up_arrow;
static GBitmap *res_down_arrow;
static GBitmap *res_check_mark;

static ActionBarLayer *action_bar_layer;

static int max_sets = 14;
static int min_sets = 0;

char num_sets_buff[10];
static char s_time_text[] = "00:00   ";

static void handle_second_tick(struct tm *tick_time, TimeUnits units_changed)
{
  if (units_changed & MINUTE_UNIT)
  {
    clock_copy_time_string(s_time_text, sizeof(s_time_text));
    text_layer_set_text(time_layer, s_time_text);
  }
}

static void select_click_handler(ClickRecognizerRef recognize, void *context) {
  //persist_write_int(m_weight_d*10);
  sets_init();
  window_stack_push(sets_window, false);
}

static void up_click_handler(ClickRecognizerRef recognize, void *context) {
  sets = sets + 1;

  if (sets > max_sets)
  {
    sets = min_sets;
  }
  
  ftoa(num_sets_buff, sets, 2);
  
  text_layer_set_text(sets_layer, num_sets_buff);
}

static void down_click_handler(ClickRecognizerRef recognize, void *context) {
  sets = sets - 1;

  if (sets < min_sets)
  {
    sets = max_sets;
  }
  
  ftoa(num_sets_buff, sets, 2);
  
  text_layer_set_text(sets_layer, num_sets_buff);
}

static void click_config_provider(void *context)
{
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_single_repeating_click_subscribe(BUTTON_ID_UP, 100, up_click_handler);
  window_single_repeating_click_subscribe(BUTTON_ID_DOWN, 100, down_click_handler);
}
static void window_load(Window* window)
{
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  sets = 3;
  
  // Create "Select a Weight" text layer
  text_layer = text_layer_create((GRect) {.origin = {bounds.size.w/2-45, bounds.origin.y+23}, .size = { 90, 60 } });
  text_layer_set_text(text_layer, "Number of Warmup Sets");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
  
  ftoa(num_sets_buff, sets, 2);
  sets_layer = text_layer_create((GRect) {.origin = {bounds.size.w/2-40, bounds.size.h/2-17}, .size = { 80, 28 } });
  text_layer_set_text_alignment(sets_layer, GTextAlignmentCenter);
  text_layer_set_text(sets_layer, num_sets_buff);
  text_layer_set_font(sets_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(sets_layer));
  
  // Create the time text layer up top
  time_layer = text_layer_create((GRect) {.origin = {bounds.size.w/2-30, bounds.origin.y+5}, .size = { 60, 15 } });
  text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(time_layer));
  
}

static void window_appear(Window* window)
{
  clock_copy_time_string(s_time_text, sizeof(s_time_text));
  text_layer_set_text(time_layer, s_time_text);
  tick_timer_service_subscribe(SECOND_UNIT, handle_second_tick);
}

static void window_unload(Window* window)
{
  num_sets_window = NULL;
  window_destroy(num_sets_window);
  action_bar_layer_destroy(action_bar_layer);
  gbitmap_destroy(res_up_arrow);
  gbitmap_destroy(res_check_mark);
  gbitmap_destroy(res_down_arrow);
}

void num_sets_init(void)
{
  if (!num_sets_window)
  {
    num_sets_window = window_create();
    
    res_up_arrow = gbitmap_create_with_resource(RESOURCE_ID_plus);
    res_down_arrow = gbitmap_create_with_resource(RESOURCE_ID_minus);
    res_check_mark = gbitmap_create_with_resource(RESOURCE_ID_check_mark);
    
    // Create the action bar
    action_bar_layer = action_bar_layer_create();
    action_bar_layer_add_to_window(action_bar_layer, num_sets_window);
    action_bar_layer_set_background_color(action_bar_layer, GColorBlack);
    action_bar_layer_set_icon(action_bar_layer, BUTTON_ID_UP, res_up_arrow);
    action_bar_layer_set_icon(action_bar_layer, BUTTON_ID_SELECT, res_check_mark);
    action_bar_layer_set_icon(action_bar_layer, BUTTON_ID_DOWN, res_down_arrow);
    layer_add_child(window_get_root_layer(num_sets_window), (Layer *)action_bar_layer);
    
    window_set_click_config_provider(num_sets_window, click_config_provider);
    window_set_window_handlers(num_sets_window, (WindowHandlers)
    {
      .load = window_load,
      .appear = window_appear,
      .unload = window_unload
    });
  }

  window_stack_push(num_sets_window, false);
}

void sets_deinit(void)
{
  text_layer_destroy(time_layer);
  window_destroy(num_sets_window);
}