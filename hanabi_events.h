/* 
 * File:   events.h
 * Author: r2d2
 *
 * Created on February 12, 2017, 6:11 AM
 */

#ifndef EVENTS_H
#define EVENTS_H

typedef enum{
	NO_EVENT = 0, EDA_BUTTON_PLAY_PRESSED, EDA_BUTTON_SETT_PRESSED,EDA_BUTTON_QUIT_PRESSED, //Main_Menu
	
	// ********************* Game Menu ************************************
	EDA_BUTTON_WHITE_PRESSED, EDA_BUTTON_BLUE_PRESSED, EDA_BUTTON_GREEN_PRESSED,
	EDA_BUTTON_YELLOW_PRESSED, EDA_BUTTON_RED_PRESSED,
	
	EDA_BUTTON_ONE_PRESSED, EDA_BUTTON_TWO_PRESSED, EDA_BUTTON_THREE_PRESSED,
	EDA_BUTTON_FOUR_PRESSED, EDA_BUTTON_FIVE_PRESSED,
	
	EDA_BUTTON_GIVE_CARD_ONE, EDA_BUTTON_GIVE_CARD_TWO, EDA_BUTTON_GIVE_CARD_THREE, 
	EDA_BUTTON_GIVE_CARD_FOUR, EDA_BUTTON_GIVE_CARD_FIVE, EDA_BUTTON_GIVE_CARD_SIX,
	
	EDA_BUTTON_GIVE_CLUE_PRESSED, EDA_BUTTON_PLAY_CARD_PRESSED , EDA_BUTTON_DISCARD_CARD_PRESSED,
	// ********************* Settings Menu ************************************
			
	EDA_BUTTON_APPLY_PRESSED, EDA_BUTTON_CANCEL_PRESSED, //Settings
	EDA_BUTTON_JOIN_PRESSED, EDA_BUTTON_HOST_PRESSED, //Settings

		
	//********************** CONNECTION MENU************************************
		
		EDA_BUTTON_CONNECT_PRESSED 

}event_button_t;


typedef enum{
	
	EDA_EVENT_DESELECT_ALL_BUTTONS, 
	EDA_EVENT_INVALID_GIVE_CLUE,EDA_EVENT_VALID_GIVE_CLUE,
	EDA_EVENT_BAD_PLAY_CARD, EDA_EVENT_DISCARD_CARD,
	
	EDA_EVENT_GAME_QUIT
		
}event_software_t;

typedef enum{
	
}event_network_t;

typedef enum{ HANABI_EVENT_BUTTON, HANABI_EVENT_NETWORK, HANABI_EVENT_SOFTWARE}event_type_t;

typedef struct
{
	union
	{
		event_button_t button_event;
		event_network_t	network_event;
		event_software_t software_event;
	};
	event_type_t type;	
	
}hanabi_game_event_t;

#endif /* EVENTS_H */

