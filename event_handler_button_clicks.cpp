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
#include "Eda_Menu_Network.h"
#include <iostream>
#include "event_handler_button_clicks.h"
#include "Hanabi_Play_Packet.h"
#include "TFTPClient.h"
#include "TFTPServer.h"

#include <allegro5/allegro_native_dialog.h>

void event_handle_button(event_button_t button_event,hanabi_game_data_t * hanabi_game_data, std::queue<hanabi_fsm_events_t> *software_event_queue)
{
	//*************************MAIN MENU***************************
	if( button_event == EDA_BUTTON_PLAY_PRESSED )
	{
		software_event_queue->push(PLAY_CLICKED);
		delete hanabi_game_data->active_menu;
		hanabi_game_data->active_menu =new Eda_Menu_Network(hanabi_game_data->display, MONO_FONT_PATH);
	}
	else if(button_event == EDA_BUTTON_SETT_PRESSED)
	{
		software_event_queue->push(SETTINGS_CLICK);
		delete hanabi_game_data->active_menu;
		hanabi_game_data->active_menu = new Eda_Menu_Settings(hanabi_game_data->game_configuration);
	}
	else if(button_event == EDA_BUTTON_QUIT_PRESSED)
	{
		//software_event_queue->push(SETTINGS_CLICK);
		hanabi_game_data->do_exit = true;
	}
	//*************************SETTINGS MENU***************************
	else if(button_event == EDA_BUTTON_CANCEL_PRESSED)
	{
		software_event_queue->push(CANCEL_CLICKED);
		delete hanabi_game_data->active_menu;
		hanabi_game_data->active_menu = new Eda_Menu_Main(hanabi_game_data->theme_settings->theme);
	}
	else if(button_event == EDA_BUTTON_APPLY_PRESSED)
	{
		software_event_queue->push(APPLY_CLICKED);
		#warning "Change reference for pointer in Eda_Menu_Settings update game setting method(class function) and change to recieve three things"
		((Eda_Menu_Settings *)hanabi_game_data->active_menu)->update_game_settings(*hanabi_game_data);
		delete hanabi_game_data->active_menu;
		hanabi_game_data->active_menu = new Eda_Menu_Main(hanabi_game_data->theme_settings->theme);
	}
	//**********************NETWORK MENU***************************
	else if(button_event == EDA_BUTTON_JOIN_PRESSED)
	{
//		hanabi_game_data->player_name = 
		std::cout << "CLient\n";
		software_event_queue->push(JOIN_CLICKED);
		
		hanabi_game_data->join_ip = ((Eda_Menu_Network*)hanabi_game_data->active_menu)->read_ip_input();
		hanabi_game_data->player_name = ((Eda_Menu_Network*)hanabi_game_data->active_menu)->read_name_input();
		hanabi_game_data->net_connection = new Networking();
		#warning "Hardcoded to loopback because net connection is not working"
		if( hanabi_game_data->net_connection->try_connect_server(DEF_TIMEOUT_SECS, ((Eda_Menu_Network*)hanabi_game_data->active_menu)->read_ip_input()))
		{
			software_event_queue->push(FOUND_SERVER);
			delete hanabi_game_data->active_menu;
			hanabi_game_data->active_menu = new Eda_Menu_Game(hanabi_game_data->theme_settings->theme);
			hanabi_game_data->connected = true;
			std::cout<< "Client has found and connected to server\n"; 
		}
		else
		{
			al_show_native_message_box( hanabi_game_data->display,
			"Warning", "Connection Problem", "Unable to find server at specified Ip Address",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
			software_event_queue->push(SERVER_NOT_FOUND);
		}
		
	}
	else if(button_event == EDA_BUTTON_HOST_PRESSED)
	{
		std::cout << "Host\n";
		software_event_queue->push(HOST_CLICKED);
		hanabi_game_data->player_name = ((Eda_Menu_Network*)hanabi_game_data->active_menu)->read_name_input();
		hanabi_game_data->net_connection = new Networking();
		if( hanabi_game_data->net_connection->listen_for_client(100.0) )
		{
			software_event_queue->push(CLIENT_CONNECTED);
			delete hanabi_game_data->active_menu;
			hanabi_game_data->active_menu = new Eda_Menu_Game(hanabi_game_data->theme_settings->theme);
			hanabi_game_data->connected = true;
			std::cout<< "Server has listened for client connection established\n"; 
		}
		else
		{
			std::cout<< "Server has listened for client unable to establish connec.\n"; 
			software_event_queue->push(CLIENT_NOT_CONNECTED);
		}
	}
	//*************************GAME MENU***************************
	
	else if(button_event >= EDA_BUTTON_ONE_PRESSED && button_event <= EDA_BUTTON_FIVE_PRESSED);//manage clue button;
	else if(button_event >= EDA_BUTTON_WHITE_PRESSED && button_event <= EDA_BUTTON_RED_PRESSED);//
	else if(button_event >= EDA_BUTTON_GIVE_CARD_ONE && button_event <= EDA_BUTTON_GIVE_CARD_SIX);

	else if( !hanabi_game_data->other_players_turn && button_event == EDA_BUTTON_GIVE_CLUE_PRESSED)
	{
		unsigned int selected_clue = ((Eda_Menu_Game *)hanabi_game_data->active_menu)->get_selected_clue();
		if( hanabi_game_data->game_board->any_clues_left() && 
			hanabi_game_data->game_board->validate_give_clue(selected_clue) )
			software_event_queue->push(ACTION_YOU_HAVE);
		//else unable to give_clue no clue tokens left discard a Card for a Clue Token
		
	}
	else if( !hanabi_game_data->other_players_turn && button_event == EDA_BUTTON_PLAY_CARD_PRESSED)
	{
		unsigned int selected_card = ((Eda_Menu_Game *)hanabi_game_data->active_menu)->get_selected_card();
		if( selected_card != NO_CARD_SELECTED )
			software_event_queue->push(ACTION_PLAY);
			
	}
	else if(!hanabi_game_data->other_players_turn && button_event == EDA_BUTTON_DISCARD_CARD_PRESSED)
	{
		unsigned int selected_card = ((Eda_Menu_Game *)hanabi_game_data->active_menu)->get_selected_card();
		if( selected_card != NO_CARD_SELECTED && !hanabi_game_data->game_board->all_clues_left() )
			software_event_queue->push(ACTION_DISCARD);
		//else;//all clues left cannot discard card
	}
}