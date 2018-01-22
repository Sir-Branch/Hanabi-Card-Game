/* 
 * File:   event_handler_button_clicks.h
 * Author: r2d2
 *
 * Created on February 12, 2017, 7:37 AM
 */

#ifndef EVENT_HANDLER_BUTTON_CLICKS_H
#define EVENT_HANDLER_BUTTON_CLICKS_H

#include "hanabi_events.h"
#include "setting_management.h"
#include "hanabi_game_fsm.h"

void event_handle_button(event_button_t button_event, hanabi_game_data_t * hanabi_game_data,std::queue<hanabi_fsm_events_t> *software_event_queue);


#endif /* EVENT_HANDLER_BUTTON_CLICKS_H */

