/* 
 * File:   setting_management.h
 * Author: r2d2
 *
 * Created on January 8, 2018, 8:38 PM
 */

#ifndef SETTING_MANAGEMENT_H
#define SETTING_MANAGEMENT_H

#define HANABI_NUMBER_RESOLUTIONS	6	//1024×576, 1152×648, 1280×720, 1366×768, 1600×900, 1920×1080
#define HANABI_NUMBER_THEMES		2
#define MONO_FONT_PATH "Fonts/DroidSansMono.ttf"
#define COMMON_FILE_PATH "Common Images Files"
#define FONT_PATH "Fonts"

#include "Hanabi_Skin.h"
#include "Hanabi_Board.h"
#include "Eda_Menu.h"
#include "TFTPCxn.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string>

typedef struct
{
	unsigned int selected_resolution;
	unsigned int selected_theme;
	bool memory_help;
	bool sound_mute;
	bool full_screen;
}game_configuration_t;

typedef struct
{
	game_configuration_t game_configuration;
	Hanabi_Board * game_board;
	Hanabi_Skin * theme_settings;
	ALLEGRO_DISPLAY * display;
	Eda_Menu * active_menu;
	bool do_exit, redraw;
	TFTPCxn * net_connection;
    TFTP_Packet * last_received_pck;
	ALLEGRO_SAMPLE *main_music;
	std::string player_name;	
}hanabi_game_data_t;

void load_configuration(hanabi_game_data_t * hanabi_game_data);
void save_configuration(hanabi_game_data_t * hanabi_game_data);
void get_static_themes_resolutions(const char *** available_themes ,  const char *** available_resolutions);
const char * get_resolution(unsigned int num_resol);
const char * get_theme(unsigned int num_theme);
unsigned int calculate_font_size (ALLEGRO_DISPLAY *display, float x_size_percent , float y_size_percent,char * path, unsigned int max_size);

#endif /* SETTING_MANAGEMENT_H */

