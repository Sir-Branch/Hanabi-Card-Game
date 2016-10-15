/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TFTP_Ack_Packet.h
 * Author: r2d2
 *
 * Created on July 25, 2016, 12:01 PM
 */

#ifndef TFTP_ACK_PACKET_H
#define TFTP_ACK_PACKET_H

#include "TFTP_Packet.h"

class TFTP_Ack_Packet : public TFTP_Packet{
public:
    TFTP_Ack_Packet(uint16_t block_num);
    TFTP_Ack_Packet(const TFTP_Ack_Packet& orig);
    virtual ~TFTP_Ack_Packet();
private:
    
};

#endif /* TFTP_ACK_PACKET_H */

