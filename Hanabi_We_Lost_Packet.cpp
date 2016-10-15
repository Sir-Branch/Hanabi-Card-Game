/* 
 * File:   Hanabi_We_Lost_Packet.cpp
 * Author: r2d2
 * 
 * Created on October 10, 2016, 3:48 PM
 */

#include "Hanabi_We_Lost_Packet.h"
#include "TFTP_Packet.h"
#include "Hanabi_Network_Defines.h"

Hanabi_We_Lost_Packet::Hanabi_We_Lost_Packet() : TFTP_Packet(HANABI_PCKS_OP_SIZE){
	packet_data[0] = HANABI_WE_LOST_OP;
}

