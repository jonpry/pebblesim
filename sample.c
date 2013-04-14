#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

//#define FOR_PEBBLE 
#ifdef FOR_PEBBLE
#define MY_UUID { 0x3C, 0x05, 0xAD, 0x9F, 0xE6, 0x98, 0x4B, 0x64, 0x91, 0xAB, 0x4D, 0x80, 0x10, 0xF4, 0xFD, 0x38 }
PBL_APP_INFO(MY_UUID,
             "Sample", "Pry Mfg Co",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);
#endif 

#define DISPLAY_W 144
#define DISPLAY_H 168

Window window;
Layer display_layer;

void display_layer_update_callback(Layer *me, GContext* ctx) {
 	(void)me;
	PblTm t;

	graphics_context_set_fill_color(ctx, GColorWhite);
	graphics_context_set_stroke_color(ctx, GColorWhite);

	GPoint center;
	center.x = DISPLAY_W/2;
	center.y = DISPLAY_H/2;
	graphics_draw_circle(ctx,center,DISPLAY_W/2);
}

void handle_second_tick(AppContextRef ctx, PebbleTickEvent *t) {

  (void)t; // TODO: Pass the time direct to the layers?
  (void)ctx;

  layer_mark_dirty(&display_layer);
}

void handle_init(AppContextRef ctx) {
	(void)ctx;
 	int i;

	window_init(&window, "Rotations");
	window_stack_push(&window, true);
	window_set_background_color(&window, GColorBlack);

  	// Init the layer for display
  	layer_init(&display_layer, window.layer.frame);
  	display_layer.update_proc = &display_layer_update_callback;
  	layer_add_child(&window.layer, &display_layer);

}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,

    // Handle time updates
    .tick_info = {
      .tick_handler = &handle_second_tick,
      .tick_units = SECOND_UNIT
    }

  };
  app_event_loop(params, &handlers);
}
