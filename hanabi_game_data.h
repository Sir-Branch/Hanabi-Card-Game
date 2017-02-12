/* 
 * File:   hanabi_game_data.h
 * Author: r2d2
 *
 * Created on February 12, 2017, 6:57 AM
 */

#ifndef HANABI_GAME_DATA_H
#define HANABI_GAME_DATA_H

#include "Hanabi_Skin.h"
#include "Hanabi_Board.h"
#include "Eda_Menu.h"

typedef struct
{
	unsigned int selected_resolution;
	unsigned int selected_theme;
	bool memory_help;
	bool sound_mute;
}game_configuration_t;

typedef struct
{
	game_configuration_t game_configuration;
	Hanabi_Board * game_board;
	Hanabi_Skin * theme_settings;
	ALLEGRO_DISPLAY * display;
	Eda_Menu * active_menu;
	bool do_exit, redraw;
	
}hanabi_game_data_t;

#endif /* HANABI_GAME_DATA_H */

