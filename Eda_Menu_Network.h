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
#include "Eda_Textbox.h"

class Eda_Menu_Network : public Eda_Menu{
public:
	Eda_Menu_Network(ALLEGRO_DISPLAY * display = NULL, char * path = NULL);
	Eda_Menu_Network(const Eda_Menu_Network& orig);
	virtual ~Eda_Menu_Network();
	
	void draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board * game_board);
	void update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse);
	bool check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<hanabi_game_event_t> &button_event_queue);
	void manage_keyboard_stroge(unsigned int allegro_key);
	const char* read_ip_input(void);
	const char* read_name_input(void);

private:
	
	Eda_Button * connect;
	Eda_Button * cancel;
	Eda_Textbox * ip_input;
	Eda_Textbox * name_input;

};

#endif /* EDA_MENU_NETWORK_H */

