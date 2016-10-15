/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TFTP_Rq_Packet.cpp
 * Author: r2d2
 * 
 * Created on July 25, 2016, 12:01 PM
 */

#include "TFTP_Rq_Packet.h"
#include "TFTP_Packet.h"
#include <cstring>

/*
 * 
 *		  2 bytes    string   1 byte     string   1 byte
 *         -----------------------------------------------
 *  RRQ/  | 01/02 |  Filename  |   0  |    Mode    |   0  |
 *  WRQ    -----------------------------------------------
 * 
 * 
 */
TFTP_Rq_Packet::TFTP_Rq_Packet(opcode_t opcode,const char *filename,rq_mode_t mode) : TFTP_Packet(SIZE_OPCODE+strlen(filename)+TERM_SIZE+mode)
{
	if(packet_data!=NULL)
	{
		tftp_packet_type = TFTP_RQ_PCK; 
		packet_data[0]='0';//primer caracter opcode
		packet_data[1]=opcode+'0';//segundo caracter opcode
		strcpy(packet_data+SIZE_OPCODE,filename);
		switch(mode)
		{
			case NETASCII:
				strcpy(packet_data+strlen(filename)+3,"netascii");
				break;
			case OCTET:
				strcpy(packet_data+strlen(filename)+3,"octet");
				break;
			case MAIL:
				strcpy(packet_data+strlen(filename)+3,"mail");
				break;
			default:
				break;
		}
		//se copio el terminador 0 en los strings
	}
    
}
TFTP_Rq_Packet::TFTP_Rq_Packet() {
}

TFTP_Rq_Packet::TFTP_Rq_Packet(const TFTP_Rq_Packet& orig) {
}

TFTP_Rq_Packet::~TFTP_Rq_Packet() {
}


