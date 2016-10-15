/* 
 * File:   Hanabi_Name_Is_Packet.h
 * Author: r2d2
 *
 * Created on October 9, 2016, 11:41 PM
 */

#ifndef HANABI_NAME_IS_PACKET_H
#define HANABI_NAME_IS_PACKET_H

#include "TFTP_Packet.h"

class Hanabi_Name_Is_Packet : public TFTP_Packet {
public:
    Hanabi_Name_Is_Packet(const char * const name );

private:

};

#endif /* HANABI_NAME_IS_PACKET_H */

