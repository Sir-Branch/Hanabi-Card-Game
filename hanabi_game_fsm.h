/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hanabi_game_fsm.h
 * Author: parallels
 *
 * Created on January 9, 2018, 5:27 AM
 */

#ifndef HANABI_GAME_FSM_H
#define HANABI_GAME_FSM_H

#include "setting_management.h"

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
		
	TABLE_END
	
}hanabi_fsm_events_t;

typedef void (*action_t) (hanabi_game_data_t *user_data); 

typedef struct state_table
{
	hanabi_fsm_events_t  event;
	struct state_table *next_state;
	action_t action;
	
}STATE;

STATE * manage_fsm(STATE * current_state_table,hanabi_fsm_events_t received_event,hanabi_game_data_t *user_data);
STATE * get_starting_state(void);


#endif /* HANABI_GAME_FSM_H */

