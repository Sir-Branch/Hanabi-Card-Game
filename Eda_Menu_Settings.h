/* 
 * File:   Eda_Menu_Settings.h
 * Author: r2d2
 *
 * Created on January 23, 2017, 6:58 PM
 */

#ifndef EDA_MENU_SETTINGS_H
#define EDA_MENU_SETTINGS_H


#define HANABI_NUMBER_RESOLUTIONS	6	//1024×576, 1152×648, 1280×720, 1366×768, 1600×900, 1920×1080
#define HANABI_NUMBER_THEMES		2

#include "Eda_Menu.h"
#include "Hanabi_Skin.h"

typedef struct
{
	Hanabi_Skin * theme_settings;
	unsigned int selected_resolution;
	unsigned int selected_theme;
	bool memory_help;
	
}game_configuration_t;

class Eda_Menu_Settings : public Eda_Menu
{
public:
	Eda_Menu_Settings(game_configuration_t game_configuration);
	virtual ~Eda_Menu_Settings();

	void draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board * game_board);
	void update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse);
	bool check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<event_button_t> &button_event_queue);
	
	void update_game_settings(ALLEGRO_DISPLAY * display, game_configuration_t & game_config);
private:
	Eda_Menu_Settings(const Eda_Menu_Settings& orig);
	
	Eda_Button * resolution_arrows[2];
	Eda_Button * theme_arrows[2];
	Eda_Button * memory_help; 
	Eda_Button * apply;
	Eda_Button * cancel;
	
	const char ** available_resolutions;//[HANABI_NUMBER_RESOLUTIONS];
	const char ** available_themes;//[HANABI_NUMBER_THEMES];
	
	unsigned int selected_resolution; //0 to number of resolutions
	unsigned int selected_theme; //0 to number of themes
	bool enable_mem_help;
};



#endif /* EDA_MENU_SETTINGS_H */
