/* 
 * File:   Hanabi_Start_Info_Packet.cpp
 * Author: r2d2
 * 
 * Created on October 10, 2016, 12:28 AM
 */

#include "Hanabi_Start_Info_Packet.h"
#include "Hanabi_Network_Defines.h"
#include "TFTP_Packet.h"
#include "Hanabi_Card.h"
#include "Hanabi_Board.h"



Hanabi_Start_Info_Packet::Hanabi_Start_Info_Packet(Hanabi_Card client_hand[HANABI_HAND_SIZE], in_game_hanabi_Card_t server_hand[HANABI_HAND_SIZE]) 
: TFTP_Packet(HANABI_PCKS_OP_SIZE+ 2 * HANABI_HAND_SIZE  * HANABI_CARD_SIZE_PCK) 
{
	packet_data[0] = HANABI_START_INFO_OP;	
	for(int i = 0 , j = 0; i < HANABI_HAND_SIZE*HANABI_HAND_SIZE ; i += HANABI_CARD_SIZE_PCK , j++)
	{
		packet_data[1+i] = (unsigned char)client_hand[j].get_value() + '0'; //Value in number convert to ascii
		packet_data[2+i] = (unsigned char)client_hand[j].get_suit();
		packet_data[1+i+HANABI_HAND_SIZE * HANABI_CARD_SIZE_PCK]= (unsigned char)server_hand[j].playing_card.get_value() + '0'; //Value in number convert to ascii
		packet_data[2+i+HANABI_HAND_SIZE * HANABI_CARD_SIZE_PCK]= (unsigned char)server_hand[j].playing_card.get_suit();
	}
}

bool verify_start_info_packet(void)
{
	
	return true; // TRUE , but should verify;
}