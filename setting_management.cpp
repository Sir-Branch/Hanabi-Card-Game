/* 
 * File:   setting_management.cpp
 * Author: r2d2
 *
 * Created on January 8, 2018, 7:22 PM
 */

#include "setting_management.h"
#include <iostream>
#include <sstream>
#include <string>



static const char * themes[HANABI_NUMBER_THEMES] = {"Classic" , "Pokemon" };
static const char * resolutions[HANABI_NUMBER_RESOLUTIONS] = {"1024x576", "1152x648", "1280x720", "1366x768", "1600x900", "1920x1080" };

static void load_default_configuration(hanabi_game_data_t * hanabi_game_data);


void get_static_themes_resolutions(const char *** available_themes ,  const char *** available_resolutions)
{
	if(available_resolutions != NULL)
		*available_resolutions = resolutions;
	if(available_themes != NULL)
		*available_themes = themes;
}

const char * get_resolution(unsigned int num_resol)
{
	const char ** available_resolutions;
	get_static_themes_resolutions(NULL, &available_resolutions);
	return available_resolutions[num_resol];
}

const char * get_theme(unsigned int num_theme)
{
	const char ** available_themes;
	get_static_themes_resolutions(&available_themes, NULL);
	return available_themes[num_theme];
}



template <typename T>
std::string num2string ( T Number )
{
	std::stringstream ss;
	ss << Number;
	return ss.str();
}

void load_configuration(hanabi_game_data_t * hanabi_game_data)
{
	ALLEGRO_CONFIG * config_file = al_load_config_file("settings.ini");
	if(config_file != NULL)
	{
		hanabi_game_data->game_configuration.memory_help = 
			atoi(al_get_config_value(config_file, "Game Settings","Memory Help"));	

		hanabi_game_data->game_configuration.full_screen =
			atoi(al_get_config_value(config_file, "Screen Settings","Full Screen"));

		hanabi_game_data->game_configuration.selected_resolution =
			atoi(al_get_config_value(config_file, "Screen Settings","Selected Resolution"));
			
		hanabi_game_data->game_configuration.sound_mute = 
			atoi(al_get_config_value(config_file, "Sound Settings","Sound Muted"));

		hanabi_game_data->game_configuration.selected_theme = 
			atoi(al_get_config_value(config_file, "Theme Settings","Selected Theme"));
	}
	else
		load_default_configuration(hanabi_game_data);// Incase of error reading anyvalue will return to default
	
}

void load_default_configuration(hanabi_game_data_t * hanabi_game_data)
{
	
	hanabi_game_data->game_configuration.memory_help = false;
	hanabi_game_data->game_configuration.full_screen = false;
	hanabi_game_data->game_configuration.sound_mute = false;
	hanabi_game_data->game_configuration.selected_resolution = 1;
	hanabi_game_data->game_configuration.selected_theme = 0;
	//hanabi_game_data->theme_settings = new Hanabi_Skin();
	//hanabi_game_data->theme_settings->load_theme("Classic");
	
}

void save_configuration(hanabi_game_data_t * hanabi_game_data)
{
	ALLEGRO_CONFIG * config_file = al_create_config();
	if(config_file != NULL)
	{
		al_set_config_value(config_file, "Game Settings", "Memory Help",
			num2string(hanabi_game_data->game_configuration.memory_help).c_str());
		
		al_set_config_value(config_file, "Screen Settings", "Selected Resolution",
			num2string(hanabi_game_data->game_configuration.selected_resolution).c_str());
		
		al_set_config_value(config_file, "Screen Settings", "Full Screen",
			num2string(hanabi_game_data->game_configuration.full_screen).c_str());
		
		al_set_config_value(config_file, "Sound Settings", "Sound Muted",
			num2string(hanabi_game_data->game_configuration.sound_mute).c_str());
		
		al_set_config_value(config_file, "Theme Settings", "Selected Theme",
			num2string(hanabi_game_data->game_configuration.selected_theme).c_str());
		
		al_save_config_file("settings.ini",config_file);
	}
}
