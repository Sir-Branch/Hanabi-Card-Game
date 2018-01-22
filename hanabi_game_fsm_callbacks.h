/* 
 * File:   hanabi_game_fsm_callbacks.h
 * Author: r2d2
 *
 * Created on January 10, 2018, 1:12 PM
 */

#ifndef HANABI_GAME_FSM_CALLBACKS_H
#define HANABI_GAME_FSM_CALLBACKS_H

#include "setting_management.h"


void do_nothing(hanabi_game_data_t*);
void send_name_pck(hanabi_game_data_t*);
void send_ack_pck(hanabi_game_data_t*);
void send_name_is_pck(hanabi_game_data_t *user_data);
void start_game_send_start_info_pck(hanabi_game_data_t *user_data);
void manage_receive_start_info(hanabi_game_data_t *user_data);
void create_send_random_start(hanabi_game_data_t *user_data);

void manage_play_send_ack(hanabi_game_data_t *user_data);
void manage_you_have_send_ack(hanabi_game_data_t *user_data);
void manage_discard_send_ack(hanabi_game_data_t *user_data);
void manage_name_is_ack(hanabi_game_data_t *user_data);

void send_you_have(hanabi_game_data_t *user_data);
void send_play_pck(hanabi_game_data_t *user_data);
void send_discard_pck(hanabi_game_data_t *user_data);
void send_error(hanabi_game_data_t *user_data);
void remove_card(hanabi_game_data_t *user_data);
void send_draw_card(hanabi_game_data_t *user_data);
#endif /* HANABI_GAME_FSM_CALLBACKS_H */

