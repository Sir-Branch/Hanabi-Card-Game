/* 
 * File:   Hanabi_Name_Packet.cpp
 * Author: r2d2
 * 
 * Created on October 10, 2016, 12:03 AM
 */

#include "Hanabi_Name_Packet.h"
#include "TFTP_Packet.h"
#include "Hanabi_Network_Defines.h"
#define NAME_OP_CODE	0x11

#warning "No esta completo este paquete"
Hanabi_Name_Packet::Hanabi_Name_Packet() : TFTP_Packet(HANABI_PCKS_OP_SIZE) {
	packet_data[0] = HANABI_NAME_OP;
	
}
