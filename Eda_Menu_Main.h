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
	Eda_Menu_Main(std::string theme);
	virtual ~Eda_Menu_Main();
	
	void draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board *game_board, bool mem_help);
	void update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse);
	bool check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<hanabi_game_event_t> &button_event_queue);

private:

	#warning "Eda menu has Eda_button rest Eda_button * make them match"
	Eda_Menu_Main(const Eda_Menu_Main& orig);
	Eda_Button play,settings,quit;
};

#endif /* EDA_MENU_MAIN_H */

