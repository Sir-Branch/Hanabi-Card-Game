/* 
 * File:   Hanabi_Play_Again_Packet.cpp
 * Author: r2d2
 * 
 * Created on October 10, 2016, 3:52 PM
 */

#include "Hanabi_Play_Again_Packet.h"
#include "TFTP_Packet.h"
#include "Hanabi_Network_Defines.h"


Hanabi_Play_Again_Packet::Hanabi_Play_Again_Packet() : TFTP_Packet(HANABI_PCKS_OP_SIZE) {
	packet_data[0] = HANABI_PLAY_AGAIN_OP;

}

