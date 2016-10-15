/* 
 * File:   Hanabi_You_Have_Packet.h
 * Author: r2d2
 *
 * Created on October 10, 2016, 8:46 PM
 */

#ifndef HANABI_YOU_HAVE_PACKET_H
#define HANABI_YOU_HAVE_PACKET_H

#include "TFTP_Packet.h"

class Hanabi_You_Have_Packet : public TFTP_Packet {
public:
	Hanabi_You_Have_Packet(unsigned char suit_or_value );

private:

};

#endif /* HANABI_YOU_HAVE_PACKET_H */

