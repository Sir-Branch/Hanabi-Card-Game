/* 
 * File:   Hanabi_Discard_Packet.h
 * Author: r2d2
 *
 * Created on October 10, 2016, 7:57 PM
 */

#ifndef HANABI_DISCARD_PACKET_H
#define HANABI_DISCARD_PACKET_H

#include "TFTP_Packet.h"

class Hanabi_Discard_Packet : public TFTP_Packet {
public:
	Hanabi_Discard_Packet(unsigned char card_position_hand);

private:

};

#endif /* HANABI_DISCARD_PACKET_H */

