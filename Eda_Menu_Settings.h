/* 
 * File:   Eda_Menu_Settings.h
 * Author: r2d2
 *
 * Created on January 23, 2017, 6:58 PM
 */

#ifndef EDA_MENU_SETTINGS_H
#define EDA_MENU_SETTINGS_H

#include "Eda_Menu.h"
#include "Hanabi_Skin.h"
#include "setting_management.h"



class Eda_Menu_Settings : public Eda_Menu
{
public:
	Eda_Menu_Settings(game_configuration_t game_configuration);
	virtual ~Eda_Menu_Settings();

	void draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board * game_board);
	void update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse);
	bool check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<hanabi_game_event_t> &button_event_queue);
	
	void update_game_settings(hanabi_game_data_t & game_config);
private:
	Eda_Menu_Settings(const Eda_Menu_Settings& orig);
	
	Eda_Button * resolution_arrows[2];
	Eda_Button * theme_arrows[2];
	Eda_Button * memory_help;
	Eda_Button * full_screen; 
	Eda_Button * apply;
	Eda_Button * cancel;
	Eda_Button * music;
			
	
	const char ** available_resolutions;//[HANABI_NUMBER_RESOLUTIONS];
	const char ** available_themes;//[HANABI_NUMBER_THEMES];
	
	unsigned int selected_resolution; //0 to number of resolutions
	unsigned int selected_theme; //0 to number of themes
	bool enable_full_screen;
	bool enable_mem_help;
	bool enable_music;
};



#endif /* EDA_MENU_SETTINGS_H */

