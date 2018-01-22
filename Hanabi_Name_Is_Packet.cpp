/* 
 * File:   Hanabi_Name_Is_Packet.cpp
 * Author: r2d2
 * 
 * Created on October 9, 2016, 11:41 PM
 */

#include "Hanabi_Name_Is_Packet.h"
#include "Hanabi_Network_Defines.h"

#define HANABI_NAME_IS_SIZE_COUNT	1
#define MAX_STRLEN	254	
#define MIN(x,y) ((x < y)?(x):(y))

Hanabi_Name_Is_Packet::Hanabi_Name_Is_Packet(const char * const name ) : TFTP_Packet(HANABI_PCKS_OP_SIZE+ HANABI_NAME_IS_SIZE_COUNT + MIN(MAX_STRLEN,strlen(name)))
{
	unsigned char packet_length = MIN(MAX_STRLEN,strlen(name));
	packet_data[0] = HANABI_NAME_IS_OP;
	packet_data[1] = packet_length;
	memcpy(packet_data+2,name, packet_length );
	//VA SIN TERMINADOR packet_data[ MIN(MAX_STRLEN,strlen(name)) ] = '/0'; //Manually setting terminator
	
}

