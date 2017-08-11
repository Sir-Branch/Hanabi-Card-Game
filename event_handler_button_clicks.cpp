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
#include "Hanabi_Play_Packet.h"

void event_handle_button(event_button_t button_event,hanabi_game_data_t * hanabi_game_data)
{
	//*************************MAIN MENU***************************
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
	//*************************SETTINGS MENU***************************
	else if(button_event == EDA_BUTTON_CANCEL_PRESSED)
	{
		delete hanabi_game_data->active_menu;
		hanabi_game_data->active_menu = new Eda_Menu_Main(hanabi_game_data->theme_settings->theme);
	}
	else if(button_event == EDA_BUTTON_APPLY_PRESSED)
	{
#warning "Change reference for pointer in Eda_Menu_Settings update game setting method(class function) and change to recieve three things"
		((Eda_Menu_Settings *)hanabi_game_data->active_menu)->update_game_settings(*hanabi_game_data);
		delete hanabi_game_data->active_menu;
		hanabi_game_data->active_menu = new Eda_Menu_Main(hanabi_game_data->theme_settings->theme);
	}
	//*************************GAME MENU***************************
	
	else if(button_event >= EDA_BUTTON_ONE_PRESSED && button_event <= EDA_BUTTON_FIVE_PRESSED);//manage clue button;
	else if(button_event >= EDA_BUTTON_WHITE_PRESSED && button_event <= EDA_BUTTON_RED_PRESSED);//
	else if(button_event >= EDA_BUTTON_GIVE_CARD_ONE && button_event <= EDA_BUTTON_GIVE_CARD_SIX);

	else if(button_event == EDA_BUTTON_GIVE_CLUE_PRESSED)
	{
		unsigned int selected_clue = ((Eda_Menu_Game *)hanabi_game_data->active_menu)->get_selected_clue();
		if( selected_clue && hanabi_game_data->game_board->any_clues_left() )
		{
			if( hanabi_game_data->net_connection == NULL || !hanabi_game_data->net_connection->connection_status_ok() )
			{
				//GENERATE NETWORK ERROR EVENT;
			}
			else
			{
				hanabi_game_data->game_board->player_action_give_clue(selected_clue,hanabi_game_data->net_connection);
			}
		}
		else
		{
			;//unable to give_clue no clue tokens left discard a Card for a Clue Token
		}
		
	}
	else if(button_event == EDA_BUTTON_PLAY_CARD_PRESSED)
	{
		unsigned int selected_card = ((Eda_Menu_Game *)hanabi_game_data->active_menu)->get_selected_card();
		TFTP_Packet * to_send = new Hanabi_Play_Packet(selected_card);
		if( selected_card ) 
		{
			hanabi_game_data->game_board->player_action_play_card(selected_card-1);
			if( hanabi_game_data->net_connection == NULL || !hanabi_game_data->net_connection->connection_status_ok() )
			{
				//GENERATE NETWORK ERROR EVENT;
			}
			else
			{
				hanabi_game_data->net_connection->send_packet(to_send);
			}
			
		}
	
		
	
		
			
	}
	else if(button_event == EDA_BUTTON_DISCARD_CARD_PRESSED)
	{
		unsigned int selected_card = ((Eda_Menu_Game *)hanabi_game_data->active_menu)->get_selected_card();
		if( selected_card && !hanabi_game_data->game_board->all_clues_left() )
		{
			hanabi_game_data->game_board->player_action_discard_card(selected_card-1);
		}
		else
		{
			;//all clues left cannot discard card
		}
	}
}