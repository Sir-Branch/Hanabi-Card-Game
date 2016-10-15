/* 
 * File:   Hanabi_Play_Packet.cpp
 * Author: r2d2
 * 
 * Created on October 10, 2016, 8:14 PM
 */

#include "Hanabi_Play_Packet.h"
#include "TFTP_Packet.h"
#include "Hanabi_Network_Defines.h"

Hanabi_Play_Packet::Hanabi_Play_Packet(unsigned char card_position_hand) : TFTP_Packet(HANABI_PCKS_OP_SIZE + sizeof(char) ) 
{
	packet_data[0] = HANABI_PLAY_OP;
	packet_data[1] = card_position_hand;
	
}


