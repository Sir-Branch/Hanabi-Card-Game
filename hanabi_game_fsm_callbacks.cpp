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
	Hanabi_Name_Is_Packet name_is_packet(user_data->player_name);
	user_data->net_connection->send_packet(&name_is_packet);
}

void start_game_send_start_info_pck(hanabi_game_data_t *user_data)
{
	//Sort Cards etc
	if( !user_data->game_board->start_game() )
		;//Error unable to start game
	
	Hanabi_Start_Info_Packet start_info_paket(user_data->game_board->otherplayers_hand,
		user_data->game_board->my_cards);
	user_data->net_connection->send_packet(&start_info_paket);
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

void manage_play_send_ack (hanabi_game_data_t *user_data)
{
	
	
	send_ack_pck(user_data);
}

void manage_you_have_send_ack(hanabi_game_data_t *user_data)
{
	
	
	send_ack_pck(user_data);
}

void manage_discard_send_ack (hanabi_game_data_t *user_data)
{
	
	
	send_ack_pck(user_data);
}

#endif
