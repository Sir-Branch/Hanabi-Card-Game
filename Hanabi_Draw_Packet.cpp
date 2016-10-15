/* 
 * File:   Hanabi_Draw_Packet.cpp
 * Author: r2d2
 * 
 * Created on October 10, 2016, 8:19 PM
 */

#include "Hanabi_Draw_Packet.h"
#include "TFTP_Packet.h"
#include "Hanabi_Network_Defines.h"
#include "Hanabi_Card.h"

Hanabi_Draw_Packet::Hanabi_Draw_Packet(Hanabi_Card card_drawn) : TFTP_Packet(HANABI_PCKS_OP_SIZE + HANABI_CARD_SIZE_PCK){
	
	packet_data[0] = HANABI_DRAW_OP;
	packet_data[1] = (char) card_drawn.get_value();
	packet_data[2] = (char) card_drawn.get_suit();
}
