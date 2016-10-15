/*
 * File:   Hanabi_You_Have_Packet.cpp
 * Author: r2d2
 * 
 * Created on October 10, 2016, 8:46 PM
 */

#include "Hanabi_You_Have_Packet.h"
#include "TFTP_Packet.h"
#include "Hanabi_Network_Defines.h"

Hanabi_You_Have_Packet::Hanabi_You_Have_Packet(unsigned char suit_or_value ) : TFTP_Packet(HANABI_PCKS_OP_SIZE + sizeof(char)) {
	
	packet_data[0] = HANABI_YOU_HAVE_OP;
	packet_data[1] = (char) suit_or_value;
}

