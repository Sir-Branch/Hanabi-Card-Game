/* 
 * File:   Hanabi_Quit_Packet.cpp
 * Author: r2d2
 * 
 * Created on October 10, 2016, 3:52 PM
 */

#include "Hanabi_Quit_Packet.h"
#include "TFTP_Packet.h"
#include "Hanabi_Network_Defines.h"

Hanabi_Quit_Packet::Hanabi_Quit_Packet() : TFTP_Packet(SIZE_OPCODE) {
	packet_data[0] = HANABI_QUIT_OP;

}


