#include <pebble.h>
#include "master.h"
#include "ftoa.h"
#include "num_sets.h"

#define KEY_UNIT_TYPE 1000
#define KEY_BAR_WEIGHT 2000
#define KEY_w100p 3000
#define KEY_w55p 4000
#define KEY_w45p 5000
#define KEY_w35p 6000
#define KEY_w25p 7000
#define KEY_w10p 8000
#define KEY_w5p 9000
#define KEY_w2point5p 1000
#define KEY_w50k 11000
#define KEY_w25k 12000
#define KEY_w20k 13000
#define KEY_w15k 14000
#define KEY_w10k 15000
#define KEY_w5k 16000
#define KEY_w2point5k 17000
#define KEY_w1point25k 18000

Window *main_window;

TextLayer *time_layer;
TextLayer *text_layer;
TextLayer *weight_layer;

static GBitmap *res_up_arrow;
static GBitmap *res_down_arrow;
static GBitmap *res_check_mark;

static ActionBarLayer *action_bar_layer;

static int max_weight = 10000;
int temp = 0;
static char s_time_text[] = "00:00   ";
char weight_buff[10];
double step_size[2] = {5, 2.5};
int barbell[2] = {45, 20};

// Initialize plate weights for imperial and metric
double plate_weights[8][2] = { {100, 50.00}, {55, 25.00}, {45, 20.00}, {35, 15.00}, {25, 10.00}, {10, 5.00}, {5, 2.50}, {2.5, 1.25} };
int plate_numbers[8][2] =    { {0,   0},     {0,  0},     {20, 20},    {0,  0},     {2,  2},     {4,  4},    {2, 2},    {2,   2}    };

void calc_max_weight(void)
{
  max_weight = 0;
  
  for (int i = 0; i < 8; i++)
  {
    max_weight += plate_numbers[i][unit_system] * plate_weights[i][unit_system];
  }
  
  max_weight += barbell[unit_system];
}

static void inbox_received_handler(DictionaryIterator *iter, void *context)
{
  Tuple *unit_system_t = dict_find(iter, KEY_UNIT_TYPE);
  if (unit_system_t) {
    unit_system = unit_system_t->value->int8;
    persist_write_int(0, unit_system);

    if (unit_system == 0) { unit_type = " lbs"; } 
    else if (unit_system == 1) { unit_type = " kgs"; }
  }
  
  Tuple *bar_weight_t = dict_find(iter, KEY_BAR_WEIGHT);

  if (bar_weight_t) {
    barbell[unit_system] = bar_weight_t->value->int8;
    persist_write_int(1, bar_weight_t->value->int8);
    weight = barbell[unit_system];
  }
  
  Tuple *w100p_t = dict_find(iter, KEY_w100p);
  Tuple *w55p_t = dict_find(iter, KEY_w55p);
  Tuple *w45p_t = dict_find(iter, KEY_w45p);
  Tuple *w35p_t = dict_find(iter, KEY_w35p);
  Tuple *w25p_t = dict_find(iter, KEY_w25p);
  Tuple *w10p_t = dict_find(iter, KEY_w10p);
  Tuple *w5p_t = dict_find(iter, KEY_w5p);
  Tuple *w2point5p_t = dict_find(iter, KEY_w2point5p);
  
  if (w100p_t)
  {
    plate_numbers[0][0] = (w100p_t->value->int16);
    persist_write_int(KEY_w100p, w100p_t->value->int16);
  }
  if (w55p_t)
  {
    plate_numbers[1][0] = (w55p_t->value->int16);
    persist_write_int(KEY_w55p, w55p_t->value->int16);
  }
  if (w45p_t)
  {
    plate_numbers[2][0] = (w45p_t->value->int16);
    persist_write_int(KEY_w45p, w45p_t->value->int16);
  }
  if (w35p_t)
  {
    plate_numbers[3][0] = (w35p_t->value->int16);
    persist_write_int(KEY_w35p, w35p_t->value->int16);
  }
  if (w25p_t)
  {
    plate_numbers[4][0] = (w25p_t->value->int16);
    persist_write_int(KEY_w25p, w25p_t->value->int16);
  }
  if (w10p_t)
  {
    plate_numbers[5][0] = (w10p_t->value->int16);
    persist_write_int(KEY_w10p, w10p_t->value->int16);
  }
  if (w5p_t)
  {
    plate_numbers[6][0] = (w5p_t->value->int16);
    persist_write_int(KEY_w5p, w5p_t->value->int16);
  }
  if (w2point5p_t)
  {
    plate_numbers[7][0] = (w2point5p_t->value->int16);
    persist_write_int(KEY_w2point5p, w2point5p_t->value->int16);
  }
  
  Tuple *w50k_t = dict_find(iter, KEY_w50k);
  Tuple *w25k_t = dict_find(iter, KEY_w25k);
  Tuple *w20k_t = dict_find(iter, KEY_w20k);
  Tuple *w15k_t = dict_find(iter, KEY_w15k);
  Tuple *w10k_t = dict_find(iter, KEY_w10k);
  Tuple *w5k_t = dict_find(iter, KEY_w5k);
  Tuple *w2point5k_t = dict_find(iter, KEY_w2point5k);
  Tuple *w1point25k_t = dict_find(iter, KEY_w1point25k);
  
  if (w50k_t)
  {
    plate_numbers[0][1] = (w50k_t->value->int16);
    persist_write_int(KEY_w50k, w50k_t->value->int16);
  }
  if (w25k_t)
  {
    plate_numbers[1][1] = (w25k_t->value->int16);
    persist_write_int(KEY_w25k, w25k_t->value->int16);
  }
  if (w20k_t)
  {
    plate_numbers[2][1] = (w20k_t->value->int16);
    persist_write_int(KEY_w20k, w20k_t->value->int16);
  }
  if (w15k_t)
  {
    plate_numbers[3][1] = (w15k_t->value->int16);
    persist_write_int(KEY_w15k, w15k_t->value->int16);
  }
  if (w10k_t)
  {
    plate_numbers[4][1] = (w10k_t->value->int16);
    persist_write_int(KEY_w10k, w10k_t->value->int16);
  }
  if (w5k_t)
  {
    plate_numbers[5][1] = (w5k_t->value->int16);
    persist_write_int(KEY_w5k, w5k_t->value->int16);
  }
  if (w2point5k_t)
  {
    plate_numbers[6][1] = (w2point5k_t->value->int16);
    persist_write_int(KEY_w2point5k, w2point5k_t->value->int16);
  }
  if (w1point25k_t)
  {
    plate_numbers[7][1] = (w1point25k_t->value->int16);
    persist_write_int(KEY_w1point25k, w1point25k_t->value->int16);
  }
  
  calc_max_weight();
}

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
  
  app_message_register_inbox_received(inbox_received_handler);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

void deinit(void)
{
  text_layer_destroy(time_layer);
  window_destroy(main_window);
}

void load_settings(void)
{
  // Load unit system
  if (persist_exists(0))
  {
    unit_system = persist_read_int(0);
  }
  else
  {
    unit_system = 0;
  }
  
  // Load barbell weight
  if (persist_exists(1))
  {
    barbell[unit_system] = persist_read_int(1);
  }
  else
  {
    if (unit_system == 0)
    {
      barbell[unit_system] = 45;
    }
    else if (unit_system == 1)
    {
      barbell[unit_system] = 20;
    }
  }
  
  // Load imperial plate numbers
  if (persist_exists(KEY_w100p))
  {
    plate_numbers[0][0] = persist_read_int(KEY_w100p);
  }
  if (persist_exists(KEY_w55p))
  {
    plate_numbers[0][0] = persist_read_int(KEY_w55p);
  }
  if (persist_exists(KEY_w45p))
  {
    plate_numbers[0][0] = persist_read_int(KEY_w45p);
  }
  if (persist_exists(KEY_w35p))
  {
    plate_numbers[0][0] = persist_read_int(KEY_w35p);
  }
  if (persist_exists(KEY_w25p))
  {
    plate_numbers[0][0] = persist_read_int(KEY_w25p);
  }
  if (persist_exists(KEY_w10p))
  {
    plate_numbers[0][0] = persist_read_int(KEY_w10p);
  }
  if (persist_exists(KEY_w5p))
  {
    plate_numbers[0][0] = persist_read_int(KEY_w5p);
  }
  if (persist_exists(KEY_w2point5p))
  {
    plate_numbers[0][0] = persist_read_int(KEY_w2point5p);
  }

  // Load imperial plate numbers
  if (persist_exists(KEY_w50k))
  {
    plate_numbers[0][1] = persist_read_int(KEY_w50k);
  }
  if (persist_exists(KEY_w25k))
  {
    plate_numbers[1][1] = persist_read_int(KEY_w25k);
  }
  if (persist_exists(KEY_w20k))
  {
    plate_numbers[2][1] = persist_read_int(KEY_w20k);
  }
  if (persist_exists(KEY_w15k))
  {
    plate_numbers[3][1] = persist_read_int(KEY_w15k);
  }
  if (persist_exists(KEY_w10k))
  {
    plate_numbers[4][1] = persist_read_int(KEY_w10k);
  }
  if (persist_exists(KEY_w5k))
  {
    plate_numbers[5][1] = persist_read_int(KEY_w5k);
  }
  if (persist_exists(KEY_w2point5k))
  {
    plate_numbers[6][1] = persist_read_int(KEY_w2point5k);
  }
  if (persist_exists(KEY_w1point25k))
  {
    plate_numbers[7][1] = persist_read_int(KEY_w1point25k);
  }
  
}

int main(void)
{
  load_settings();
  calc_max_weight();
  weight = 100;
  
   // Initialize kg or lbs
  if (unit_system == 0) { unit_type = " lbs"; } 
  else if (unit_system == 1) { unit_type = " kgs"; }
  
  init();
  app_event_loop();
  deinit();
}
