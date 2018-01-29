/* 
 * File:   setting_management.h
 * Author: r2d2
 *
 * Created on January 8, 2018, 8:38 PM
 */

#ifndef SETTING_MANAGEMENT_H
#define SETTING_MANAGEMENT_H

#include "Hanabi_Skin.h"
#include "Hanabi_Board.h"
#include "Eda_Menu.h"
#include "TFTPCxn.h"
#include "Networking.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string>

#define HANABI_NUMBER_RESOLUTIONS	7	//1024×576, 1152×648, 1280×720, 1366×768, 1600×900, 1920×1080
#define HANABI_NUMBER_THEMES		2
#define MONO_FONT_PATH "Fonts/DroidSansMono.ttf"
#define COMMON_FILE_PATH "Common Images Files"
#define FONT_PATH "Fonts"
#define NUM_SAMPLES 4
#define NO_CARD_SELECTED	0xFF

typedef enum events_type
{
    PLAY_CLICKED = 1,SETTINGS_CLICK,
	JOIN_CLICKED, HOST_CLICKED,
	APPLY_CLICKED, CANCEL_CLICKED, //6
		
	TIMEOUT,FOUND_SERVER,CLIENT_CONNECTED,//9
	SERVER_NOT_FOUND, CLIENT_NOT_CONNECTED,//11
		
    START_INFO_OK, START_INFO_ERRORS,  ACTION_YOU_HAVE, ACTION_PLAY, ACTION_DISCARD,
    RECEIVE_ACK, RECEIVE_ERROR,
    RECEIVE_START_INFO, RECEIVE_NAME_IS, //20
	RECEIVE_NAME, RECEIVE_USTART, RECEIVE_ISTART, RECEIVE_YOU_START, RECEIVE_I_START,
    RECEIVE_PLAY, RECEIVE_YOU_HAVE, RECEIVE_DISCARD, RECEIVE_DRAW,
		
	RECEIVE_DRAW_LAST, LAST_DRAW_SENT,
	RECEIVE_MATCH_IS_OVER, RECEIVE_WE_WON, RECEIVE_WE_LOST, 
	RECEIVE_GAME_OVER, RECEIVE_PLAY_AGAIN,
		
	GAME_OVER,
	
	TABLE_END
	
}hanabi_fsm_events_t;

typedef struct
{
	unsigned int selected_resolution;
	unsigned int selected_theme;
	bool memory_help;
	bool sound_mute;
	bool full_screen;
	//bool music;

}game_configuration_t;

typedef struct
{
	bool do_exit, redraw;
	bool connected, check_connection;

    TFTP_Packet * last_received_pck;
	Networking * net_connection;

	ALLEGRO_DISPLAY * display;
	ALLEGRO_SAMPLE *main_music;
	ALLEGRO_TIMER * fps_timer = NULL, * network_timer = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue;
	
	bool other_players_turn;
	game_configuration_t game_configuration;
	Hanabi_Board * game_board;
	Hanabi_Skin * theme_settings;
	Eda_Menu * active_menu;
	
	std::string player_name,other_player_name;	
	std::string join_ip;
	
	std::queue<std::string> message_event_queue;
	std::queue<hanabi_game_event_t> button_event_queue;
	std::queue<hanabi_fsm_events_t> software_event_queue;
	
}hanabi_game_data_t;

void load_configuration(hanabi_game_data_t * hanabi_game_data);
void save_configuration(hanabi_game_data_t * hanabi_game_data);
void get_static_themes_resolutions(const char *** available_themes ,  const char *** available_resolutions);
const char * get_resolution(unsigned int num_resol);
const char * get_theme(unsigned int num_theme);
unsigned int calculate_font_size (ALLEGRO_DISPLAY *display, float x_size_percent , float y_size_percent,char * path, unsigned int max_size);
ALLEGRO_SAMPLE *play_main_music();
void stop_main_music(ALLEGRO_SAMPLE *sample);
#endif /* SETTING_MANAGEMENT_H */

