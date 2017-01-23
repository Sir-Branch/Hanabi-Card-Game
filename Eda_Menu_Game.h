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

class Eda_Menu_Game : public Eda_Menu
{
public:
	Eda_Menu_Game();
	virtual ~Eda_Menu_Game();
	void draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board * game_board);
	void update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse);
	bool check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<event_button_t> &button_event_queue);
	
private:
	void draw_clue_tokens(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board * game_board,
					float x_center , float y_center ,float x_size_percent , float y_size_percent);
	void draw_lightning_tokens(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board * game_board,
					float x_center , float y_center ,float x_size_percent , float y_size_percent);
	void draw_cards(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme,
					float x_center , float y_center ,float x_size_percent , float y_size_percent, float space_between,
					int number_cards, const Hanabi_Card * cards_to_draw);
	
	Eda_Menu_Game(const Eda_Menu_Game& orig);
	Eda_Button * color_buttons[5];
	Eda_Button * number_buttons[5];
	Eda_Button * give_clue;
};

#endif /* EDA_MENU_GAME_H */

