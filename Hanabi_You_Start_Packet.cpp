/* 
 * File:   Hanabi_You_Start_Packet.cpp
 * Author: r2d2
 * 
 * Created on October 10, 2016, 3:46 PM
 */

#include "Hanabi_You_Start_Packet.h"
#include "TFTP_Packet.h"
#include "Hanabi_Network_Defines.h"


Hanabi_You_Start_Packet::Hanabi_You_Start_Packet() : TFTP_Packet(HANABI_PCKS_OP_SIZE){
	packet_data[0] = HANABI_YOU_START_OP;

}
