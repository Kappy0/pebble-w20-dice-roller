#include <pebble.h>

Window *window;
TextLayer *textLayer;
TextLayer *clickLayer;

static void main_window_load(Window *window) 
{
	// Get information about the Window
	Layer *windowLayer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(windowLayer);
	
	// Create the TextLayer with specific bounds
	textLayer = text_layer_create(GRect(0, 25, bounds.size.w - 30, 50));
	clickLayer = text_layer_create(GRect(100, 25, bounds.size.w - 30, 50));
	
	// textLayer
	text_layer_set_background_color(textLayer, GColorClear);
	text_layer_set_text_color(textLayer, GColorBlack);
	text_layer_set_text(textLayer, "Number of Dice: ");
	text_layer_set_font(textLayer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
	text_layer_set_text_alignment(textLayer, GTextAlignmentCenter);
	
	// clickLayer
	text_layer_set_text_color(clickLayer, GColorBlack);
	text_layer_set_text(clickLayer, "10");
	text_layer_set_font(clickLayer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
	text_layer_set_text_alignment(textLayer, GTextAlignmentCenter);
	
	// Add it as a child layer to the Window's root layer
	layer_add_child(windowLayer, text_layer_get_layer(textLayer));
	layer_add_child(windowLayer, text_layer_get_layer(clickLayer));
}

static void main_window_unload(Window *window) 
{
	// Destroy TextLayer
	text_layer_destroy(textLayer);
	text_layer_destroy(clickLayer);
}

static void init() 
{
	// Create main Window element and assign to pointer
	window = window_create();
	
	// Set handlers to manage the elements inside the Window
	window_set_window_handlers(window, (WindowHandlers)
	{
		.load = main_window_load,
		.unload = main_window_unload
	});
	
	// Show the Window on the watch, with animated=true
	window_stack_push(window, true);
}

static void deinit(void)
{
	window_destroy(window);
}

int main(void) 
{
	init();
	app_event_loop();
	deinit();
}
