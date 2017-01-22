/* 
 * File:   main.cpp
 * Author: r2d2
 *
 * Created on October 12, 2016, 8:29 PM
 */

#include <cstdlib>
#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <queue>
#include "Hanabi_Board.h"
#include "Hanabi_Skin.h"
#include "Eda_Button.h"
#include "Eda_Menu_Main.h"
#include "Eda_Menu_Game.h"

using namespace std;


 
#define FPS				60.0
#define SCREEN_W		1024
#define SCREEN_H		576
 
int main(void)
{
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
  
   std::queue<event_button_t> button_event_queue;
	
   bool redraw = false;
   bool do_exit = false;
 
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   al_init_image_addon();
   
   if(!al_install_mouse()) {
      fprintf(stderr, "failed to initialize the mouse!\n");
      return -1;
   }
 
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
   al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);  
   
   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }
 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
   
   Hanabi_Skin * theme = new Hanabi_Skin();
   theme->load_theme("Classic");
   
   Eda_Menu * active_menu = new Eda_Menu_Main();
   
   al_register_event_source(event_queue, al_get_display_event_source(display));
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   al_register_event_source(event_queue, al_get_mouse_event_source());
 
   active_menu->draw(display,theme);
   al_start_timer(timer);
 
   while(!do_exit)  // idem anterior
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) // por que tenemos un timer para redibujar?
         redraw = true;
	  
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)//Si se cierra el display o click de mouse cerrar
         do_exit = true;
	  
      else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) 
		 active_menu->update_buttons(display,ev.mouse.x, ev.mouse.y);
	  
	  else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		  active_menu->check_for_click(display,ev.mouse.x, ev.mouse.y,button_event_queue);
	  
      if(redraw && al_is_event_queue_empty(event_queue)) 
	  {
         redraw = false;
         active_menu->draw(display,theme);
      }
	  
	  if(!button_event_queue.empty())
	  {
		 if( button_event_queue.front() == EDA_BUTTON_PLAY_PRESSED )
		 {
			button_event_queue.pop();
			delete active_menu;
			active_menu = new Eda_Menu_Game();
		 }
	  }
	  
   }
 
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
   delete active_menu;
   return 0;
}
