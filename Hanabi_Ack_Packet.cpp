/* 
 * File:   Hanabi_Ack_Packet.cpp
 * Author: r2d2
 * 
 * Created on October 10, 2016, 3:42 PM
 */

#include "Hanabi_Ack_Packet.h"
#include "TFTP_Packet.h"
#include "Hanabi_Network_Defines.h"


Hanabi_Ack_Packet::Hanabi_Ack_Packet() : TFTP_Packet(HANABI_PCKS_OP_SIZE) {
	packet_data[0] = HANABI_ACK_OP;
}


