/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TFTP_Err_Packet.h
 * Author: r2d2
 *
 * Created on July 25, 2016, 12:24 PM
 */

#ifndef TFTP_ERR_PACKET_H
#define TFTP_ERR_PACKET_H

#include "TFTP_Packet.h"
class TFTP_Err_Packet : public TFTP_Packet{
public:
    TFTP_Err_Packet(errors_tftp_t error_code,const char *err_msg);
    TFTP_Err_Packet(const TFTP_Err_Packet& orig);
    virtual ~TFTP_Err_Packet();
private:

};

#endif /* TFTP_ERR_PACKET_H */

