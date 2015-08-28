#include <pebble.h>

Window *my_window;
TextLayer *hour_layer, *minute_layer_1, *minute_layer_2;
static GFont s_hour_font, s_minute_font;
static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  static char hbuffer[] = "00";
  static char mbuffer[] = "00";
  
  static char textten[] = "seventeen ";
  static char textone[] = "seventeen ";
  //static char fulltext[] = "fourty seven ";
    
  
  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) { strftime(hbuffer, sizeof("00"), "%H", tick_time); } 
  else { strftime(hbuffer, sizeof("00"), "%I", tick_time); }
  // Remove trailing zero
  if (hbuffer[0] == '0') 
    memmove(hbuffer, hbuffer+1, strlen(hbuffer));
  text_layer_set_text(hour_layer, hbuffer);

  strftime(mbuffer, sizeof("00"), "%M", tick_time);
  int minutes   = atoi(mbuffer);
  int quotient  = minutes/10;
  int remainder = minutes%10;
  
  if (minutes < 20) {
    strcpy(textten, "");
    switch (minutes) {
      case 0 :
        strcpy(textone, "o'clock");
        break;
      case 1 :
        strcpy(textone, " one");
        break;
      case 2 :
        strcpy(textone, " two");
        break;
      case 3 :
        strcpy(textone, " three");
        break;
      case 4 :
        strcpy(textone, " four");
        break;
      case 5 :
        strcpy(textone, " five");
        break;
      case 6 :
        strcpy(textone, " six");
        break;
      case 7 :
        strcpy(textone, " seven");
        break;
      case 8 :
        strcpy(textone, " eight");
        break;
      case 9 :
        strcpy(textone, " nine");
        break;
      case 10 :
        strcpy(textone, " ten");
        break;
      case 11 :
        strcpy(textone, " eleven");
        break;
      case 12 :
        strcpy(textone, " twelve");
        break;
      case 13 :
        strcpy(textone, " thirteen");
        break;
      case 14 :
        strcpy(textone, " fourteen");
        break;
      case 15 :
        strcpy(textone, " fifteen");
        break;
      case 16 :
        strcpy(textone, " sixteen");
        break;
      case 17 :
        strcpy(textone, " seventeen");
        break;
      case 18 :
        strcpy(textone, " eightteen");
        break;
      case 19 :
        strcpy(textone, " nineteen");
        break;
    }
    text_layer_set_text(minute_layer_1, textone);
    text_layer_set_text(minute_layer_2, "");
  }
  else {
   switch (quotient){
    case 0: 
      strcpy(textten, "");
      break;
    case 1: 
      strcpy(textten, "ten");
      break;
    case 2: 
      strcpy(textten, "twenty");
      break;
    case 3: 
      strcpy(textten, "thirty");
      break;
    case 4: 
      strcpy(textten, "fourty");
      break;
    case 5: 
      strcpy(textten, "fifty");
      break;
    default:
      strcpy(textten, "dunno..");
      break;
   }
    switch (remainder) {
      case 0 :
        if (quotient == 0) { strcpy(textone, "oh"); }
        else { strcpy(textone, ""); }
        break;
      case 1 :
        strcpy(textone, " one");
        break;
      case 2 :
        strcpy(textone, " two");
        break;
      case 3 :
        strcpy(textone, " three");
        break;
      case 4 :
        strcpy(textone, " four");
        break;
      case 5 :
        strcpy(textone, " five");
        break;
      case 6 :
        strcpy(textone, " six");
        break;
      case 7 :
        strcpy(textone, " seven");
        break;
      case 8 :
        strcpy(textone, " eight");
        break;
      case 9 :
        strcpy(textone, " nine");
        break;
    }
    text_layer_set_text(minute_layer_1, textten);
    //strcat(fulltext, "\n");
    //strcat(fulltext,textone);
    text_layer_set_text(minute_layer_2, textone);
  }  
  //strcpy(fulltext,textten);
  
}  


static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}



void handle_init(void) {
  my_window = window_create();

  s_background_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  #ifdef PBL_COLOR
    s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ONEPLUS_BACKGROUND_COLOR);
  #else
    s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ONEPLUS_BACKGROUND_BW);
  #endif
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
  bitmap_layer_set_background_color(s_background_layer, GColorBlack);
  layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(s_background_layer));
  
  hour_layer   = text_layer_create(GRect(32, 35, 80, 70));
  minute_layer_1 = text_layer_create(GRect(4, 95, 140, 35));
  minute_layer_2 = text_layer_create(GRect(0, 125, 144, 35));
  text_layer_set_text_color(hour_layer, GColorWhite);
  #ifdef PBL_COLOR
    text_layer_set_text_color(minute_layer_1, GColorLightGray);
    text_layer_set_text_color(minute_layer_2, GColorLightGray);
  #else  
    text_layer_set_text_color(minute_layer_1, GColorWhite);
    text_layer_set_text_color(minute_layer_2, GColorWhite);
  #endif
  text_layer_set_background_color(hour_layer,GColorClear);
  text_layer_set_background_color(minute_layer_1,GColorClear);
  text_layer_set_background_color(minute_layer_2,GColorClear);
  
  
  s_hour_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_OCRA_EXTENDED_36));
  text_layer_set_font(hour_layer, s_hour_font);
  text_layer_set_text_alignment(hour_layer, GTextAlignmentCenter);
  
  s_minute_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_LATO_REGULAR_24));
  text_layer_set_font(minute_layer_1, s_minute_font);
  text_layer_set_font(minute_layer_2, s_minute_font);
  //text_layer_set_font(minute_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
  text_layer_set_text_alignment(minute_layer_1, GTextAlignmentCenter);
  text_layer_set_text_alignment(minute_layer_2, GTextAlignmentCenter);
  
  layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(hour_layer));
  layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(minute_layer_1));
  layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(minute_layer_2));
  window_stack_push(my_window, true);
  
  // Make sure the time is displayed from the start
  update_time();
  
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}


void handle_deinit(void) {
  fonts_unload_custom_font(s_minute_font);
  text_layer_destroy(hour_layer);
  text_layer_destroy(minute_layer_1);
  text_layer_destroy(minute_layer_2);
  gbitmap_destroy(s_background_bitmap);
  bitmap_layer_destroy(s_background_layer);
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}

