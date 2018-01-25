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

