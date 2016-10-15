/* 
 * File:   Hanabi_IStart_Packet.cpp
 * Author: r2d2
 * 
 * Created on October 10, 2016, 3:47 PM
 */

#include "Hanabi_IStart_Packet.h"
#include "TFTP_Packet.h"
#include "Hanabi_Network_Defines.h"


Hanabi_IStart_Packet::Hanabi_IStart_Packet() : TFTP_Packet(HANABI_PCKS_OP_SIZE) {
	packet_data[0] = HANABI_ISTART_OP;

}

