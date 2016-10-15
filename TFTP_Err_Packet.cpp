/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TFTP_Err_Packet.cpp
 * Author: r2d2
 * 
 * Created on July 25, 2016, 12:24 PM
 */

#include "TFTP_Err_Packet.h"
#include "TFTP_Packet.h"
#include <cstring>

/*
          2 bytes  2 bytes        string    1 byte
          ----------------------------------------
   ERROR | 05    |  ErrorCode |   ErrMsg   |   0  |
          ----------------------------------------
*/
TFTP_Err_Packet::TFTP_Err_Packet(errors_tftp_t error_code,const char *err_msg) : TFTP_Packet(SIZE_OPCODE+SIZE_ERRCODE+strlen(err_msg)+TERM_SIZE) 
{
	if(packet_data!=NULL)
	{
		tftp_packet_type = TFTP_ERR_PCK; 
		packet_data[0]='0';//primer caracter opcode
		packet_data[1]=OP_ERROR+'0';//segundo caracter opcode
		packet_data[2]='0';//segundo caracter opcode
		packet_data[3]=error_code+'0';//segundo caracter opcode
		strcpy(packet_data+4,err_msg);
	}
	
	
}

TFTP_Err_Packet::TFTP_Err_Packet(const TFTP_Err_Packet& orig) {
}

TFTP_Err_Packet::~TFTP_Err_Packet() {
}


