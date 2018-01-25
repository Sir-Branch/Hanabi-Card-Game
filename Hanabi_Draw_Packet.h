/* 
 * File:   Hanabi_Draw_Packet.h
 * Author: r2d2
 *
 * Created on October 10, 2016, 8:19 PM
 */

#ifndef HANABI_DRAW_PACKET_H
#define HANABI_DRAW_PACKET_H

#include "TFTP_Packet.h"
#include "Hanabi_Card.h"
class Hanabi_Draw_Packet : public TFTP_Packet{
public:
	Hanabi_Draw_Packet(Hanabi_Card card_drawn);
	Hanabi_Draw_Packet(); // LAST HAND DRAW PACKET
private:

};

#endif /* HANABI_DRAW_PACKET_H */

