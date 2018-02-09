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
#include "Eda_Menu_Gameover.h"


void do_nothing (hanabi_game_data_t *user_data)
{

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
		user_data->other_players_turn = false;
		message_my_turn(user_data);
	}
	else 
	{
		Hanabi_You_Start_Packet you_start;
		user_data->net_connection->send_packet(&you_start);
		user_data->other_players_turn = true;
		message_other_player_turn(user_data);

	}
}

void manage_play_send_ack(hanabi_game_data_t *user_data)
{
	user_data->game_board->receive_action_play_card(user_data->last_received_pck->get_data_pck()[1]-1);
	if(user_data->game_board->any_lives_left())
	{
		send_ack_pck(user_data);
	}
	else
	{
		Hanabi_We_Lost_Packet we_lost;
		user_data->net_connection->send_packet(&we_lost);
		user_data->software_event_queue.push(RECEIVE_WE_LOST);
	}
}

void manage_you_have(hanabi_game_data_t *user_data)
{
	user_data->game_board->receive_action_get_clue(user_data->last_received_pck->get_data_pck()[1]);
	user_data->message_event_queue.push(">Clue Received fixed func!");
	user_data->other_players_turn = false;
	message_my_turn(user_data);
}

void manage_discard_send_ack(hanabi_game_data_t *user_data)
{
	user_data->game_board->receive_action_discard_card(user_data->last_received_pck->get_data_pck()[1]-1);
	send_ack_pck(user_data);
}

void manage_name_is_ack(hanabi_game_data_t *user_data)
{
	char temp_buff[256];
	unsigned char name_len = user_data->last_received_pck->get_data_pck()[1];
	memcpy(temp_buff,user_data->last_received_pck->get_data_pck() + 2,name_len);
	temp_buff[name_len] = '\0';
	
#warning "make draw receive user data to fix"
	user_data->game_board->other_player_name = std::string(temp_buff);
	user_data->other_player_name = std::string(temp_buff);
	
	send_ack_pck(user_data);
	
}
void send_you_have(hanabi_game_data_t *user_data)
{
	unsigned char value_or_suit = ((Eda_Menu_Game *)user_data->active_menu)->get_selected_clue();
	user_data->game_board->player_action_give_clue(value_or_suit);
	Hanabi_You_Have_Packet you_have(value_or_suit);
	user_data->net_connection->send_packet(&you_have);
	user_data->other_players_turn = true;
	
	user_data->message_event_queue.push(">Clue Sent!!");
	message_other_player_turn(user_data);
}

void send_play_pck(hanabi_game_data_t *user_data)
{
	unsigned int selected_card =((Eda_Menu_Game*) user_data->active_menu)->get_selected_card();
	user_data->game_board->player_action_play_card(selected_card);	
	Hanabi_Play_Packet play_pck(selected_card+1); //Packets goes 1 to 6
	user_data->net_connection->send_packet(&play_pck);

	user_data->message_event_queue.push(">Card played!!");
}

void send_discard_pck(hanabi_game_data_t *user_data)
{
	unsigned int selected_card = ((Eda_Menu_Game*) user_data->active_menu)->get_selected_card();
	user_data->game_board->player_action_discard_card(selected_card);
	Hanabi_Discard_Packet discard_pck(selected_card+1);
	user_data->net_connection->send_packet(&discard_pck);
	
	user_data->message_event_queue.push(">Card discarded!!");
}

void send_error(hanabi_game_data_t *user_data)
{
	user_data->message_event_queue.push(">Error sent!!");
	Hanabi_Error_Packet error;
	user_data->net_connection->send_packet(&error);
}

void remove_card_to_hand(hanabi_game_data_t *user_data)
{
	hanabi_values_t received_value = (hanabi_values_t)(user_data->last_received_pck->get_data_pck()[1] - '0');
	hanabi_suits_t received_suit = (hanabi_suits_t)user_data->last_received_pck->get_data_pck()[2];
	user_data->game_board->receive_action_draw_card(Hanabi_Card(received_suit, received_value));
	user_data->other_players_turn = false;
	message_my_turn(user_data);

#warning "puede llegar a ir un ACK aca"
}

void send_draw_card(hanabi_game_data_t *user_data)
{
	if(user_data->game_board->draw_card(user_data->game_board->my_card_replace) )
	{
		Hanabi_Draw_Packet draw_packet(user_data->game_board->my_cards[user_data->game_board->my_card_replace].playing_card);
		user_data->net_connection->send_packet(&draw_packet);
	}
	else
	{
		Hanabi_Draw_Packet draw_packet;//Last Draw Packet
		user_data->net_connection->send_packet(&draw_packet);
		user_data->software_event_queue.push(LAST_DRAW_SENT);
	}
	
	user_data->other_players_turn = true;
	message_other_player_turn(user_data);
#warning "Add end game if no draw possible"
}

void message_ustart(hanabi_game_data_t *user_data)
{
	user_data->message_event_queue.push(">It's your turn!!");
}

void message_other_player_turn(hanabi_game_data_t *user_data)
{
	user_data->message_event_queue.push(">It's " + user_data->other_player_name + " turn!!");
}

void message_my_turn(hanabi_game_data_t *user_data)
{
	user_data->message_event_queue.push(">It's your turn!!");
}


void receive_istart_send_ack(hanabi_game_data_t *user_data)
{
	user_data->message_event_queue.push(">It's " + user_data->other_player_name + " turn!!");
	send_ack_pck(user_data);
}


void manage_final_play(hanabi_game_data_t *user_data)
{
	user_data->game_board->receive_action_play_card(user_data->last_received_pck->get_data_pck()[1]-1);
	std::cout<<"hola"<<std::endl;

	if(!user_data->game_board->any_lives_left())
	{
		Hanabi_We_Lost_Packet we_lost;
		user_data->net_connection->send_packet(&we_lost);
		user_data->software_event_queue.push(RECEIVE_WE_LOST);
	}
	else if(user_data->game_board->score != 25)
	{
		Hanabi_We_Lost_Packet we_lost;
		user_data->net_connection->send_packet(&we_lost);
		user_data->software_event_queue.push(RECEIVE_WE_LOST);
	}
	else 
	{
		Hanabi_We_Won_Packet we_won;
		user_data->net_connection->send_packet(&we_won);
		user_data->software_event_queue.push(RECEIVE_WE_WON);
	}
	//send_ack_pck(user_data);
}
void manage_final_you_have(hanabi_game_data_t *user_data)
{
	Hanabi_We_Lost_Packet we_lost;
	user_data->game_board->receive_action_get_clue(user_data->last_received_pck->get_data_pck()[1]);
	user_data->message_event_queue.push(">Clue Received fixed func!");
	user_data->net_connection->send_packet(&we_lost);
	user_data->software_event_queue.push(RECEIVE_WE_LOST);
	user_data->other_players_turn = false;
}


void manage_final_discard(hanabi_game_data_t *user_data)
{
	user_data->game_board->receive_action_discard_card(user_data->last_received_pck->get_data_pck()[1]-1);
	Hanabi_We_Lost_Packet we_lost;
	user_data->net_connection->send_packet(&we_lost);
	user_data->software_event_queue.push(RECEIVE_WE_LOST);
	
	///send_ack_pck(user_data);
}

void manage_final_play_send_result(hanabi_game_data_t *user_data)
{
	manage_final_play(user_data);	//send_ack_pck(user_data);
	TFTP_Packet game_result;
	get_game_result(user_data, &game_result);
	send_game_result(user_data);
}

void manage_final_you_have_send_result(hanabi_game_data_t *user_data)
{
	manage_final_you_have(user_data);
	send_game_result(user_data);
}

void manage_final_discard_send_result(hanabi_game_data_t *user_data)
{
	manage_final_discard(user_data);
	send_game_result(user_data);
	///send_ack_pck(user_data);
}

void change_play_again_menu(hanabi_game_data_t *user_data)
{
	delete user_data->active_menu;
	user_data->active_menu =new Eda_Menu_GameOver();
}

void get_game_result(hanabi_game_data_t *user_data, TFTP_Packet * game_result)
{
	if( user_data->game_board->any_lives_left())
		*game_result = Hanabi_We_Lost_Packet();
	else if(user_data->game_board->calculate_score() == MAX_SCORE)
		*game_result = Hanabi_We_Lost_Packet();
	else
		*game_result = Hanabi_Match_Over_Packet();

}

void send_game_result(hanabi_game_data_t *user_data)
{
	TFTP_Packet game_result;
	get_game_result(user_data, &game_result);
	user_data->net_connection->send_packet(&game_result);
}


#endif
