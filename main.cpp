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
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro_start_shutdown.h"
#include "hanabi_events.h"
#include "hanabi_game_data.h"
#include "event_dispatcher.h" 
#include "event_handler_allegro.h"
#include "Eda_Menu_Network.h"

#define FPS				30.0
#define SCREEN_W		1152 
#define SCREEN_H		648
//16:9 1280×720 1024x576

#define MONO_FONT_PATH "DroidSansMono.ttf"
 
int main(void)
{

						
	hanabi_game_data_t hanabi_game_data;
	ALLEGRO_EVENT ev;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	
	std::queue<hanabi_game_event_t> button_event_queue, network_event_queue, software_event_queue;
 
	if(allegro_startup() == AL_STARTUP_ERROR) {
		fprintf(stderr, "failed to initialize allegro!\n");
		allegro_shut_down();
		return -1;
	}
	
		//ALLEGRO_MONITOR_INFO info;
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	//al_get_monitor_info(0, &info);
 
	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		allegro_shut_down();
		return -1;
	}

	hanabi_game_data.display = create_display(SCREEN_W, SCREEN_H);//SCREEN_W, SCREEN_H);
	if(!hanabi_game_data.display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		allegro_shut_down();
		return -1;
	}
	//al_resize_display(hanabi_game_data.display,disp_data.width * 0.99, disp_data.height  * 0.8);
 
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(hanabi_game_data.display);
		al_destroy_timer(timer);
		allegro_shut_down();
		return -1;
	}
	al_register_event_source(event_queue, al_get_display_event_source(hanabi_game_data.display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	
	hanabi_game_data.game_configuration.memory_help = false;
	hanabi_game_data.game_configuration.full_screen = false;
	hanabi_game_data.game_configuration.sound_mute = false;
	hanabi_game_data.game_configuration.selected_resolution = 1;
	hanabi_game_data.game_configuration.selected_theme = 0;
	hanabi_game_data.theme_settings = new Hanabi_Skin();
	hanabi_game_data.theme_settings->load_theme("Classic");
	hanabi_game_data.game_board = new Hanabi_Board();


	hanabi_game_data.game_board->lose_live();
	hanabi_game_data.game_board->remove_clue_token();
	hanabi_game_data.game_board->otherplayers_hand[0] = Hanabi_Card(HANABI_CARD_WHITE, HANABI_CARD_TWO); 
	hanabi_game_data.game_board->otherplayers_hand[1] = Hanabi_Card(HANABI_CARD_BLUE, HANABI_CARD_ONE); 
	hanabi_game_data.game_board->otherplayers_hand[2] = Hanabi_Card(HANABI_CARD_GREEN, HANABI_CARD_ONE); 
	hanabi_game_data.game_board->otherplayers_hand[3] = Hanabi_Card(HANABI_CARD_YELLOW, HANABI_CARD_ONE); 
	hanabi_game_data.game_board->otherplayers_hand[4] = Hanabi_Card(HANABI_CARD_RED, HANABI_CARD_ONE); 
	hanabi_game_data.game_board->otherplayers_hand[5] = Hanabi_Card(HANABI_CARD_WHITE, HANABI_CARD_TWO); 

	hanabi_game_data.game_board->draw_card(0);
	hanabi_game_data.game_board->draw_card(1);
	hanabi_game_data.game_board->draw_card(2);
	hanabi_game_data.game_board->draw_card(3);
	hanabi_game_data.game_board->draw_card(4);
	hanabi_game_data.game_board->draw_card(5);
	
	hanabi_game_data.do_exit = false;
	hanabi_game_data.redraw = false;

	//hanabi_game_data.active_menu = new Eda_Menu_Main(hanabi_game_data.theme_settings->theme);
	hanabi_game_data.active_menu = new Eda_Menu_Network(hanabi_game_data.display, MONO_FONT_PATH );
	hanabi_game_data.active_menu->draw(hanabi_game_data.display,hanabi_game_data.theme_settings, hanabi_game_data.game_board);
	al_start_timer(timer);

	
	while(!hanabi_game_data.do_exit)  // idem anterior
	{
		
		if( al_get_next_event(event_queue, &ev) )
			event_handle_allegro(ev, &hanabi_game_data, &button_event_queue);
		
		if(!button_event_queue.empty())
		{
			dispatch_event(button_event_queue.front(), &hanabi_game_data);
			button_event_queue.pop();
		}
		
		if(hanabi_game_data.redraw && al_is_event_queue_empty(event_queue) && button_event_queue.empty() ) 
		{
			hanabi_game_data.redraw = false;
			hanabi_game_data.active_menu->draw(hanabi_game_data.display,hanabi_game_data.theme_settings, hanabi_game_data.game_board);
		}

	}

	al_destroy_timer(timer);
	al_destroy_display(hanabi_game_data.display);
	al_destroy_event_queue(event_queue);
	allegro_shut_down();

	return 0;
}

#else

#include <cstdlib>
#include <iostream>
#include "TFTPServer.h"
#include "TFTPClient.h"
#include "TFTP_Packet.h"
#include "Hanabi_Name_Is_Packet.h"
#include "Client.h"
using namespace std;

int main(int argc, char** argv) {
	apr_initialize();

	Net_connection * cxn = new Client();
	std::cout << "Will search for server for 5 seconds \n";
	if(!((Client *)cxn)->connect_to_server(HOME_ADRESS,DEF_REMOTE_PORT,1000) )
	{
		delete cxn;
		cxn = new Server(DEF_REMOTE_PORT);
		std::cout << "Server will now try listening for client for 500secs \n";
		while (!((Server*)cxn)->listen_for_connection(500* 1000) )
		{
			getchar();
		}
	}
	else
	{
		std::cout << "ABLE TO CONNECT TO SERVER YEAH BITCHES \n";
		std::cout << "Server press character to receive packet WAIT FOR SERVER TO SEND \n";
		getchar();
	}
	printf("END PROGRAM \n");
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
			getchar();
			TFTP_Packet * tosend = new Hanabi_Name_Is_Packet( "Rama Merello" );
			tosend->print_packet();
			if (cxn->send_packet(tosend) == APR_SUCCESS )
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
		TFTP_Packet * toreceive;
		if(cxn->receive_packet(&toreceive))
		{
			std::cout << "Packet receive correctly \n" ;
			toreceive->print_packet();
		}
		else 
			std::cout << "Packet not receive correctly \n" ;
	}
	printf("END PROGRAM \n");
	while(1);
	return 0;
}

#endif