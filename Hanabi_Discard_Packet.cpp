/* 
 * File:   Hanabi_Discard_Packet.cpp
 * Author: r2d2
 * 
 * Created on October 10, 2016, 7:57 PM
 */

#include "Hanabi_Discard_Packet.h"
#include "TFTP_Packet.h"
#include "Hanabi_Network_Defines.h"

Hanabi_Discard_Packet::Hanabi_Discard_Packet(unsigned char card_position_hand) : TFTP_Packet(HANABI_PCKS_OP_SIZE + sizeof(char) ) {
	
	packet_data[0] = HANABI_DISCARD_OP;
	packet_data[1] = card_position_hand;
	
}

