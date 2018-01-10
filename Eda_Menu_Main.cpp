/* 
 * File:   Eda_Menu_Main.cpp
 * Author: r2d2
 * 
 * Created on January 21, 2017, 11:32 PM
 */

#include "Eda_Menu_Main.h"
#include "Eda_Button.h"
#include "setting_management.h"


Eda_Menu_Main::Eda_Menu_Main(std::string theme): 
	play(0.5, 0.6, 0.10, 0.08 ,(COMMON_FILE_PATH "/play.png"), (COMMON_FILE_PATH "/play_glow.png"), NULL, EDA_BUTTON_PLAY_PRESSED),
	settings(0.5, 0.70, 0.20, 0.08 ,(COMMON_FILE_PATH "/settings.png"),(COMMON_FILE_PATH "/settings_glow.png"), NULL, EDA_BUTTON_SETT_PRESSED ),
	quit(0.5, 0.80, 0.10, 0.08 ,(COMMON_FILE_PATH "/quit.png"),(COMMON_FILE_PATH "/quit_glow.png"), NULL, EDA_BUTTON_QUIT_PRESSED )

{
	
}

Eda_Menu_Main::~Eda_Menu_Main() {
}

void Eda_Menu_Main::draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board * game_board)
{
	al_draw_scaled_bitmap(theme->main_menu, 
							0.0, 0.0, al_get_bitmap_width(theme->main_menu), al_get_bitmap_height(theme->main_menu),
							0.0, 0.0, al_get_display_width(display), al_get_display_height(display), //x , y cord to draw and width and height to draw
							0); //flags
	play.draw(display);
	settings.draw(display);
	quit.draw(display);
	al_flip_display();
}

void Eda_Menu_Main::update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse)
{
	play.update_hovering(display, x_mouse, y_mouse);
	settings.update_hovering(display, x_mouse, y_mouse);
	quit.update_hovering(display,x_mouse, y_mouse);
}

bool Eda_Menu_Main::check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<hanabi_game_event_t> &button_event_queue)
{
	bool click = true;
	
	if(play.check_mouse_over(display,x_mouse,y_mouse))
		button_event_queue.push(play.get_click_event());
	else if(settings.check_mouse_over(display,x_mouse,y_mouse))
		button_event_queue.push(settings.get_click_event());
	else if(quit.check_mouse_over(display,x_mouse,y_mouse))
		button_event_queue.push(quit.get_click_event());
	else
		click = false;
	return click;
}