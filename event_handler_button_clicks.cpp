/* 
 * File:   event_handler_button_clicks.cpp
 * Author: r2d2
 *
 * Created on February 12, 2017, 6:06 AM
 */

#include "hanabi_events.h"
#include "hanabi_game_data.h"
#include "Eda_Menu_Main.h"
#include "Eda_Menu_Game.h"
#include "Eda_Menu_Settings.h"

#include "event_handler_button_clicks.h"

void event_handle_button(event_button_t button_event,hanabi_game_data_t * hanabi_game_data)
{
	//manage_button_event;
	if( button_event == EDA_BUTTON_PLAY_PRESSED )
	{
		delete hanabi_game_data->active_menu;
		hanabi_game_data->active_menu = new Eda_Menu_Game(hanabi_game_data->theme_settings->theme);
	}
	else if(button_event == EDA_BUTTON_SETT_PRESSED)
	{
		delete hanabi_game_data->active_menu;
		hanabi_game_data->active_menu = new Eda_Menu_Settings(hanabi_game_data->game_configuration);
	}
	else if(button_event == EDA_BUTTON_CANCEL_PRESSED)
	{
		delete hanabi_game_data->active_menu;
		hanabi_game_data->active_menu = new Eda_Menu_Main(hanabi_game_data->theme_settings->theme);
	}
	else if(button_event == EDA_BUTTON_APPLY_PRESSED)
	{
#warning "Change reference for pointer in Eda_Menu_Settings update game setting method(class function)"
		((Eda_Menu_Settings *)hanabi_game_data->active_menu)->update_game_settings(*hanabi_game_data);
		delete hanabi_game_data->active_menu;
		hanabi_game_data->active_menu = new Eda_Menu_Main(hanabi_game_data->theme_settings->theme);
	}
}