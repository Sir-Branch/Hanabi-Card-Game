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
//#include "setting_management.h"

class Eda_Menu{
public:
	Eda_Menu();
	virtual ~Eda_Menu();
	virtual void draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board *game_board, bool mem_help) = 0;
	virtual void update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse) = 0;
	virtual bool check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<hanabi_game_event_t> &button_event_queue) = 0;
	virtual void manage_keyboard_stroge(unsigned int allegro_key);
	void draw_font(ALLEGRO_DISPLAY * display, const char * font_name, float x_center , float y_center, 
					float y_size_percent, const char * text, ALLEGRO_COLOR color);
private:
	Eda_Menu(const Eda_Menu& orig);
	

};

#endif /* EDA_MENU_H */

