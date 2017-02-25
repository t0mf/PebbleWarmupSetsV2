#include <pebble.h>
#include <math.h>
#include "sets.h"
#include "master.h"
#include "mini-printf.h"
#include "ftoa.h"
#include "math.h"
//#include "timer.h"

static MenuLayer *s_menu_layer;
static TextLayer *s_list_message_layer;
static TextLayer *s_list_message_layer2;
static TextLayer *s_time_layer;

static int baseSet[2] = {1, 10};
char plates[16][16];
double set_percentages[15];
int weights[15+2];
int numReps[15][15] = 
  {
    { 5 },
    { 5, 3 },
    { 5, 3, 2 },
    { 5, 4, 3, 2 },
    { 5, 4, 3, 2, 1 },
    { 5, 4, 3, 2, 1, 1 },
    { 5, 4, 3, 2, 2, 1, 1 },
    { 5, 4, 3, 3, 2, 2, 1, 1 },
    { 5, 4, 4, 3, 3, 2, 2, 1, 1 },
    { 5, 5, 4, 4, 3, 3, 2, 2, 1, 1 },
    { 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 1 },
    { 5, 5, 4, 4, 3, 3, 2, 2, 2, 1, 1, 1 },
    { 5, 5, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1 },
    { 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1 },
    { 5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1}
  };

char sets_buff[15];
int head = 0, ret;

static char s_time_text[] = "00:00   ";

// Method handles changing the clock every minute
static void handle_second_tick(struct tm *tick_time, TimeUnits units_changed)
{
  if (units_changed & MINUTE_UNIT)
  {
      clock_copy_time_string(s_time_text, sizeof(s_time_text));
      text_layer_set_text(s_time_layer,s_time_text);
  }
}

static void select_click(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{
  //init_timer_window();
  //window_stack_push(s_timer_window, false);
}

static uint16_t get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *context)
{
  return sets + 2;
}

static void draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *context)
{
  char buff1[10];
  char buff2[10];
  char buff3[10];
  static char s_buff4[20];
  static char s_buff5[20];
  
  if (cell_index->row == 0)
  {
    
    ftoa(buff1, baseSet[0], 0);
    ftoa(buff2, baseSet[1], 0);
    ftoa(buff3, weights[cell_index->row], 0);
    
    snprintf(s_buff4, sizeof(s_buff4), "%sx%s %s %s", buff1, buff2, buff3, unit_type);
    snprintf(s_buff5, sizeof(s_buff5), "(%s )", "Bar");
  }
  else if (cell_index->row == sets + 1)
  {
    ftoa(buff1, weights[cell_index->row], 0);
    
    snprintf(s_buff4, sizeof(s_buff4), "%s %s", buff1, unit_type);
    snprintf(s_buff5, sizeof(s_buff5), "(%s )", plates[cell_index->row-1]);
  }
  else
  {
    ftoa(buff2, numReps[sets-1][cell_index->row-1], 0);
    ftoa(buff3, weights[cell_index->row], 3);
    
    snprintf(s_buff4, sizeof(s_buff4), "1x%s %s %s", buff2, buff3, unit_type);
    snprintf(s_buff5, sizeof(s_buff5), "(%s )", plates[cell_index->row-1]);
  }
   
    //snprintf(s_buff4, sizeof(s_buff4), ""%s %s %s", sets[cell_index->row], sets_buff, unit_type);
    //snprintf(s_buff5, sizeof(s_buff5), "(%s )", plates[cell_index->row]);"
    menu_cell_basic_draw(ctx, cell_layer, s_buff4, s_buff5, NULL);
}

static int16_t get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
  return PBL_IF_ROUND_ELSE(
    menu_layer_is_index_selected(menu_layer, cell_index) ?
      MENU_CELL_ROUND_FOCUSED_SHORT_CELL_HEIGHT : MENU_CELL_ROUND_UNFOCUSED_TALL_CELL_HEIGHT,
    50);
}

void calculate_percentages(void)
{
  //float percentage = ;
  
  for (int i = 0; i < sets; i++)
  {
    set_percentages[i] = (i+1)*(100/(sets+1));
  }
}

void calculate_weights(void)
{
  for (int i = 0; i < sets + 2; i++)
  {
    if (i == 0)
    {
      weights[i] = barbell[unit_system];
    }
    else if (i == sets+1)
    {
      weights[i] = weight;
    }
    else
    {
      int temp;
      temp = (set_percentages[i-1]/100) * weight;
      if (temp < barbell[unit_system])
      {
        temp = barbell[unit_system];
      }
      while (temp % 5 != 0)
      {
          temp = temp + 1;
      }
      
      weights[i] = temp;
    }
  }
}

static void sets_window_load(Window *window) {
  
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  s_menu_layer = menu_layer_create(GRect(bounds.origin.x, bounds.origin.y+20, bounds.size.w, 137));
  menu_layer_set_click_config_onto_window(s_menu_layer, window);
  menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks) {
      .get_num_rows = get_num_rows_callback,
      .draw_row = draw_row_callback,
      .get_cell_height = get_cell_height_callback,
      .select_click = select_click
  });
  layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
  
  /*
  const GEdgeInsets message_insets = {.top = 137};
  s_list_message_layer = text_layer_create(grect_inset(bounds, message_insets));
  text_layer_set_text_alignment(s_list_message_layer, GTextAlignmentCenter);
  //if (exercise_int == 6) {
    text_layer_set_text(s_list_message_layer, "Plate Math");
  //} else {
   // text_layer_set_text(s_list_message_layer, exercise_name_strings[exercise_int]);
  //}
  layer_add_child(window_layer, text_layer_get_layer(s_list_message_layer));
  */
  static char s_buff4[16];
  ftoa(sets_buff, weight, 5);
  snprintf(s_buff4, sizeof(s_buff4), "%s %s", sets_buff, unit_type);
  const GEdgeInsets message_insets2 = {.top = 152};
  s_list_message_layer2 = text_layer_create(grect_inset(bounds, message_insets2));
  text_layer_set_text_alignment(s_list_message_layer2, GTextAlignmentCenter);
  text_layer_set_text(s_list_message_layer2,s_buff4);
  layer_add_child(window_layer, text_layer_get_layer(s_list_message_layer2));
  
  s_time_layer = text_layer_create((GRect) {.origin = {bounds.size.w/2-30, bounds.origin.y+5}, .size = { 60, 15 } });
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
  
}

static void sets_window_appear(Window *window) {
  clock_copy_time_string(s_time_text, sizeof(s_time_text));
  text_layer_set_text(s_time_layer,s_time_text);
  tick_timer_service_subscribe(SECOND_UNIT, handle_second_tick);
}

static void sets_window_unload(Window *window) {
  sets_window = NULL;
  window_destroy(sets_window);
}

void sets_init(void) {
  calculate_percentages();
  calculate_weights();
  if(!sets_window) {
    sets_window = window_create();
    window_set_window_handlers(sets_window, (WindowHandlers) {
        .load = sets_window_load,
        .appear = sets_window_appear,
        .unload = sets_window_unload,
    });
  }
  
  //calculate_sets();
  //calculate_weights();
  //do_stuff();
  window_stack_push(sets_window, false);  
}



/*
void calculate_sets(void) {
  for (int i = 0; i < 5; i++) {
    //sets[i] = exercise_set_strings[exercise_int][i]; 
  }
}

void calculate_weights(void) {
  if (strcmp(exercise_name_strings[exercise_int],"Deadlift") == 0) {
    for (int i = 0; i < 4; i++) {
      weights[i] = findWeight(exercise_multipliers[exercise_int][i] *m_weight_d);
    }
  } else {
    for (int i = 0; i < 5; i++) {
      weights[i] = findWeight(exercise_multipliers[exercise_int][i] *m_weight_d);
    }
  }
}

double findWeight(double num) {
  int tmp = num;
  if (unit_system == 0) {
    if ((tmp - (tmp % 5)) < barbell_weights[unit_system])
      return barbell_weights[unit_system];
    else
    return (tmp - (tmp % 5));
  } else if (unit_system == 1) {
      num /= 2.5;
      num = floor(num);
      num *= 2.5;
      if (num < barbell_weights[unit_system])
        return barbell_weights[unit_system];
      return num;
  }
  return -1;
}

void calculate_barbell_math(double weight, int i) {

  double bar_weight = barbell_weights[unit_system];
  
  weight -= bar_weight;
  
  if ( weight == 0) { strcpy(plates[i]," Bar"); }
  
  weight /= 2;
  
  int weight_45 = 0;
  int weight_35 = 0;
  int weight_25 = 0;
  int weight_10 = 0;
  int weight_5 = 0;
  int weight_2half = 0;
    
  while (weight > 0) {
    if (weight < plate_weights[4][unit_system]) {
      weight_2half += 1;
      weight -= plate_weights[5][unit_system];
    } else if (weight < plate_weights[3][unit_system]) {
      weight_5 += 1;
      weight -= plate_weights[4][unit_system];
    } else if (weight < plate_weights[2][unit_system]) {
      weight_10 += 1;
      weight -= plate_weights[3][unit_system];
    } else if (weight < plate_weights[1][unit_system]) {
      weight_25 += 1;
      weight -= plate_weights[2][unit_system];
    } else if (weight < plate_weights[0][unit_system]) {
      weight_35 += 1;
      weight -= plate_weights[1][unit_system];
    } else if (weight >= plate_weights[0][unit_system]) {
      weight_45 += 1;
      weight -= plate_weights[0][unit_system];
    }  
  }
  
  head = 0;
  
  if (weight_45 != 0) { concatPlates(weight_45, i, plate_weights[0][unit_system]); }
  if (weight_35 != 0) { concatPlates(weight_35, i, plate_weights[1][unit_system]); }
  if (weight_25 != 0) { concatPlates(weight_25, i, plate_weights[2][unit_system]); }
  if (weight_10 != 0) { concatPlates(weight_10, i, plate_weights[3][unit_system]); }
  if (weight_5 != 0) { concatPlates(weight_5, i, plate_weights[4][unit_system]); }
  if (weight_2half != 0) { concatPlates(weight_2half, i, plate_weights[5][unit_system]); }
  
}

void concatPlates(int plateNumber, int i, double plateWeights) {
  ftoa(sets_buff, plateWeights, 5);
    if (plateNumber > 1) {
      ret = snprintf(plates[i] + head, 10, " %dx%s" , plateNumber, sets_buff);
      head += ret;
    } else {
      ret = snprintf(plates[i] + head, 6, " %s", sets_buff);
      head += ret;
    }
}

void do_stuff(void) {
  for (int i = 0; i < 5; i++) {
    calculate_barbell_math(weights[i], i);
  }
}



*/











