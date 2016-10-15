/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TFTP_Data_Packet.h
 * Author: r2d2
 *
 * Created on July 25, 2016, 12:01 PM
 */

#ifndef TFTP_DATA_PACKET_H
#define TFTP_DATA_PACKET_H

#include "TFTP_Packet.h"

class TFTP_Data_Packet : public TFTP_Packet {
public:
    TFTP_Data_Packet();
    TFTP_Data_Packet(uint16_t block_num,unsigned int num_bytes,const char * source);
    TFTP_Data_Packet(const TFTP_Data_Packet& orig);
    virtual ~TFTP_Data_Packet();
private:

};

#endif /* TFTP_DATA_PACKET_H */

