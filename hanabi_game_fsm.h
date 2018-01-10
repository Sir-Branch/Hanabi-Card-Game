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


typedef enum events_type
{
    PLAY_CLICKED,SETTINGS_CLICK,TIMEOUT,FIND_SERVER,CLIENT_CONNECTED,
    START_INFO_OK, START_INFO_ERRORS,  ACTION_YOU_HAVE, ACTION_PLAY, ACTION_DISCARD,
    RECEIVE_ACK, RECEIVE_ERROR,
    RECEIVE_START_INFO, RECEIVE_NAME_IS, RECEIVE_NAME, RECEIVE_USTART, RECEIVE_ISTART, RECEIVE_YOU_START, RECEIVE_I_START,
    RECEIVE_PLAY, RECEIVE_YOU_HAVE, RECEIVE_DISCARD, RECEIVE_DRAW
}events_type_t;


#endif /* HANABI_GAME_FSM_H */

