/* 
 * File:   main.cpp
 * Author: r2d2
 *
 * Created on October 12, 2016, 8:29 PM
 */

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



using namespace std;
#define FPS				60.0
#define SCREEN_W		1152 
#define SCREEN_H		648
//16:9 1280×720 1024x576
 
int main(void)
{
	hanabi_game_data_t hanabi_config;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
  
	std::queue<hanabi_game_event_t> button_event_queue;
	
	bool redraw = false;
	bool do_exit = false;
 
	if(allegro_startup() == AL_STARTUP_ERROR) {
		fprintf(stderr, "failed to initialize allegro!\n");
		allegro_shut_down();
		return -1;
	}
 
	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		allegro_shut_down();
		return -1;
	}
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);  

	hanabi_config.display = create_display(SCREEN_W, SCREEN_H);
	if(!hanabi_config.display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		allegro_shut_down();
		return -1;
	}
 
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(hanabi_config.display);
		al_destroy_timer(timer);
		allegro_shut_down();
		return -1;
	}
   
	hanabi_config.game_configuration.memory_help = false;
	hanabi_config.game_configuration.sound_mute = false;
	hanabi_config.game_configuration.selected_resolution = 1;
	hanabi_config.game_configuration.selected_theme = 0;
	hanabi_config.theme_settings = new Hanabi_Skin();
	hanabi_config.theme_settings->load_theme("Classic");
	hanabi_config.game_board = new Hanabi_Board();


	hanabi_config.game_board->lose_live();
	hanabi_config.game_board->remove_clue_token();
	hanabi_config.game_board->otherplayers_hand[0] = Hanabi_Card(HANABI_CARD_WHITE, HANABI_CARD_TWO); 
	hanabi_config.game_board->otherplayers_hand[1] = Hanabi_Card(HANABI_CARD_BLUE, HANABI_CARD_ONE); 
	hanabi_config.game_board->otherplayers_hand[2] = Hanabi_Card(HANABI_CARD_GREEN, HANABI_CARD_ONE); 
	hanabi_config.game_board->otherplayers_hand[3] = Hanabi_Card(HANABI_CARD_YELLOW, HANABI_CARD_ONE); 
	hanabi_config.game_board->otherplayers_hand[4] = Hanabi_Card(HANABI_CARD_RED, HANABI_CARD_ONE); 
	hanabi_config.game_board->otherplayers_hand[5] = Hanabi_Card(HANABI_CARD_WHITE, HANABI_CARD_TWO); 



	hanabi_config.active_menu = new Eda_Menu_Main(hanabi_config.theme_settings->theme);

	al_register_event_source(event_queue, al_get_display_event_source(hanabi_config.display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	hanabi_config.active_menu->draw(hanabi_config.display,hanabi_config.theme_settings, hanabi_config.game_board);
	al_start_timer(timer);

	while(!do_exit)  // idem anterior
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER) // por que tenemos un timer para redibujar?
			redraw = true;
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)//Si se cierra el display o click de mouse cerrar
			do_exit = true;
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) 
			hanabi_config.active_menu->update_buttons(hanabi_config.display,ev.mouse.x, ev.mouse.y);
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			hanabi_config.active_menu->check_for_click(hanabi_config.display,ev.mouse.x, ev.mouse.y,button_event_queue);

		if(redraw && al_is_event_queue_empty(event_queue)) 
		{
			redraw = false;
			hanabi_config.active_menu->draw(hanabi_config.display,hanabi_config.theme_settings, hanabi_config.game_board);
		}

		if(!button_event_queue.empty())
		{
			dispatch_event(button_event_queue.front(), &hanabi_config);
			button_event_queue.pop();
		}

	}

	al_destroy_timer(timer);
	al_destroy_display(hanabi_config.display);
	al_destroy_event_queue(event_queue);
	allegro_shut_down();

	return 0;
}
