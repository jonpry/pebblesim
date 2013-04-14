#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include <math.h>

#define DISPLAY_W 144
#define DISPLAY_H 196
uint8_t display[DISPLAY_W][DISPLAY_H];

void graphics_context_set_stroke_color(GContext *ctx, GColor color){

}

void graphics_context_set_fill_color(GContext *ctx, GColor color){

}

void graphics_draw_pixel(GContext *ctx, GPoint p){
	if(p.x < 0 || p.x >= DISPLAY_W)
		return;
	if(p.y < 0 || p.y >= DISPLAY_H)
		return; 
	display[p.x][p.y] = '1';
}

void setPixel(int x, int y){
	GPoint p;
	p.x = x; p.y = y;
	graphics_draw_pixel(0,p);
}

void rasterCircle(int x0, int y0, int radius)
{
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;
 
  setPixel(x0, y0 + radius);
  setPixel(x0, y0 - radius);
  setPixel(x0 + radius, y0);
  setPixel(x0 - radius, y0);
 
  while(x < y)
  {
    // ddF_x == 2 * x + 1;
    // ddF_y == -2 * y;
    // f == x*x + y*y - radius*radius + 2*x - y + 1;
    if(f >= 0) 
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;    
    setPixel(x0 + x, y0 + y);
    setPixel(x0 - x, y0 + y);
    setPixel(x0 + x, y0 - y);
    setPixel(x0 - x, y0 - y);
    setPixel(x0 + y, y0 + x);
    setPixel(x0 - y, y0 + x);
    setPixel(x0 + y, y0 - x);
    setPixel(x0 - y, y0 - x);
  }
}

void graphics_draw_circle(GContext *ctx, GPoint p, int radius){
	rasterCircle(p.x,p.y,radius);
}

void graphics_draw_line(GContext *ctx, GPoint a, GPoint b){
	printf("Line %d,%d %d,%d\n", a.x,a.y,b.x,b.y);

	GPoint dab, sab, ab;

  	dab.x = abs(b.x-a.x); sab.x = a.x<b.x ? 1 : -1;
  	dab.y = abs(b.y-a.y); sab.y = a.y<b.y ? 1 : -1; 
  	int eab = (dab.x>dab.y ? dab.x : -dab.y)/2;
	int eab2;
 
	ab = a;
  	for(;;){
    		graphics_draw_pixel(ctx,ab);
    		if (ab.x==b.x && ab.y==b.y) break;
    		eab2 = eab;
    		if (eab2 >-dab.x) { eab -= dab.y; ab.x += sab.x; }
    		if (eab2 < dab.y) { eab += dab.x; ab.y += sab.y; }
  	}
}

void get_time(PblTm *time){
	printf("Get time\n");
	time->tm_hour = 1;
}

void window_init(Window *window, const char *debug_name){

}

void window_stack_push(Window *window, bool animated){

}

void window_set_background_color(Window *window, GColor background_color){

}

void layer_mark_dirty(Layer *layer){

}

void layer_add_child(Layer *parent, Layer *child){

}

void layer_init(Layer *layer, GRect frame){

}

void app_event_loop(AppTaskContextRef app_task_ctx, PebbleAppHandlers *handlers){

}

void display_layer_update_callback(Layer *me, GContext* ctx);
void convert(uint8_t image[144][196], char* outfile);
void main(){
	int x,y;
	for(x=0; x < DISPLAY_W; x++){
		for(y=0; y < DISPLAY_H; y++)
			display[x][y] = '0';
	}

	handle_init();
	display_layer_update_callback(0,0);

	for(y=0; y < DISPLAY_H; y++){
		for(x=0; x < DISPLAY_W; x++){
			printf("%c",display[x][y]);
		}
		printf("\n");
	}

	convert(display,"out.bmp");

}

