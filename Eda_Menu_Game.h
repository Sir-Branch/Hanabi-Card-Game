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

#define CLUE_BUT_DIR "Clue Buttons/" //Clue button Directory path

class Eda_Menu_Game : public Eda_Menu
{
public:
	Eda_Menu_Game();
	virtual ~Eda_Menu_Game();
	void draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme);
	void update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse);
	bool check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<event_button_t> &button_event_queue);
	
public:
	Eda_Menu_Game(const Eda_Menu_Game& orig);
	Eda_Button *color_buttons[5];
	Eda_Button *number_buttons[5];
};

#endif /* EDA_MENU_GAME_H */

