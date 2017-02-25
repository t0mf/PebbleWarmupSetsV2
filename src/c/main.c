#include <pebble.h>
#include "master.h"
#include "ftoa.h"
#include "num_sets.h"

Window *main_window;

TextLayer *time_layer;
TextLayer *text_layer;
TextLayer *weight_layer;

static GBitmap *res_up_arrow;
static GBitmap *res_down_arrow;
static GBitmap *res_check_mark;

static ActionBarLayer *action_bar_layer;

static int max_weight = 1000;
int temp = 0;
static char s_time_text[] = "00:00   ";
char weight_buff[10];
double step_size[2] = {5, 2.5};
int barbell[2] = {45, 20};

static void handle_second_tick(struct tm *tick_time, TimeUnits units_changed)
{
  if (units_changed & MINUTE_UNIT)
  {
    clock_copy_time_string(s_time_text, sizeof(s_time_text));
    text_layer_set_text(time_layer, s_time_text);
  }
}

static void select_click_handler(ClickRecognizerRef recognize, void *context) {
  ftoa(weight_buff, weight, 2);
  text_layer_set_text(weight_layer, weight_buff);
  //persist_write_int(m_weight_d*10);
  num_sets_init();
  window_stack_push(num_sets_window, false);
}

static void up_click_handler(ClickRecognizerRef recognize, void *context) {
  weight = weight + step_size[unit_system];

  if (weight > max_weight) {
    weight = barbell[unit_system];
  }
  
  ftoa(weight_buff, weight, 2);
  
  temp = weight;
  if (unit_system == 1 && temp % 5 == 0) {
    strcat(weight_buff,".0");
  }
  text_layer_set_text(weight_layer, weight_buff);
  
}

static void down_click_handler(ClickRecognizerRef recognize, void *context) {
   weight = weight - step_size[unit_system];
  
  if (weight < barbell[unit_system]) {
    weight = max_weight;
  }
  ftoa(weight_buff, weight, 2);
  temp = weight;
  if (unit_system == 1 && temp % 5 == 0) {
    strcat(weight_buff,".0");
  }
  text_layer_set_text(weight_layer, weight_buff);
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
  
  // Create "Select a Weight" text layer
  text_layer = text_layer_create((GRect) {.origin = {bounds.size.w/2-35, bounds.origin.y+33}, .size = { 70, 60 } });
  text_layer_set_text(text_layer, "Select a Weight");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
  
  ftoa(weight_buff, weight, 2);
  if (unit_system == 1 && temp % 5 == 0) {
    strcat(weight_buff,".0");
  }
  weight_layer = text_layer_create((GRect) {.origin = {bounds.size.w/2-40, bounds.size.h/2-17}, .size = { 80, 28 } });
  text_layer_set_text_alignment(weight_layer, GTextAlignmentCenter);
  text_layer_set_text(weight_layer, weight_buff);
  text_layer_set_font(weight_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(weight_layer));
  
  // Create unit system text layer
  text_layer = text_layer_create((GRect) {.origin = {bounds.size.w/2-35, bounds.size.h/2 + 15}, .size = { 70, 60 } });
  if (unit_system == 0)
  {
    text_layer_set_text(text_layer, "Pounds");
  }
  else
  {
    text_layer_set_text(text_layer, "Kilograms");
  }
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
  
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
  main_window = NULL;
  window_destroy(main_window);
  action_bar_layer_destroy(action_bar_layer);
  gbitmap_destroy(res_up_arrow);
  gbitmap_destroy(res_check_mark);
  gbitmap_destroy(res_down_arrow);
}

void init(void)
{
  if (!main_window)
  {
    main_window = window_create();
    
    // Initialize the action bar layer
    if (unit_system == 1)
    {
      res_up_arrow = gbitmap_create_with_resource(RESOURCE_ID_25_plus);
      res_down_arrow = gbitmap_create_with_resource(RESOURCE_ID_25_minus);
    }
    else
    {
      res_up_arrow = gbitmap_create_with_resource(RESOURCE_ID_5_plus);
      res_down_arrow = gbitmap_create_with_resource(RESOURCE_ID_5_minus);
    }
    
    res_check_mark = gbitmap_create_with_resource(RESOURCE_ID_check_mark);
    
    // Create the action bar
    action_bar_layer = action_bar_layer_create();
    action_bar_layer_add_to_window(action_bar_layer, main_window);
    action_bar_layer_set_background_color(action_bar_layer, GColorBlack);
    action_bar_layer_set_icon(action_bar_layer, BUTTON_ID_UP, res_up_arrow);
    action_bar_layer_set_icon(action_bar_layer, BUTTON_ID_SELECT, res_check_mark);
    action_bar_layer_set_icon(action_bar_layer, BUTTON_ID_DOWN, res_down_arrow);
    layer_add_child(window_get_root_layer(main_window), (Layer *)action_bar_layer);
    
    window_set_click_config_provider(main_window, click_config_provider);
    window_set_window_handlers(main_window, (WindowHandlers)
    {
      .load = window_load,
      .appear = window_appear,
      .unload = window_unload
    });
  }

  window_stack_push(main_window, false);
}

void deinit(void)
{
  text_layer_destroy(time_layer);
  window_destroy(main_window);
}

int main(void)
{
  // set the unit system
  unit_system = 0;
  weight = 185;
  
   // Initialize kg or lbs
  if (unit_system == 0) { unit_type = " lbs"; } 
  else if (unit_system == 1) { unit_type = " kgs"; }
  
  init();
  app_event_loop();
  deinit();
}
