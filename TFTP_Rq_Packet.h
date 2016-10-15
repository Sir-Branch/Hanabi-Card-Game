/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TFTP_Rq_Packet.h
 * Author: r2d2
 *
 * Created on July 25, 2016, 12:01 PM
 */

#ifndef TFTP_RQ_PACKET_H
#define TFTP_RQ_PACKET_H
#include "TFTP_Packet.h"

class TFTP_Rq_Packet : public TFTP_Packet {
public:
    TFTP_Rq_Packet();
    TFTP_Rq_Packet(opcode_t opcode,const char *filename,rq_mode_t mode);
    TFTP_Rq_Packet(const TFTP_Rq_Packet& orig);
    virtual ~TFTP_Rq_Packet();
private:

};

#endif /* TFTP_RQ_PACKET_H */

