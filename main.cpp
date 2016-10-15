/* 
 * File:   main.cpp
 * Author: r2d2
 *
 * Created on October 12, 2016, 8:29 PM
 */

#include <cstdlib>
#include <iostream>
#include "Hanabi_Board.h"


using namespace std;


int main(int argc, char** argv) {
			
	
	
	
	Hanabi_Board game_board;

	game_board.hanabi_game_deck.print_deck();
	for(int i = 0 ; i < 6 ; i++)
		game_board.draw_card(i);
	game_board.hanabi_game_deck.print_deck();
	
	game_board.print_my_hand();
	
	std::cout << "Any clues left: " << game_board.any_clues_left() << std::endl;
	std::cout << "Any lifes left: " << game_board.any_lifes_left() << std::endl;
	
	game_board.flip_clue_tokens(true);
	game_board.flip_clue_tokens(true);
	game_board.flip_clue_tokens(true);
	
	std::cout << "All clues left: " << game_board.all_clues_left() << std::endl;
	
	game_board.lose_life();
	game_board.lose_life();
	game_board.lose_life();
	
	std::cout << "Any lifes left: " << game_board.any_lifes_left() << std::endl;

	
	for(int i = 0 ; i < 6 ; i++)
	{
		std::cout << "Can place card #" << i <<": " << game_board.can_place_card( i ) << std::endl;
		if(game_board.can_place_card(i))
		{
			game_board.player_action_play_card(i);
			std::cout<< "Card Placed NIGGAAAA \n";
			game_board.print_my_hand();
		}
	}
	
	game_board.print_my_hand();
	game_board.player_action_discard_card(0);
	std::cout << "All clues left: " << game_board.all_clues_left() << std::endl;
	

	game_board.print_my_hand();
	game_board.player_action_discard_card(0);
	std::cout << "All clues left: " << game_board.all_clues_left() << std::endl;
	
	
	game_board.print_my_hand();
	game_board.player_action_discard_card(0);
	std::cout << "All clues left: " << game_board.all_clues_left() << std::endl;
	game_board.print_my_hand();
	
	for(int i = 0 ; i < 5 ; i ++)
	{
		std::cout << "Printing graveyard for #" << i << std::endl;
		game_board.grave_yard[i].print_deck();
		
	}
	

	game_board.receive_action_get_clue('B');
	game_board.receive_action_get_clue(1);
	game_board.receive_action_get_clue('Y');
	game_board.receive_action_get_clue(2);
	game_board.receive_action_get_clue('G');
	game_board.receive_action_get_clue(3);
	game_board.receive_action_get_clue('W');
	game_board.receive_action_get_clue(4);
	game_board.receive_action_get_clue('R');
	game_board.receive_action_get_clue(5);
	
	return 0;
}


#if 0

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



void create_packet_test_array(TFTP_Packet *tosend[17]);

int main(int argc, char** argv) {

	apr_initialize();

	TFTPCxn * cxn = new TFTPClient();
	std::cout << "Will search for server for 5 seconds \n";
	if(!((TFTPClient *)cxn)->try_connect_server(5.0,HOME_ADRESS, DEF_REMOTE_PORT, DEF_IPMODE ))
	{
		delete cxn;
		cxn = new TFTPServer(NULL, DEF_REMOTE_PORT, DEF_IPMODE );
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
#endif


/*
 * OUTPUT:
 * Printing my hand 
B1
R3
Y3
B2
B3
G4
Any clues left: 1
Any lifes left: 1
All clues left: 0
Any lifes left: 1
Any lifes left: 1
Any lifes left: 0
Can place card #0: 1
Card Placed NIGGAAAA 

Printing my hand 
R3
R3
Y3
B2
B3
G4
Can place card #1: 0
Can place card #2: 0
Can place card #3: 1
Card Placed NIGGAAAA 

Printing my hand 
R3
R3
Y3
R1
B3
G4
Can place card #4: 1
Card Placed NIGGAAAA 

Printing my hand 
R3
R3
Y3
R1
R2
G4
Can place card #5: 0

 * 
 */