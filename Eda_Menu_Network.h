/* 
 * File:   Eda_Menu_Network.h
 * Author: r2d2
 *
 * Created on March 9, 2017, 2:55 PM
 */

#ifndef EDA_MENU_NETWORK_H
#define EDA_MENU_NETWORK_H

#include "Eda_Button.h"
#include "Eda_Menu.h"

class Eda_Menu_Network : public Eda_Menu{
public:
	Eda_Menu_Network();
	Eda_Menu_Network(const Eda_Menu_Network& orig);
	virtual ~Eda_Menu_Network();
	
	void draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board * game_board);
	void update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse);
	bool check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<hanabi_game_event_t> &button_event_queue);
	
private:
	
	Eda_Button * connect;
	Eda_Button * cancel;

};

#endif /* EDA_MENU_NETWORK_H */

