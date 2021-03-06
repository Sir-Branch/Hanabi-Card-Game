/* 
 * File:   event_dispacher.cpp
 * Author: r2d2
 *
 * Created on February 12, 2017, 6:10 AM
 */
#include "hanabi_events.h"
#include "setting_management.h"
#include "event_handler_button_clicks.h"
#include "event_handler_network.h"
#include "event_handler_software.h"

void dispatch_event(hanabi_game_event_t event, hanabi_game_data_t * hanabi_game_data,std::queue<hanabi_fsm_events_t> *software_event_queue)
{
	if( event.type == HANABI_EVENT_BUTTON)
	{
		event_handle_button(event.button_event, hanabi_game_data,software_event_queue );
	}
	else if( event.type == HANABI_EVENT_NETWORK)
	{
		event_handle_network(event.network_event, hanabi_game_data);
	}
	else if( event.type == HANABI_EVENT_SOFTWARE)
	{
		event_handle_software(event.software_event, hanabi_game_data);
	}
}