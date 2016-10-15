/* 
 * File:   Hanabi_Play_Packet.h
 * Author: r2d2
 *
 * Created on October 10, 2016, 8:14 PM
 */

#ifndef HANABI_PLAY_PACKET_H
#define HANABI_PLAY_PACKET_H

#include "TFTP_Packet.h"

class Hanabi_Play_Packet : public TFTP_Packet {
public:
	Hanabi_Play_Packet(unsigned char card_position_hand);

private:

};

#endif /* HANABI_PLAY_PACKET_H */

