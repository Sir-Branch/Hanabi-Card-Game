/* 
 * File:   main.cpp
 * Author: r2d2
 *
 * Created on October 12, 2016, 8:29 PM
 */

#define NETWORK_TEST 0



#if !NETWORK_TEST 

#include <cstdlib>
#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <queue>
#include "Hanabi_Board.h"
#include "Hanabi_Skin.h"
#include "Eda_Menu_Main.h"
#include "Eda_Menu_Game.h"
#include "Eda_Menu_Settings.h"
#include "Eda_Button.h"
#include "Eda_Menu.h"
#include "Eda_Menu_Gameover.h"
#include "hanabi_events.h"
#include "setting_management.h"
#include "hanabi_events.h"
#include "setting_management.h"
#include "event_dispatcher.h" 
#include "event_handler_allegro.h"
#include "event_dispatcher.h" 
#include "event_handler_allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro_start_shutdown.h"
#include "hanabi_events.h"
#include "setting_management.h"
#include "event_dispatcher.h" 
#include "event_handler_allegro.h"
#include "Eda_Menu_Network.h"
#include "setting_management.h"
#include "hanabi_game_fsm.h"
#include "event_generator.h"

#define FPS				30.0
#define NETWORK_TIMER_RATE	0.001
//#define SCREEN_W		1152 
//#define SCREEN_H		648
//16:9 1280×720 1024x576

static unsigned int game_startup(hanabi_game_data_t & hanabi_game_data);
static void game_shutdown(hanabi_game_data_t &hanabi_game_data);

int main(void)
{		
	hanabi_game_data_t hanabi_game_data;
	ALLEGRO_EVENT ev;


	TFTP_Packet * temp_pck = NULL;
	STATE * current_state = get_starting_state();

	game_startup(hanabi_game_data);//Starts APR, ALLEGRO, loads configuration
	
	while(!hanabi_game_data.do_exit)  // idem anterior
	{
		if( al_get_next_event(hanabi_game_data.event_queue, &ev) )
			event_handle_allegro(ev, &hanabi_game_data, &hanabi_game_data.button_event_queue);
			
		if(!hanabi_game_data.button_event_queue.empty())
		{
			dispatch_event(hanabi_game_data.button_event_queue.front(), &hanabi_game_data,&hanabi_game_data.software_event_queue );
			hanabi_game_data.button_event_queue.pop();
		}
		
		if(!hanabi_game_data.software_event_queue.empty())
		{
			std::cout << "Software event received" << hanabi_game_data.software_event_queue.front() << std::endl;
			std::cout << "State before" << current_state << std::endl;
			current_state = manage_fsm(current_state, hanabi_game_data.software_event_queue.front(), &hanabi_game_data);
			hanabi_game_data.software_event_queue.pop();
			std::cout << "State after" << current_state << std::endl;
		}
		
		if(!hanabi_game_data.message_event_queue.empty())
		{
			((Eda_Menu_Game *)hanabi_game_data.active_menu)->add_message(hanabi_game_data.message_event_queue.front());
			hanabi_game_data.message_event_queue.pop();
		}
		if(hanabi_game_data.redraw && al_is_event_queue_empty(hanabi_game_data.event_queue)
			&& hanabi_game_data.button_event_queue.empty() && hanabi_game_data.software_event_queue.empty() ) 
		{
			hanabi_game_data.redraw = false;
			hanabi_game_data.active_menu->draw(hanabi_game_data.display, hanabi_game_data.theme_settings, hanabi_game_data.game_board,hanabi_game_data.game_configuration.memory_help);
			//std::cout<<"hola   "<<hanabi_game_data.game_configuration.memory_help<<std::endl<<((Eda_Menu_Settings*)hanabi_game_data.active_menu)->get_enable_full_screen();
			
		}
		
		if(hanabi_game_data.connected && hanabi_game_data.check_connection)// && software_event_queue.empty())
		{
			hanabi_game_data.check_connection = false;
			if( hanabi_game_data.net_connection->receive_packet(&temp_pck) )
			{
				hanabi_game_data.last_received_pck = temp_pck;
				hanabi_game_data.software_event_queue.push(event_generator(temp_pck));
				std::cout<<"Packet received ";
				temp_pck->print_packet();
			}
		}
		
	}
	game_shutdown(hanabi_game_data);
	return 0;
}

unsigned int game_startup(hanabi_game_data_t &hanabi_game_data)
{
	unsigned int height, width; //Variables used for screen height and width
	load_configuration(&hanabi_game_data);
	//stopMusic(hanabi_game_data.main_music); //Stops background music. 
	srand(time(NULL)); 

	sscanf(get_resolution(hanabi_game_data.game_configuration.selected_resolution), "%dx%d",&width, &height);
	apr_initialize();
	if(allegro_startup() == AL_STARTUP_ERROR) {
		fprintf(stderr, "failed to initialize allegro!\n");
		allegro_shut_down();
		return -1;
	}
 
	hanabi_game_data.fps_timer = al_create_timer(1.0 / FPS);
	if(!hanabi_game_data.fps_timer) {
		fprintf(stderr, "failed to create fps_timer!\n");
		allegro_shut_down();
		return -1;
	}
	hanabi_game_data.network_timer = al_create_timer(NETWORK_TIMER_RATE);
	if(!hanabi_game_data.network_timer) {
		fprintf(stderr, "failed to create network timer!\n");
		al_destroy_timer(hanabi_game_data.fps_timer);
		al_destroy_timer(hanabi_game_data.network_timer);
		allegro_shut_down();
		return -1;
	}

	if(hanabi_game_data.game_configuration.full_screen) //Set of fullscreen window mode
		al_set_new_display_flags( ALLEGRO_FULLSCREEN_WINDOW);
	
	
	hanabi_game_data.display = create_display(width, height);//Creation of allegro display
	if(!hanabi_game_data.display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(hanabi_game_data.fps_timer);
		al_destroy_timer(hanabi_game_data.network_timer);
		allegro_shut_down();
		return -1;
	}
 
	hanabi_game_data.event_queue = al_create_event_queue(); //Creation of allegro event queue, if an error is found, the display, timer and allegro are destroy and the program is terminated
	if(!hanabi_game_data.event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(hanabi_game_data.display);
		al_destroy_timer(hanabi_game_data.fps_timer);
		al_destroy_timer(hanabi_game_data.network_timer);
		allegro_shut_down();
		return -1;
	}
        
        //Registration of display, timer, mouse and keyboard
	al_register_event_source(hanabi_game_data.event_queue, al_get_display_event_source(hanabi_game_data.display));
	al_register_event_source(hanabi_game_data.event_queue, al_get_timer_event_source(hanabi_game_data.fps_timer));
	al_register_event_source(hanabi_game_data.event_queue, al_get_timer_event_source(hanabi_game_data.network_timer));
	al_register_event_source(hanabi_game_data.event_queue, al_get_mouse_event_source());
	al_register_event_source(hanabi_game_data.event_queue, al_get_keyboard_event_source());
	
	hanabi_game_data.theme_settings = new Hanabi_Skin();
	hanabi_game_data.theme_settings->load_theme(get_theme(hanabi_game_data.game_configuration.selected_theme));
	
	hanabi_game_data.game_board = new Hanabi_Board();
	hanabi_game_data.do_exit = false;
	hanabi_game_data.redraw = false;
	hanabi_game_data.connected = false;
	
	hanabi_game_data.active_menu = new Eda_Menu_Main(hanabi_game_data.theme_settings->theme);
	hanabi_game_data.active_menu->draw(hanabi_game_data.display, hanabi_game_data.theme_settings, hanabi_game_data.game_board,hanabi_game_data.game_configuration.memory_help);
	al_start_timer(hanabi_game_data.fps_timer);
	al_start_timer(hanabi_game_data.network_timer);
	
}
void game_shutdown(hanabi_game_data_t &hanabi_game_data)
{
	save_configuration(&hanabi_game_data);
	al_destroy_timer(hanabi_game_data.fps_timer);
	al_destroy_timer(hanabi_game_data.network_timer);
	al_destroy_display(hanabi_game_data.display);
	al_destroy_event_queue(hanabi_game_data.event_queue);
	allegro_shut_down();
}



#else 



#include <cstdlib>
#include <iostream>
#include "TFTPServer.h"
#include "my_sleep_ms.h"
#include "Networking.h"
#include "TFTPClient.h"
#include "TFTP_Packet.h"
#include "Hanabi_Name_Is_Packet.h"
#include <unistd.h>
using namespace std;

int main(int argc, char** argv) {
	bool connected = false;
	apr_initialize();
	srand(time(NULL));
	Networking network;
	string ip = "192.168.0.23";
	
	
	char buffer[1000] = {0};
	char inputed_char;
	unsigned int length;
	TFTP_Packet * tosend, * toreceive;
	switch( inputed_char = getchar())
	{
		case 'c':
			getchar();
			network.try_connect_server(2.0, ip);
			tosend = new Hanabi_Name_Is_Packet( "I'm Client" );
			//client
			std::cout << "I'm Client" <<std::endl;
			getchar();
			network.send_packet(tosend);
			getchar();
			network.receive_packet(&toreceive);
			getchar();
			break;
			
		case 's':
						getchar();
			tosend = new Hanabi_Name_Is_Packet( "I'm Server" );
			std::cout << "I'm Server" <<std::endl;
			//network.abortConnecting();
			//network.prepareToListen();
			//server
			if(network.listen_for_client(100))
			{
				getchar();
				network.receive_packet(&toreceive);
				getchar();
				network.send_packet(tosend);
				getchar();
			}
			break;
	}
	
	

	while(1);
	return 0;
}








#endif 
#if 0

#include <cstdlib>
#include <iostream>
#include "TFTPServer.h"
#include "TFTPClient.h"
#include "TFTP_Packet.h"
#include "Hanabi_Name_Is_Packet.h"
#include <unistd.h>
using namespace std;

int main(int argc, char** argv) {
	apr_initialize();

	TFTPCxn * cxn = new TFTPClient();
	std::cout << "Will search for server for 5 seconds \n";
	if(!((TFTPClient *)cxn)->try_connect_server(1.0,HOME_ADRESS, DEF_REMOTE_PORT, DEF_IPMODE ) )
	{
		delete cxn;
		cxn = new TFTPServer(DEF_REMOTE_PORT, DEF_IPMODE );
		std::cout << "Server will now try listening for client for 500secs \n";
		if (((TFTPServer*)cxn)->listen_for_client(500.0) )
		{
			std::cout << "Able to connect to client \n";
			std::cout << "Server press character to send name packet \n";
			while( getchar() != 'q')
			{
				TFTP_Packet * toreceive;// = new Hanabi_Name_Is_Packet( "" );
				if(cxn->receive_packet(&toreceive))
				{
					std::cout << "Packet receive correctly \n" ;
					toreceive->print_packet();
				}
				
				TFTP_Packet * tosend = new Hanabi_Name_Is_Packet( "" );
				tosend->print_packet();
				if (cxn->send_packet(tosend) )
					std::cout << "Able to send packet \n";
				else
					std::cout << "Unable to send packet \n";
			}
		}
	}
	else
	{
		std::cout << "ABLE TO CONNECT TO SERVER YEAH BITCHES \n";
		//std::cout << "Server press character to receive packet WAIT FOR SERVER TO SEND \n";
//		TFTP_Packet * tosend = new Hanabi_Name_Is_Packet( "Sent by Client" );
//		tosend->print_packet();
//				if (cxn->send_packet(tosend) )
//					std::cout << "Able to send packet \n";
//				else
//					std::cout << "Unable to send packet \n";

		while( 1 )
		{
			usleep(1000);
			TFTP_Packet * toreceive;
			if(cxn->receive_packet(&toreceive))
			{
				std::cout << "Packet receive correctly \n" ;
				toreceive->print_packet();
			}
			//else 
			//	std::cout << "No Packet to receive\n" ;
		}
	}
	printf("END PROGRAM \n");
	while(1);
	return 0;
}

#endif
