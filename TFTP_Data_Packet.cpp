/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TFTP_Data_Packet.cpp
 * Author: r2d2
 * 
 * Created on July 25, 2016, 12:01 PM
 */
#include "TFTP_Packet.h"
#include "TFTP_Data_Packet.h"
#include <iostream>

TFTP_Data_Packet::TFTP_Data_Packet() {
}

TFTP_Data_Packet::TFTP_Data_Packet(const TFTP_Data_Packet& orig) {
}

TFTP_Data_Packet::~TFTP_Data_Packet() {
}


/*
 *			2 bytes    2 bytes       n bytes
 *         ---------------------------------
 *  DATA  | 03    |   Block #  |    Data    |
 *         ---------------------------------
 * num_bytes 1-512
 * unsigned int overflow defined in c standard .
 */
TFTP_Data_Packet::TFTP_Data_Packet(uint16_t block_num,unsigned int num_bytes,const char * source) : TFTP_Packet(SIZE_OPCODE+SIZE_BLOCK_NUM+num_bytes)
{
	if(packet_data!=NULL)
	{
		tftp_packet_type = TFTP_DATA_PCK; 
		packet_data[0]='0';//primer caracter opcode
		packet_data[1]=OP_DATA+'0';//segundo caracter opcode
		*(uint16_t *)(packet_data+2)=block_num;//muy feo??
		std::cout<< "Data Packet created with block_num" << *(uint16_t*)(packet_data+2) <<std::endl;

		memcpy(packet_data+4,source,num_bytes);
	}
    
}
