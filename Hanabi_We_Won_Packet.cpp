/* 
 * File:   Hanabi_We_Won_Packet.cpp
 * Author: r2d2
 * 
 * Created on October 10, 2016, 3:48 PM
 */

#include "Hanabi_We_Won_Packet.h"
#include "TFTP_Packet.h"
#include "Hanabi_Network_Defines.h"



Hanabi_We_Won_Packet::Hanabi_We_Won_Packet() : TFTP_Packet(HANABI_PCKS_OP_SIZE){
	packet_data[0] = HANABI_WE_WON_OP;
}

