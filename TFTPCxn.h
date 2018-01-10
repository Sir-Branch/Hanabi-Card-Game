/* 
 * File:   TFTPCxn.h
 * Author: r2d2
 *
 * Created on May 30, 2016, 1:11 AM
 */

#ifndef TFTPCXN_H
#define TFTPCXN_H

#include <apr-1.0/apr_general.h>
#include <apr-1.0/apr_network_io.h>
#include <apr-1.0/apr_strings.h>
#include <apr-1.0/apr_file_io.h>
#include "TFTP_Packet.h"

#define DEF_REMOTE_PORT		13796					// default connect port number 13796
#define DEF_SOCK_TIMEOUT	(APR_USEC_PER_SEC * 5)	//TIMEOUT DE TODAS LAS OPERACIONES (ENVIAR, RECIBIR, CONECTAR) EN SEGUNDOS
#define HOME_ADRESS			"192.168.43.187"					//aca escribimos el ip de esta pc, es decir, del host.
#define DEF_SOCKET_BACKLOG	SOMAXCONN				// cantidad maxima que el sistema operativo pone para aceptar.
#define DEF_IPMODE			AF_INET

class TFTPCxn
{
	
public:
	TFTPCxn();
	virtual ~TFTPCxn();
	//apr_socket_t * get_cxn_socket(); //Shouldn't be necessary ....
	bool send_packet(TFTP_Packet * pck_to_send);
	bool receive_packet(TFTP_Packet ** pck_to_recieve);
	bool connection_status_ok(void);
        apr_socket_t* get_cxn_socket (void);
	
    //apr_status_t get_connection_status();
        
protected:
	apr_socket_t * socket;
	apr_pool_t * mem_pool;
    apr_status_t cxn_status;
};


#endif /* TFTPCXN_H */


//Just a connection test
/*
int main(int argc, char** argv) {

	apr_initialize();

	TFTPCxn * cxn = new TFTPClient();
	if(!((TFTPClient *)cxn)->try_connect_server(5.0,HOME_ADRESS, DEF_REMOTE_PORT, DEF_IPMODE ))
	{
		delete cxn;
		cxn = new TFTPServer();
		std::cout << "Server will now try listening for client for 600secs \n";
		if (((TFTPServer*)cxn)->listen_for_client(600.0) )
			std::cout << "Able to connect to client \n";
	}
	else
		std::cout << "ABLE TO CONNECT TO SERVER YEAH BITCHES \n";
	
	
	printf("END PROGRAM \n");
	while(1);
	return 0;
}
*/


//Great test with packet sending

/*
#include "Hanabi_Name_Is_Packet.h"

#include <cstdlib>
#include <iostream>
#include "TFTPServer.h"
#include "TFTPClient.h"
#include "TFTP_Packet.h"

#include "Hanabi_Name_Is_Packet.h"
#include "Hanabi_Ack_Packet.h"
#include "Hanabi_Discard_Packet.h"
#include "Hanabi_Draw_Packet.h"
#include "Hanabi_Error_Packet.h"
#include "Hanabi_Game_Over_Packet.h"
#include "Hanabi_IStart_Packet.h"
#include "Hanabi_Match_Over_Packet.h"
#include "Hanabi_Name_Is_Packet.h"
#include "Hanabi_Name_Packet.h"
#include "Hanabi_Play_Again_Packet.h"
#include "Hanabi_Play_Packet.h"
#include "Hanabi_Quit_Packet.h"
#include "Hanabi_Start_Info_Packet.h"
#include "Hanabi_We_Lost_Packet.h"
#include "Hanabi_We_Won_Packet.h"
#include "Hanabi_You_Have_Packet.h"
#include "Hanabi_You_Start_Packet.h"

using namespace std;


void create_packet_test_array(TFTP_Packet *tosend[17]);

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
			TFTP_Packet *tosend[17];
			create_packet_test_array(tosend);
			
			for(int i=0 ; i < 17 ; i++)
			{	
				getchar();
				tosend[i]->print_packet();
				if (tosend[i]->send_packet(cxn->get_cxn_socket()) == APR_SUCCESS )
					std::cout << "Able to send packet \n";
				else
					std::cout << "Unable to send packet \n";
		
			}
		}
			
	}
	else
	{
		std::cout << "ABLE TO CONNECT TO SERVER YEAH BITCHES \n";
		std::cout << "Server press character to receive packet WAIT FOR SERVER TO SEND \n";
		TFTP_Packet torecieve;

		for(int i=0 ; i < 17 ; i++)
		{	
			getchar();
			if (torecieve.recieve_pck(cxn->get_cxn_socket()))
			{
				std::cout << "Packet recieved correctly \n" ;
				torecieve.print_packet();
			}
			else 
				std::cout << "Packet not recieved correctly \n" ;
		}
			
	}
	
	printf("END PROGRAM \n");
	while(1);
	return 0;
}


#include "Hanabi_Card.h"
void create_packet_test_array(TFTP_Packet *tosend[17])
{
	tosend[0] = new Hanabi_Ack_Packet() ;
	tosend[1] = new Hanabi_Name_Packet() ;
	tosend[2] = new Hanabi_Name_Is_Packet("Rama Merello");
	
	Hanabi_Card client_array[6] = {	Hanabi_Card(HANABI_CARD_WHITE,HANABI_CARD_ONE),
								Hanabi_Card(HANABI_CARD_WHITE,HANABI_CARD_TWO),
								Hanabi_Card(HANABI_CARD_WHITE,HANABI_CARD_THREE),
								Hanabi_Card(HANABI_CARD_WHITE,HANABI_CARD_FOUR),
								Hanabi_Card(HANABI_CARD_WHITE,HANABI_CARD_FIVE),
								Hanabi_Card(HANABI_CARD_BLUE,HANABI_CARD_ONE)
							};
	
	Hanabi_Card server_array[6] = {	Hanabi_Card(HANABI_CARD_BLUE,HANABI_CARD_TWO),
								Hanabi_Card(HANABI_CARD_BLUE,HANABI_CARD_THREE),
								Hanabi_Card(HANABI_CARD_BLUE,HANABI_CARD_FOUR),
								Hanabi_Card(HANABI_CARD_BLUE,HANABI_CARD_FIVE),
								Hanabi_Card(HANABI_CARD_GREEN,HANABI_CARD_ONE),
								Hanabi_Card(HANABI_CARD_GREEN,HANABI_CARD_TWO)
							};
	
	tosend[3] = new Hanabi_Start_Info_Packet(client_array,server_array);
	
	tosend[4] = new Hanabi_You_Start_Packet() ;
	tosend[5] = new Hanabi_IStart_Packet() ;
	
	tosend[6] = new Hanabi_Discard_Packet(0x01) ;
	tosend[7] = new Hanabi_Play_Packet(0x02) ;
	tosend[8] = new Hanabi_You_Have_Packet(HANABI_CARD_RED) ;
	tosend[9] = new Hanabi_Draw_Packet(Hanabi_Card(HANABI_CARD_RED,HANABI_CARD_THREE)) ;
	
	tosend[10] = new Hanabi_We_Won_Packet() ;
	tosend[11] = new Hanabi_We_Lost_Packet() ;
	tosend[12] = new Hanabi_Match_Over_Packet() ;
	tosend[13] = new Hanabi_Play_Again_Packet();
	tosend[14] = new Hanabi_Game_Over_Packet() ;
	tosend[15] = new Hanabi_Quit_Packet() ;
	tosend[16] = new Hanabi_Error_Packet() ;
	
}
 * 
 */