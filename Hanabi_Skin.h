/* 
 * File:   Hanabi_Skin.h
 * Author: r2d2
 *
 * Created on January 20, 2017, 11:53 PM
 */

#ifndef HANABI_SKIN_H
#define HANABI_SKIN_H

#include "allegro5/allegro5.h"
#include <string>

class Hanabi_Skin {
public:
	Hanabi_Skin();
	virtual ~Hanabi_Skin();
	bool load_theme(std::string theme_name);
	
public:
	ALLEGRO_BITMAP * main_menu;
	ALLEGRO_BITMAP * connecting_background;
	ALLEGRO_BITMAP * game_mat;
	
	ALLEGRO_BITMAP * cards_blue[5];
	ALLEGRO_BITMAP * cards_green[5];
	ALLEGRO_BITMAP * cards_red[5];
	ALLEGRO_BITMAP * cards_white[5];
	ALLEGRO_BITMAP * cards_yellow[5];
	ALLEGRO_BITMAP * cards_backside;
	
	//0 Will correspond to disable 1 to enabled for tokens
	ALLEGRO_BITMAP * token_clue[2]; 
	ALLEGRO_BITMAP * token_lightning[2];
	
	//ALLEGRO_BITMAP * clue_numbers[5];
	//ALLEGRO_BITMAP * clue_colors[5];
	//ALLEGRO_BITMAP * clue_hover;

private:
	Hanabi_Skin(const Hanabi_Skin& orig);
};

#endif /* HANABI_SKIN_H */

