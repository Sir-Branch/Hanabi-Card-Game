
#include "Eda_Menu_Gameover.h"
#include "Eda_Button.h"
#include "Eda_Textbox.h"
#include "setting_management.h"
#include "Eda_Menu_Game.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <iostream>
#include <string>
#include <cstdlib>


/*
 * Constructor. Defines two buttons: one for play again and another for quit. 
 * 
 * Input:
 *	-ALLEGRO_DISPLAY * display: The display
 *	-char *path: path to the pngs, necesary for loading images. It is not used. 
 * 
 * Return:
 *	-no return in constructor
 */
Eda_Menu_GameOver::Eda_Menu_GameOver() {
	
	Eda_Button* play_again =  new Eda_Button( 0.4, 0.75, 0.045 * 3.75, 0.08, COMMON_FILE_PATH "/join.png", COMMON_FILE_PATH "/join_hover.png", NULL, EDA_BUTTON_JOIN_PRESSED);
	Eda_Button* quit = new Eda_Button(0.6, 0.75, 0.045 * 3.75, 0.08, COMMON_FILE_PATH "/host.png", COMMON_FILE_PATH "/host_hover.png", NULL, EDA_BUTTON_HOST_PRESSED );
}

Eda_Menu_GameOver::Eda_Menu_GameOver(const Eda_Menu_GameOver& orig) {
}

/*
 * Destructor. Destruction of the two buttons
 * 
 * Input:
 *	-no input 
 * 
 * Return:
 *	-no return
 */

Eda_Menu_GameOver::~Eda_Menu_GameOver() {
	
	delete play_again;
	delete quit;
}

void Eda_Menu_GameOver::draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board * game_board)
{
	ALLEGRO_FONT * font;
	//Draw the background
	//al_draw_scaled_bitmap(theme->connecting_background, 
	//						0.0, 0.0, al_get_bitmap_width(theme->connecting_background), al_get_bitmap_height(theme->connecting_background),
	//						0.0, 0.0, al_get_display_width(display), al_get_display_height(display), //x , y cord to draw and width and height to draw
	//						0); //flags	
	
#warning "o ponemos otro background ?"
	al_draw_filled_rounded_rectangle( 0.1 * al_get_display_width(display) , 
							  0.1 * al_get_display_height(display),
							  0.9	* al_get_display_width(display), 
							  0.9 * al_get_display_height(display),
							  15, 15, al_map_rgba(0,0,0,200)
							);

	play_again->draw(display); //Draws the play again button
	quit->draw(display);// Draws the quit button 
		
	font = al_load_ttf_font(MONO_FONT_PATH,calculate_font_size(display, 0.3, 0.3, MONO_FONT_PATH, 9),0); //Loads font for "game over"	
	al_draw_text(font, al_color_name("white"),0.5 * al_get_display_width(display),
				(0.5 - 0.2) * al_get_display_height(display) - al_get_font_line_height(font)*0.5,
				 ALLEGRO_ALIGN_CENTRE, "Game Over" );
	
	al_destroy_font(font);
	
	font = al_load_ttf_font(MONO_FONT_PATH,calculate_font_size(display, 0.8-0.7, 0.8-0.7, MONO_FONT_PATH, 8),0); //Loads font for "game over"
	al_draw_text(font, al_color_name("white"),0.5 * al_get_display_width(display),
				(0.5) * al_get_display_height(display) - al_get_font_line_height(font)*0.5,
				 ALLEGRO_ALIGN_CENTRE, "Score: 25" );
	
	//std::string score_message = "Score: " + std::to_string(game_board->score); //Esto va arriba 
#warning "no se porque no encuentra std"
	
	al_destroy_font(font);	
	al_flip_display();
	
	
}

	
	
	
	

void Eda_Menu_GameOver::update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse)
{
	play_again->update_hovering(display,x_mouse,y_mouse);
	quit->update_hovering(display,x_mouse,y_mouse);
}

bool Eda_Menu_GameOver::check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<hanabi_game_event_t> &button_event_queue)
{		
	bool click_button = false;

	if( play_again->check_mouse_over_toggle(display, x_mouse, y_mouse) )
	{
		click_button = true;
		button_event_queue.push( play_again->get_click_event() );
	}
	else if( quit->check_mouse_over_toggle(display, x_mouse, y_mouse) )
	{
		click_button = true;
		button_event_queue.push( quit->get_click_event() );
	}

	return click_button;
}

