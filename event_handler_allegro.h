/* 
 * File:   event_handler_allegro.h
 * Author: r2d2
 *
 * Created on February 12, 2017, 9:57 AM
 */

#ifndef EVENT_HANDLER_ALLEGRO_H
#define EVENT_HANDLER_ALLEGRO_H

#include <queue>
#include <allegro5/allegro5.h>
#include "setting_management.h"

void event_handle_allegro(ALLEGRO_EVENT ev, hanabi_game_data_t * hanabi_game_data, std::queue<hanabi_game_event_t> *button_event_queue);


#endif /* EVENT_HANDLER_ALLEGRO_H */

