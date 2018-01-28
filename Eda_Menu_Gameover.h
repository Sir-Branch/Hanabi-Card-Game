#ifndef EDA_MENU_GAMEOVER_H
#define EDA_MENU_GAMEOVER_H


#include "Eda_Button.h"
#include "Eda_Menu.h"
#include <iostream>
#include <string.h>
#include <cstdlib>

class Eda_Menu_GameOver : public Eda_Menu{
public:
	Eda_Menu_GameOver();
	Eda_Menu_GameOver(const Eda_Menu_GameOver& orig);
	virtual ~Eda_Menu_GameOver();
	
	void draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board *game_board, bool mem_help);
	void update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse);
	bool check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<hanabi_game_event_t> &button_event_queue);

private:
	
	Eda_Button * play_again;
	Eda_Button * quit;

};

#endif /* EDA_MENU_GAMEOVER_H */
