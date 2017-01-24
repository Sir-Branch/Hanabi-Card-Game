/* 
 * File:   Eda_Menu_Game.cpp
 * Author: r2d2
 * 
 * Created on January 22, 2017, 3:53 AM
 */

#include "Eda_Menu_Game.h"
#include "Eda_Button.h"
#include "Hanabi_Board.h"

Eda_Menu_Game::Eda_Menu_Game()
{
	//give clue could be a Button and not a pointer and construct during call but I rather everything be the same in this menu
	give_clue = new Eda_Button(0.5, 0.737, 0.281, 0.08, CLUE_BUT_DIR "give_clue.png", CLUE_BUT_DIR "give_clue_hover.png", NULL, EDA_BUTTON_GIVE_CLUE_PRESSED);
	discard_card = new Eda_Button(0.85, 0.9, 0.045 * 3.75, 0.08, CLUE_BUT_DIR "discard_card.png", CLUE_BUT_DIR "discard_card_hover.png", NULL, EDA_BUTTON_DISCARD_CARD_PRESSED);
	play_card = new Eda_Button(0.15, 0.9, 0.045 * 3.75, 0.08, CLUE_BUT_DIR "play_card.png", CLUE_BUT_DIR "play_card_hover.png", NULL, EDA_BUTTON_PLAY_CARD_PRESSED);
		
	color_buttons[0] = new Eda_Button(0.410, 0.575, 0.045, 0.08, CLUE_BUT_DIR "Button White.png", CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_WHITE_PRESSED);
	color_buttons[1] = new Eda_Button(0.455, 0.575, 0.045, 0.08, CLUE_BUT_DIR "Button Blue.png", CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_BLUE_PRESSED);
	color_buttons[2] = new Eda_Button(0.500, 0.575, 0.045, 0.08, CLUE_BUT_DIR "Button Green.png", CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_GREEN_PRESSED);
	color_buttons[3] = new Eda_Button(0.545, 0.575, 0.045, 0.08, CLUE_BUT_DIR "Button Yellow.png", CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_YELLOW_PRESSED);
	color_buttons[4] = new Eda_Button(0.590, 0.575, 0.045, 0.08, CLUE_BUT_DIR "Button Red.png",	CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_RED_PRESSED);

	number_buttons[0] = new Eda_Button(0.410, 0.655, 0.045, 0.08, CLUE_BUT_DIR "Number1.png", CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_ONE_PRESSED);
	number_buttons[1] = new Eda_Button(0.455, 0.655, 0.045, 0.08, CLUE_BUT_DIR "Number2.png", CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_TWO_PRESSED);
	number_buttons[2] = new Eda_Button(0.500, 0.655, 0.045, 0.08, CLUE_BUT_DIR "Number3.png", CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_THREE_PRESSED);
	number_buttons[3] = new Eda_Button(0.545, 0.655, 0.045, 0.08, CLUE_BUT_DIR "Number4.png", CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_FOUR_PRESSED);
	number_buttons[4] = new Eda_Button(0.590, 0.655, 0.045, 0.08, CLUE_BUT_DIR "Number5.png",	CLUE_BUT_DIR "hover.png", CLUE_BUT_DIR "selection.png", EDA_BUTTON_FIVE_PRESSED);

}

Eda_Menu_Game::Eda_Menu_Game(const Eda_Menu_Game& orig) {
}

Eda_Menu_Game::~Eda_Menu_Game() 
{	
	for(int i = 0 ; i < 5 ; i++)
	{
		delete color_buttons[i];
		delete number_buttons[i];
	}
	delete give_clue; 
}

void Eda_Menu_Game::draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board * game_board)
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
	give_clue->draw(display);
	discard_card->draw(display);
	play_card->draw(display);
	
	draw_clue_tokens(display, theme, game_board, 
					0.1, 0.1,
					0.045, 0.08 );
	draw_lightning_tokens(display, theme, game_board, 
					0.2, 0.1,
					0.045, 0.08 );
	
	
	draw_cards(display,theme, //DRAW OTHER PLAYERS CARDS
					0.5, 0.1,
					0.063, 0.168, 0.005,
					6 , game_board->otherplayers_hand);
	
	draw_cards(display,theme, //DRAW CENTRAL_CARDS
					0.5, 0.4,
					0.063, 0.168, 0.02,
					5 , game_board->central_cards);
					//0.0495, 0.132);
					//0.045, 0.12);
	
	
	draw_cards(display,theme, //DRAW Other players hand repeated just for looks
					0.5, 0.9,
					0.063, 0.168, 0.005,
					6 , game_board->otherplayers_hand);
	
	al_flip_display();
}


void Eda_Menu_Game::update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse)
{
	for(int i = 0 ; i < 5 ; i++)
	{
		color_buttons[i]->update_hovering(display, x_mouse, y_mouse);
		number_buttons[i]->update_hovering(display, x_mouse, y_mouse);
	}
	give_clue->update_hovering(display, x_mouse, y_mouse);
	discard_card->update_hovering(display, x_mouse, y_mouse);
	play_card->update_hovering(display, x_mouse, y_mouse);


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
	
	--i; // i will point to the click button in array
	//If click occurs on a button will deselect rest of buttons
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

void Eda_Menu_Game::draw_lightning_tokens(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board * game_board,
					float x_center , float y_center ,float x_size_percent , float y_size_percent)
{
	unsigned int used_tokens = HANABI_LIGHT_TOKENS - game_board->number_lives_left();
	
	for(unsigned int i = 1 ; i <= HANABI_LIGHT_TOKENS ; i++)
	{
		if( i <= used_tokens)
			al_draw_scaled_bitmap(theme->token_lightning[0], //token_lightning[0] corresponds to disabled
							0.0, 0.0, al_get_bitmap_width(theme->token_lightning[0]), al_get_bitmap_height(theme->token_lightning[0]),
							(x_center-0.5 * x_size_percent) * al_get_display_width(display), //x_cord to draw
							(y_center-0.5 * y_size_percent + y_size_percent * (i-1)) * al_get_display_height(display),  //y_cord to draw
							x_size_percent * al_get_display_width(display), y_size_percent * al_get_display_height(display), //width and height to draw
							0); //flags
		else
			al_draw_scaled_bitmap(theme->token_lightning[1], 	//token_lightning[1] corresponds to enabled
								0.0, 0.0, al_get_bitmap_width(theme->token_lightning[1]), al_get_bitmap_height(theme->token_lightning[1]),
								(x_center-0.5 * x_size_percent) * al_get_display_width(display), //x_cord to draw
								(y_center-0.5 * y_size_percent + y_size_percent * (i-1)) * al_get_display_height(display),  //y_cord to draw
								x_size_percent * al_get_display_width(display), y_size_percent * al_get_display_height(display), //width and height to draw
								0); //flags
	}
	
}

void Eda_Menu_Game::draw_clue_tokens(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board * game_board,
						float x_center , float y_center ,float x_size_percent , float y_size_percent)
{
	unsigned int used_tokens = HANABI_CLUE_TOKENS - game_board->number_clues_left();
	
	for(unsigned int i = 1 ; i <= HANABI_CLUE_TOKENS ; i++)
	{
		if( i <= used_tokens)
			al_draw_scaled_bitmap(theme->token_clue[0], //token_lightning[0] corresponds to disabled
							0.0, 0.0, al_get_bitmap_width(theme->token_clue[0]), al_get_bitmap_height(theme->token_clue[0]),
							(x_center-0.5 * x_size_percent) * al_get_display_width(display), //x_cord to draw
							(y_center-0.5 * y_size_percent + y_size_percent * (i-1)) * al_get_display_height(display),  //y_cord to draw
							x_size_percent * al_get_display_width(display), y_size_percent * al_get_display_height(display), //width and height to draw
							0); //flags
		else
			al_draw_scaled_bitmap(theme->token_clue[1], 	//token_lightning[1] corresponds to enabled
								0.0, 0.0, al_get_bitmap_width(theme->token_lightning[1]), al_get_bitmap_height(theme->token_clue[1]),
								(x_center-0.5 * x_size_percent) * al_get_display_width(display), //x_cord to draw
								(y_center-0.5 * y_size_percent + y_size_percent * (i-1)) * al_get_display_height(display),  //y_cord to draw
								x_size_percent * al_get_display_width(display), y_size_percent * al_get_display_height(display), //width and height to draw
								0); //flags
	}
	
	
}

void Eda_Menu_Game::draw_cards(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme,
					float x_center , float y_center ,float x_size_percent , float y_size_percent, float space_between,
					int number_cards, const Hanabi_Card * cards_to_draw)
{
	Hanabi_Card empty_card;	
	for(int i = 0 ; i < number_cards ; i++)
	{
		Hanabi_Card temp_copy = cards_to_draw[i];
		if( empty_card == cards_to_draw[i] )
			al_draw_scaled_bitmap(theme->cards_backside, 
									0.0, 0.0, al_get_bitmap_width(theme->cards_backside), al_get_bitmap_height(theme->cards_backside),
									(x_center + (space_between+x_size_percent) * (i-number_cards/2.0)) * al_get_display_width(display), //x_cord to draw
									(y_center - 0.5 * y_size_percent) * al_get_display_height(display),  //y_cord to draw
									x_size_percent * al_get_display_width(display), y_size_percent * al_get_display_height(display), //width and height to draw
									0); //flags
		else
		{
			int suit_num = temp_copy.get_suit_number();
			al_draw_scaled_bitmap(theme->deck[suit_num][temp_copy.get_value()-1],
									0.0, 0.0, al_get_bitmap_width(theme->deck[suit_num][temp_copy.get_value()-1]), al_get_bitmap_height(theme->deck[suit_num][temp_copy.get_value()-1]),
									(x_center + (space_between+x_size_percent) * (i-number_cards/2.0)) * al_get_display_width(display), //x_cord to draw
									(y_center - 0.5 * y_size_percent) * al_get_display_height(display),  //y_cord to draw
									x_size_percent * al_get_display_width(display), y_size_percent * al_get_display_height(display), //width and height to draw
									0); //flags
		}
#warning "FIX DRAWING IS SLIGHTLY OFF WHEN IMPAIR NUMBER DUE TO SPACING I THINK"
		
	}							
	
	
}