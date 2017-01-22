/* 
 * File:   Eda_Menu_Game.cpp
 * Author: r2d2
 * 
 * Created on January 22, 2017, 3:53 AM
 */

#include "Eda_Menu_Game.h"
#include "Eda_Button.h"

Eda_Menu_Game::Eda_Menu_Game()
{
	color_buttons[0] = new Eda_Button(0.410, 0.615, 0.045, 0.08, CLUE_BUT_DIR "Button White.png", CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_WHITE_PRESSED);
	color_buttons[1] = new Eda_Button(0.455, 0.615, 0.045, 0.08, CLUE_BUT_DIR "Button Blue.png", CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_BLUE_PRESSED);
	color_buttons[2] = new Eda_Button(0.500, 0.615, 0.045, 0.08, CLUE_BUT_DIR "Button Green.png", CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_GREEN_PRESSED);
	color_buttons[3] = new Eda_Button(0.545, 0.615, 0.045, 0.08, CLUE_BUT_DIR "Button Yellow.png", CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_YELLOW_PRESSED);
	color_buttons[4] = new Eda_Button(0.590, 0.615, 0.045, 0.08, CLUE_BUT_DIR "Button Red.png",	CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_RED_PRESSED);

	number_buttons[0] = new Eda_Button(0.410, 0.70, 0.045, 0.08, CLUE_BUT_DIR "Number1.png", CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_ONE_PRESSED);
	number_buttons[1] = new Eda_Button(0.455, 0.70, 0.045, 0.08, CLUE_BUT_DIR "Number2.png", CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_TWO_PRESSED);
	number_buttons[2] = new Eda_Button(0.500, 0.70, 0.045, 0.08, CLUE_BUT_DIR "Number3.png", CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_THREE_PRESSED);
	number_buttons[3] = new Eda_Button(0.545, 0.70, 0.045, 0.08, CLUE_BUT_DIR "Number4.png", CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_FOUR_PRESSED);
	number_buttons[4] = new Eda_Button(0.590, 0.70, 0.045, 0.08, CLUE_BUT_DIR "Number5.png",	CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_FIVE_PRESSED);
}

Eda_Menu_Game::Eda_Menu_Game(const Eda_Menu_Game& orig) {
}

Eda_Menu_Game::~Eda_Menu_Game() {
	
	for(int i = 0 ; i < 5 ; i++)
	{
		delete color_buttons[i];
		delete number_buttons[i];
	}
}

void Eda_Menu_Game::draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme)
{
	al_draw_scaled_bitmap(theme->game_mat, 
							0.0, 0.0, al_get_bitmap_width(theme->main_menu), al_get_bitmap_height(theme->main_menu),
							0.0, 0.0, al_get_display_width(display), al_get_display_height(display), //x , y cord to draw and width and height to draw
							0); //flags	
	for(int i = 0 ; i < 5 ; i++)
	{
		color_buttons[i]->draw(display);
		number_buttons[i]->draw(display);
	}
	
	al_flip_display();
}


void Eda_Menu_Game::update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse)
{
	for(int i = 0 ; i < 5 ; i++)
	{
		color_buttons[i]->update_hovering(display, x_mouse, y_mouse);
		number_buttons[i]->update_hovering(display, x_mouse, y_mouse);
	}

}

bool Eda_Menu_Game::check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<event_button_t> &button_event_queue)
{
	bool click_color = false;
	bool click_number = false;
	unsigned int i;
	
	for(i = 0 ; i < 5 && !click_color &&  !click_number; i++)
	{
		if(color_buttons[i]->check_mouse_over_click(display, x_mouse, y_mouse))
			click_color = true;
		else if( number_buttons[i]->check_mouse_over_click(display, x_mouse, y_mouse))
			click_number = true;
	}
	
	--i; // I will woint to the click button in array
	//If click on a button will deselet rest of buttons
	if(click_color || click_number)
		for(int j = 0 ; j < 5 ; j++)
		{
			if( !click_color || i != j) //If click color will deselect all except clicked
				color_buttons[j]->deselect();
			if( !click_number || i != j) //If click number will deselect all except clicked
				number_buttons[j]->deselect();
		}
	

	return click_color || click_number;
	
	
}


