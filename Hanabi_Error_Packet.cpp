/* 
 * File:   Hanabi_Error_Packet.cpp
 * Author: r2d2
 * 
 * Created on October 10, 2016, 3:53 PM
 */

#include "Hanabi_Error_Packet.h"
#include "TFTP_Packet.h"
#include "Hanabi_Network_Defines.h"


Hanabi_Error_Packet::Hanabi_Error_Packet() : TFTP_Packet(HANABI_PCKS_OP_SIZE) {
	packet_data[0] = HANABI_ERROR_OP;

}


