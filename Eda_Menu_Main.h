/* 
 * File:   Eda_Menu_Main.h
 * Author: r2d2
 *
 * Created on January 21, 2017, 11:32 PM
 */

#ifndef EDA_MENU_MAIN_H
#define EDA_MENU_MAIN_H

#include <queue>
#include "allegro5/allegro5.h"
#include "Eda_Button.h"
#include "Eda_Menu.h"
#include "Hanabi_Skin.h"

class Eda_Menu_Main : public Eda_Menu{
public:
	Eda_Menu_Main();
	virtual ~Eda_Menu_Main();
	
	void draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme);
	void update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse);
	bool check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<event_button_t> &button_event_queue);

private:
	Eda_Menu_Main(const Eda_Menu_Main& orig);
	Eda_Button play,settings;
};

#endif /* EDA_MENU_MAIN_H */

