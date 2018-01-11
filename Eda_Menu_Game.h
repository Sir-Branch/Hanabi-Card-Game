/* 
 * File:   Eda_Menu_Game.h
 * Author: r2d2
 *
 * Created on January 22, 2017, 3:53 AM
 */

#ifndef EDA_MENU_GAME_H
#define EDA_MENU_GAME_H

#include <queue>
#include "allegro5/allegro5.h"
#include "Eda_Button.h"
#include "Eda_Menu.h"
#include "Hanabi_Skin.h"
#include "Hanabi_Board.h"

#define CLUE_BUT_DIR "Clue Buttons/" //Clue button Directory path
#define NAME_SIZE 10

class Eda_Menu_Game : public Eda_Menu
{
public:
	Eda_Menu_Game(std::string theme = "");
	virtual ~Eda_Menu_Game();
	void draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board * game_board);
	void update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse);
	bool check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<hanabi_game_event_t> &button_event_queue);
	
	unsigned int get_selected_clue(void);
	unsigned int get_selected_card(void);
	
private:
	Eda_Menu_Game(const Eda_Menu_Game& orig);
	
	void draw_clue_tokens(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board * game_board,
					float x_center , float y_center ,float x_size_percent , float y_size_percent);
	void draw_lightning_tokens(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board * game_board,
					float x_center , float y_center ,float x_size_percent , float y_size_percent);
	void draw_cards(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme,
					float x_center , float y_center ,float x_size_percent , float y_size_percent, float space_between,
					int number_cards, const Hanabi_Card * cards_to_draw);
	void draw_deck(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board *gameboard, float x_center , float y_center ,float x_size_percent , float y_size_percent);

	void draw_graveyard(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme,float x_center , float y_center ,float x_size_percent , float y_size_percent, Hanabi_Board * board);
	void draw_player_box_name (ALLEGRO_DISPLAY *display,const char* player_name,float x_center , float y_center ,float x_size_percent , float y_size_percent, char * path);

	bool hidden_graveyard;
	Eda_Button * graveyard_toggle;
	Eda_Button * color_buttons[5];
	Eda_Button * number_buttons[5];
	Eda_Button * give_clue;
	Eda_Button * discard_card;
	Eda_Button * play_card;
	
	Eda_Button * my_cards_buttons[6];
};

#endif /* EDA_MENU_GAME_H */

