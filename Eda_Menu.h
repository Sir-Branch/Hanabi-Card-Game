/* 
 * File:   Eda_Menu.h
 * Author: r2d2
 *
 * Created on January 14, 2017, 10:27 PM
 */

#ifndef EDA_MENU_H
#define EDA_MENU_H

#include <queue>
#include "allegro5/allegro5.h"
#include "Eda_Button.h"
#include "Hanabi_Skin.h"
#include "Hanabi_Board.h"

class Eda_Menu{
public:
	Eda_Menu();
	virtual ~Eda_Menu();
	virtual void draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board * game_board) = 0;
	virtual void update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse) = 0;
	virtual bool check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<event_button_t> &button_event_queue) = 0;
	
private:
	Eda_Menu(const Eda_Menu& orig);
	

};

#endif /* EDA_MENU_H */

