/* 
 * File:   hanabi_game_fsm_callbacks.h
 * Author: r2d2
 *
 * Created on January 10, 2018, 1:12 PM
 */

#ifndef HANABI_GAME_FSM_CALLBACKS_H
#define HANABI_GAME_FSM_CALLBACKS_H

#include "setting_management.h"


void do_nothing (hanabi_game_data_t*);
void send_name_pck (hanabi_game_data_t*);
void send_ack_pck (hanabi_game_data_t*);

#endif /* HANABI_GAME_FSM_CALLBACKS_H */

