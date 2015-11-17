#include <pebble.h>

Window *window;

//Set up text layers
TextLayer *textLayer1; //textLayer1 will be used for numDice and numSuccesses
TextLayer *textLayer2; //textLayer2 will be used for difficulty and num1's
//TextLayer *textLayer3; //textLayer3 will used for number of explosions
//TextLayer *textLayer4; //textLayer4 will be used for number of total successes

//Set up click layers
TextLayer *clickNumDiceLayer;
TextLayer *clickDifficultyLayer;

//Set up integer "state" variable
//0 = Select Num Dice
//1 = Select Difficulty
//2 = Display Results
int state = 0; 

//Set up result variables
int numOne = 0, numExplosions = 0, numSuccess = 0;

//Set up dice and difficulty variables
int numDice = 0, difficultyNum = 0;

//Buffers used to print numDice and difficultyNum
static char diceBuffer[] = "00000000000";
static char difficultyBuffer[] = "00000000000";

static void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
	text_layer_set_text(textLayer1, "");
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context)
{
	numDice++;
	snprintf(diceBuffer, sizeof(diceBuffer), "%d", numDice);
	text_layer_set_text(clickNumDiceLayer, diceBuffer);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context)
{
	numDice--;
	snprintf(diceBuffer, sizeof(diceBuffer), "%d", numDice);
	text_layer_set_text(clickNumDiceLayer, diceBuffer);
}

static void click_config_provider(void *context)
{
	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
	window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
	window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void main_window_load(Window *window) 
{
	//Get information about the Window
	Layer *windowLayer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(windowLayer);
	
	//Create the TextLayer with specific bounds
	textLayer1 = text_layer_create(GRect(0, 25, bounds.size.w - 30, 50));
	textLayer2 = text_layer_create(GRect(-15, 40, bounds.size.w - 30, 50));
	clickNumDiceLayer = text_layer_create(GRect(100, 25, bounds.size.w - 30, 50));
	clickDifficultyLayer = text_layer_create(GRect(100, 40, bounds.size.w - 30, 50));
	
	//textLayer1
	text_layer_set_background_color(textLayer1, GColorClear);
	text_layer_set_text_color(textLayer1, GColorBlack);
	text_layer_set_text(textLayer1, "Number of Dice: ");
	text_layer_set_font(textLayer1, fonts_get_system_font(FONT_KEY_GOTHIC_14));
	text_layer_set_text_alignment(textLayer1, GTextAlignmentCenter);
	
	//textLayer2
	text_layer_set_background_color(textLayer2, GColorClear);
	text_layer_set_text_color(textLayer2, GColorBlack);
	text_layer_set_text(textLayer2, "Difficulty: ");
	text_layer_set_font(textLayer2, fonts_get_system_font(FONT_KEY_GOTHIC_14));
	text_layer_set_text_alignment(textLayer2, GTextAlignmentCenter);
	
	//clickNumLayer
	text_layer_set_text_color(clickNumDiceLayer, GColorBlack);
	snprintf(diceBuffer, sizeof(diceBuffer), "%d", numDice);
	text_layer_set_text(clickNumDiceLayer, diceBuffer);
	text_layer_set_font(clickNumDiceLayer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
	
	//clickDifficultyLayer
	text_layer_set_text_color(clickDifficultyLayer, GColorBlack);
	snprintf(difficultyBuffer, sizeof(difficultyBuffer), "%d", difficultyNum);
	text_layer_set_text(clickDifficultyLayer, difficultyBuffer);
	text_layer_set_font(clickDifficultyLayer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
	
	//Add text layer as a child layer to the Window's root layer
	layer_add_child(windowLayer, text_layer_get_layer(textLayer1));
	layer_add_child(windowLayer, text_layer_get_layer(textLayer2));
	layer_add_child(windowLayer, text_layer_get_layer(clickNumDiceLayer));
	layer_add_child(windowLayer, text_layer_get_layer(clickDifficultyLayer));
}

static void main_window_unload(Window *window) 
{
	//Destroy text layers
	text_layer_destroy(textLayer1);
	text_layer_destroy(textLayer2);
	text_layer_destroy(clickNumDiceLayer);
	text_layer_destroy(clickDifficultyLayer);
}

static void init() 
{
	//Create main Window element and assign to pointer
	window = window_create();
	
	//Set handlers to manage the elements inside the Window
	window_set_window_handlers(window, (WindowHandlers)
	{
		.load = main_window_load,
		.unload = main_window_unload
	});
	
	window_set_click_config_provider(window, click_config_provider);
	
	//Show the Window on the watch, with animated=true
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
