/* 
 * File:   Hanabi_Network_Defines.h
 * Author: r2d2
 *
 * Created on October 10, 2016, 3:55 PM
 */

#ifndef HANABI_NETWORK_DEFINES_H
#define HANABI_NETWORK_DEFINES_H


#define HANABI_PCKS_OP_SIZE			1 //HANABI OPCODE PCKS SIZE
#define HANABI_HAND_SIZE			6
#define HANABI_CARD_SIZE_PCK		2	//Size of card in pck
#define NO_CARD_TO_DRAW				0xFF
enum packets_type
{   HANABI_ACK_OP = 0x01,			HANABI_NAME_OP = 0x10,		HANABI_NAME_IS_OP = 0x11,	HANABI_START_INFO_OP = 0x12 , //Game configuration and communication packets
    HANABI_YOU_START_OP = 0x20,		HANABI_ISTART_OP = 0x21,	//Game start packets
    HANABI_DISCARD_OP = 0x32,		HANABI_PLAY_OP = 0x33,		HANABI_YOU_HAVE_OP = 0x34 ,		HANABI_DRAW_OP = 0x35 , //GamePlay packets 
    HANABI_WE_WON_OP = 0x40,		HANABI_WE_LOST_OP = 0x41,	HANABI_MATCH_OVER_OP = 0x42 , //Match End packets
    HANABI_PLAY_AGAIN_OP = 0x50,    HANABI_GAME_OVER_OP = 0x51, //Game finished
    HANABI_QUIT_OP = 0xFE,			HANABI_ERROR_OP = 0xFF  //Quit and error handling
};


/*
#include <cstdlib>
#include <iostream>
#include "TFTPServer.h"
#include "TFTPClient.h"
#include "TFTP_Packet.h"
#include "Hanabi_Name_Is_Packet.h"
using namespace std;

int main(int argc, char** argv) {
	apr_initialize();

	TFTPCxn * cxn = new TFTPClient();
	std::cout << "Will search for server for 5 seconds \n";
	if(!((TFTPClient *)cxn)->try_connect_server(5.0,HOME_ADRESS, DEF_REMOTE_PORT, DEF_IPMODE ))
	{
		delete cxn;
		cxn = new TFTPServer(HOME_ADRESS, DEF_REMOTE_PORT, DEF_IPMODE );
		std::cout << "Server will now try listening for client for 600secs \n";
		if (((TFTPServer*)cxn)->listen_for_client(600.0) )
		{
			std::cout << "Able to connect to client \n";
		
			std::cout << "Server press character to send name packet \n";
			getchar();
			TFTP_Packet * tosend = new Hanabi_Name_Is_Packet( "Rama Merello" );
			tosend->print_packet();
			if (tosend->send_packet(cxn->get_cxn_socket()) == APR_SUCCESS )
				std::cout << "Able to send packet \n";
			else
				std::cout << "Unable to send packet \n";
		}
	}
	else
	{
		std::cout << "ABLE TO CONNECT TO SERVER YEAH BITCHES \n";
		std::cout << "Server press character to receive packet WAIT FOR SERVER TO SEND \n";
		getchar();
		TFTP_Packet torecieve;
		if (torecieve.recieve_pck(cxn->get_cxn_socket()))
		{
			std::cout << "Packet recieved correctly \n" ;
			torecieve.print_packet();
		}
		else 
			std::cout << "Packet not recieved correctly \n" ;
	}
	printf("END PROGRAM \n");
	while(1);
	return 0;
}
*/

#endif // HANABI_NETWORK_DEFINES_H 

