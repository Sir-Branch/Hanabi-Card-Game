/* 
 * File:   Hanabi_Start_Info_Packet.h
 * Author: r2d2
 *
 * Created on October 10, 2016, 12:28 AM
 */

#ifndef HANABI_START_INFO_PACKET_H
#define HANABI_START_INFO_PACKET_H

#include "TFTP_Packet.h"
#include "Hanabi_Network_Defines.h"
#include "Hanabi_Card.h"

class Hanabi_Start_Info_Packet : public TFTP_Packet{
public:
   Hanabi_Start_Info_Packet( Hanabi_Card client_hand[HANABI_HAND_SIZE], Hanabi_Card server_hand[HANABI_HAND_SIZE] );

private:

};

#endif /* HANABI_START_INFO_PACKET_H */

