/* 
 * File:   Eda_Menu_Settings.cpp
 * Author: r2d2
 * 
 * Created on January 23, 2017, 6:59 PM
 */

#include "Eda_Menu_Settings.h"
#include "Eda_Menu.h"
#include "Hanabi_Skin.h"
#include "Eda_Menu_Game.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_color.h"

static void draw_font(ALLEGRO_DISPLAY * display, const char * font_name, float x_center , float y_center, 
					float y_size_percent, const char * text, ALLEGRO_COLOR color);

Eda_Menu_Settings::Eda_Menu_Settings(game_configuration_t game_configuration)
{
	static const char * themes[HANABI_NUMBER_THEMES] = {"Classic" , "Pokemon" };
	static const char * resolutions[HANABI_NUMBER_RESOLUTIONS] = {"1024x576", "1152x648", "1280x720", "1366x768", "1600x900", "1920x1080" };
	
	this->available_themes = themes;
	this->available_resolutions = resolutions;
	
	apply = new Eda_Button(0.9, 0.8, 0.045 * 3.75, 0.08, CLUE_BUT_DIR "apply.png", CLUE_BUT_DIR "apply_hover.png", NULL, EDA_BUTTON_APPLY_PRESSED);
	cancel = new Eda_Button(0.9, 0.9, 0.045 * 3.75, 0.08, CLUE_BUT_DIR "cancel.png",CLUE_BUT_DIR "cancel_hover.png", NULL, EDA_BUTTON_CANCEL_PRESSED );
	memory_help = new Eda_Button(0.5, 0.85, 1.2 * 0.045, 1.2 * 0.08, CLUE_BUT_DIR "mem_help.png",CLUE_BUT_DIR "mem_help_hover.png", CLUE_BUT_DIR "mem_help_selection.png", NO_EVENT );

	resolution_arrows[0] = new Eda_Button(0.7, 0.25, 1.2 * 0.045, 1.2 * 0.08, CLUE_BUT_DIR "arrow_right.png",CLUE_BUT_DIR "arrow_right_hover.png", NULL, NO_EVENT );
	resolution_arrows[1] = new Eda_Button(0.3, 0.25, 1.2 * 0.045, 1.2 * 0.08, CLUE_BUT_DIR "arrow_left.png",CLUE_BUT_DIR "arrow_left_hover.png", NULL, NO_EVENT );
	
	theme_arrows[0] = new Eda_Button(0.7, 0.55, 1.2 * 0.045, 1.2 * 0.08, CLUE_BUT_DIR "arrow_right.png",CLUE_BUT_DIR "arrow_right_hover.png", NULL, NO_EVENT );
	theme_arrows[1] = new Eda_Button(0.3, 0.55, 1.2 * 0.045, 1.2 * 0.08, CLUE_BUT_DIR "arrow_left.png",CLUE_BUT_DIR "arrow_left_hover.png", NULL, NO_EVENT );

	selected_resolution = game_configuration.selected_resolution;
	selected_theme = game_configuration.selected_theme;
	enable_mem_help = game_configuration.memory_help;
	
	if(enable_mem_help)
		memory_help->select();
}

Eda_Menu_Settings::Eda_Menu_Settings(const Eda_Menu_Settings& orig) {
}

Eda_Menu_Settings::~Eda_Menu_Settings() 
{
	delete apply;
	delete cancel;
	delete memory_help;
	delete resolution_arrows[0];
	delete resolution_arrows[1];
	delete theme_arrows[0];
	delete theme_arrows[1];
}


void Eda_Menu_Settings::draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board * game_board)
{
	al_draw_scaled_bitmap(theme->setting_background, 
							0.0, 0.0, al_get_bitmap_width(theme->setting_background), al_get_bitmap_height(theme->setting_background),
							0.0, 0.0, al_get_display_width(display), al_get_display_height(display), //x , y cord to draw and width and height to draw
							0); //flags	
	
	apply->draw(display);
	cancel->draw(display);
	memory_help->draw(display);
	resolution_arrows[0]->draw(display);
	resolution_arrows[1]->draw(display);
	theme_arrows[0]->draw(display);
	theme_arrows[1]->draw(display);
	
	draw_font(display,"AlexBrush-Regular.ttf", 0.5, 0.10 , 0.2, "Resolution", al_color_name("black") );
	draw_font(display,"OpenSans-Regular.ttf", 0.5, 0.23 , 0.1, available_resolutions[selected_resolution], al_color_name("grey") );
	draw_font(display,"OpenSans-Regular.ttf", 0.5, 0.23 , 0.1, available_resolutions[selected_resolution], al_color_name("grey") );
	
	draw_font(display,"AlexBrush-Regular.ttf", 0.5, 0.415 , 0.2, "Theme", al_color_name("black") );
	draw_font(display,"OpenSans-Regular.ttf", 0.5, 0.53 , 0.1, available_themes[selected_theme], al_color_name("grey") );
	
	draw_font(display,"AlexBrush-Regular.ttf", 0.5, 0.7 , 0.2, "Memory Help", al_color_name("black") );
	//draw_font(display,"AlexBrush-Regular.ttf", 0.35, 0.78 , 0.2, "Memory Help", al_color_name("black") );
	al_flip_display();
}


void Eda_Menu_Settings::update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse)
{

	apply->update_hovering(display, x_mouse, y_mouse);
	cancel->update_hovering(display, x_mouse, y_mouse);
	memory_help->update_hovering(display, x_mouse, y_mouse);
	resolution_arrows[0]->update_hovering(display, x_mouse, y_mouse);
	resolution_arrows[1]->update_hovering(display, x_mouse, y_mouse);
	theme_arrows[0]->update_hovering(display, x_mouse, y_mouse);
	theme_arrows[1]->update_hovering(display, x_mouse, y_mouse);


}

bool Eda_Menu_Settings::check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<event_button_t> &button_event_queue)
{
	if( memory_help->check_mouse_over_toggle(display, x_mouse, y_mouse) )
		enable_mem_help = !enable_mem_help;
	
	else if( resolution_arrows[0]->check_mouse_over(display,x_mouse,y_mouse) )
		selected_resolution = (selected_resolution + 1) % HANABI_NUMBER_RESOLUTIONS;
	else if( resolution_arrows[1]->check_mouse_over(display,x_mouse,y_mouse) )
		selected_resolution = (selected_resolution + HANABI_NUMBER_RESOLUTIONS - 1) % HANABI_NUMBER_RESOLUTIONS;
	
	else if( theme_arrows[0]->check_mouse_over(display,x_mouse,y_mouse) )
		selected_theme = (selected_theme + 1) % HANABI_NUMBER_THEMES;
	else if( theme_arrows[1]->check_mouse_over(display,x_mouse,y_mouse) )
		selected_theme = (selected_theme + HANABI_NUMBER_THEMES - 1) % HANABI_NUMBER_THEMES;
	
	else if( apply->check_mouse_over(display, x_mouse, y_mouse) )
		button_event_queue.push( apply->get_click_event() );
	else if( cancel->check_mouse_over(display, x_mouse, y_mouse) )
		button_event_queue.push( cancel->get_click_event() );
}


void draw_font(ALLEGRO_DISPLAY * display, const char * font_name, float x_center , float y_center,
				float y_size_percent, const char * text, ALLEGRO_COLOR color)
{
	ALLEGRO_FONT * font_to_draw;
	unsigned int font_size = y_size_percent * al_get_display_height(display); //cast to int
	font_to_draw = al_load_font(font_name, font_size, 0);
	
	al_draw_text(font_to_draw, color , x_center * al_get_display_width(display), y_center * al_get_display_height(display) - font_size/2, ALLEGRO_ALIGN_CENTRE , text);
	
	al_destroy_font(font_to_draw);
}

#include "allegro5/allegro5.h"
#include <sstream>
#include <iostream>
//To be called on update
void Eda_Menu_Settings::update_game_settings(ALLEGRO_DISPLAY * display, game_configuration_t & game_config)
{
	int width, height;//because allegro used ints 
	//sscanf(available_resolutions[0],"%dx%d\n",&width,&height); //DOESN'T FUCKING WORK WON'T LOAD HEIGHT WHY THE FUCK!!!!
	//FOUND OUT WHY THE FUCKING x in resolutions was not the same as the one in the keyboard FUCK
	
	if(game_config.selected_theme != selected_theme)
	{
		game_config.selected_theme = selected_theme;
		if(game_config.theme_settings != NULL)//couldn't be NULL but just in case
			delete game_config.theme_settings;
			
		game_config.theme_settings = new Hanabi_Skin();
		game_config.theme_settings->load_theme(available_themes[selected_theme]);
	}
	
	
	if(game_config.selected_resolution != selected_resolution)
	{
		game_config.selected_resolution = selected_resolution;
		sscanf(available_resolutions[selected_resolution], "%dx%d",&width, &height);
		
		al_resize_display(display, width, height);
		al_set_target_backbuffer(display);
	}

	game_config.memory_help = enable_mem_help;
	
}
