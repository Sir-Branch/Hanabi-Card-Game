/* 
 * File:   hanabi_game_fsm_callbacks.cpp
 * Author: r2d2
 *
 * Created on January 10, 2018, 1:12 PM
 */
#if 1	
#include "Hanabi_Ack_Packet.h"
#include "Hanabi_Discard_Packet.h"
#include "Hanabi_Draw_Packet.h"
#include "Hanabi_Error_Packet.h"
#include "Hanabi_Game_Over_Packet.h"
#include "Hanabi_IStart_Packet.h"
#include "Hanabi_Match_Over_Packet.h"
#include "Hanabi_Name_Is_Packet.h"
#include "Hanabi_Name_Packet.h"
#include "Hanabi_Play_Again_Packet.h"
#include "Hanabi_Play_Packet.h"
#include "Hanabi_Quit_Packet.h"
#include "Hanabi_Start_Info_Packet.h"
#include "Hanabi_We_Lost_Packet.h"
#include "Hanabi_We_Won_Packet.h"
#include "Hanabi_You_Have_Packet.h"
#include "Hanabi_You_Start_Packet.h"
#include "setting_management.h"
#include "hanabi_game_fsm_callbacks.h"
#include "Hanabi_Board.h"
#include "Eda_Menu_Game.h"


void do_nothing (hanabi_game_data_t *user_data)
{
	;
}

void send_name_pck(hanabi_game_data_t *user_data)
{
	Hanabi_Name_Packet name_packet;
	user_data->net_connection->send_packet(&name_packet);
}

void send_ack_pck(hanabi_game_data_t *user_data)
{
	Hanabi_Ack_Packet ack_packet;
	user_data->net_connection->send_packet(&ack_packet);
}

void send_name_is_pck(hanabi_game_data_t *user_data)
{
	Hanabi_Name_Is_Packet name_is_packet(user_data->player_name.c_str());
	user_data->net_connection->send_packet(&name_is_packet);
}

void start_game_send_start_info_pck(hanabi_game_data_t *user_data)
{
	//Sort Cards etc
	if( !user_data->game_board->start_game() )
		;//Error unable to start game
	
	Hanabi_Start_Info_Packet start_info_packet(user_data->game_board->otherplayers_hand,
		user_data->game_board->my_cards);
	user_data->net_connection->send_packet(&start_info_packet);
}

void manage_receive_start_info(hanabi_game_data_t *user_data)
{
	user_data->game_board->receive_start_game(user_data->last_received_pck->get_data_pck());
	send_ack_pck(user_data);
	
}

void create_send_random_start(hanabi_game_data_t *user_data)
{
	int random;
	random = rand()%2;
	if (random)
	{
		Hanabi_IStart_Packet i_start;
		user_data->net_connection->send_packet(&i_start);
	}
	else 
	{
		Hanabi_You_Start_Packet you_start;
		user_data->net_connection->send_packet(&you_start);
	}
}

void manage_play_send_ack(hanabi_game_data_t *user_data)
{
	user_data->game_board->receive_action_play_card(user_data->last_received_pck->get_data_pck()[1]);
	send_ack_pck(user_data);
}

#warning "Hacer esta funcion"
void manage_you_have_send_ack(hanabi_game_data_t *user_data)
{
	
	send_ack_pck(user_data);
}

void manage_discard_send_ack(hanabi_game_data_t *user_data)
{
	user_data->game_board->receive_action_discard_card(user_data->last_received_pck->get_data_pck()[1]);
	send_ack_pck(user_data);
}

void manage_name_is_ack(hanabi_game_data_t *user_data)
{
	char temp_buff[256];
	unsigned char name_len = user_data->last_received_pck->get_data_pck()[1];
	memcpy(temp_buff,user_data->last_received_pck->get_data_pck() + 2,name_len);
	temp_buff[name_len] = '\0';
	
	user_data->game_board->other_player_name = std::string(temp_buff);
	send_ack_pck(user_data);
	
}
void send_you_have(hanabi_game_data_t *user_data)
{
	Hanabi_You_Have_Packet you_have(((Eda_Menu_Game *)user_data->active_menu)->get_selected_clue());
	user_data->net_connection->send_packet(&you_have);
}

void send_play_pck(hanabi_game_data_t *user_data)
{
	Hanabi_Play_Packet play_pck (((Eda_Menu_Game*) user_data->active_menu)->get_selected_card());
	user_data->net_connection->send_packet(&play_pck);
}

void send_discard_pck(hanabi_game_data_t *user_data)
{
	Hanabi_Discard_Packet discard_pck (((Eda_Menu_Game*) user_data->active_menu)->get_selected_card());
	user_data->net_connection->send_packet(&discard_pck);
}

void send_error(hanabi_game_data_t *user_data)
{
	Hanabi_Error_Packet error;
	user_data->net_connection->send_packet(&error);
}

void remove_card(hanabi_game_data_t *user_data)
{
	hanabi_values_t received_value = (hanabi_values_t)user_data->last_received_pck->get_data_pck()[1];
	hanabi_suits_t received_suit = (hanabi_suits_t)user_data->last_received_pck->get_data_pck()[2];
	user_data->game_board->hanabi_game_deck.remove_specific_card(Hanabi_Card(received_suit, received_value));
#warning "puede llegar a ir un ACK aca"
}

void send_draw_card(hanabi_game_data_t *user_data)
{
	//Hanabi_Draw_Packet draw_packet;
	//user_data->net_connection->send_packet(&draw_packet);
}
#endif
