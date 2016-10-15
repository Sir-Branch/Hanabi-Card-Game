/* 
 * File:   Hanabi_Match_Over_Packet.cpp
 * Author: r2d2
 * 
 * Created on October 10, 2016, 3:50 PM
 */

#include "Hanabi_Match_Over_Packet.h"
#include "TFTP_Packet.h"
#include "Hanabi_Network_Defines.h"


Hanabi_Match_Over_Packet::Hanabi_Match_Over_Packet() : TFTP_Packet(HANABI_PCKS_OP_SIZE){
	packet_data[0] = HANABI_MATCH_OVER_OP;

}

