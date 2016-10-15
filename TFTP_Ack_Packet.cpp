/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TFTP_Ack_Packet.cpp
 * Author: r2d2
 * 
 * Created on July 25, 2016, 12:01 PM
 */

#include "TFTP_Ack_Packet.h"
#include "TFTP_Packet.h"

/*
          2 bytes    2 bytes
          -------------------
   ACK   | 04    |   Block #  |
          --------------------
 * 
 * */
TFTP_Ack_Packet::TFTP_Ack_Packet(uint16_t block_num) : TFTP_Packet(SIZE_OPCODE+SIZE_BLOCK_NUM) 
{
	if(packet_data!=NULL)
	{
		tftp_packet_type = TFTP_ACK_PCK; 
		packet_data[0]='0';//primer caracter opcode
		packet_data[1]=OP_ACK+'0';//segundo caracter opcode
		*(uint16_t *)(packet_data+2)=block_num;//muy feo??
	}
	
	
}

TFTP_Ack_Packet::TFTP_Ack_Packet(const TFTP_Ack_Packet& orig) {
}

TFTP_Ack_Packet::~TFTP_Ack_Packet() {
}



