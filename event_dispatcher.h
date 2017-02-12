/* 
 * File:   event_dispatcher.h
 * Author: r2d2
 *
 * Created on February 12, 2017, 7:46 AM
 */

#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include "hanabi_events.h"
#include "hanabi_game_data.h"

void dispatch_event(hanabi_game_event_t event, hanabi_game_data_t * hanabi_game_data);


#endif /* EVENT_DISPACHER_H */

