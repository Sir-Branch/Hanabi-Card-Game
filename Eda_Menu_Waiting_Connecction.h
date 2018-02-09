/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Eda_Menu_Waiting_Connecction.h
 * Author: parallels
 *
 * Created on January 31, 2018, 9:10 AM
 */

#ifndef EDA_MENU_WAITING_CONNECCTION_H
#define EDA_MENU_WAITING_CONNECCTION_H
#include "Eda_Menu.h"
#include "Eda_Button.h"
#include <string>
#include <queue>
#include "allegro5/allegro5.h"
#include "Eda_Button.h"
#include "Hanabi_Skin.h"

class Eda_Menu_Waiting_Connecction : public Eda_Menu{
public:
    Eda_Menu_Waiting_Connecction();
    Eda_Menu_Waiting_Connecction(std::string theme);
    virtual ~Eda_Menu_Waiting_Connecction();
    void draw(ALLEGRO_DISPLAY *display, Hanabi_Skin *theme, Hanabi_Board *game_board, bool mem_help);
    void update_buttons(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse);
    bool check_for_click(ALLEGRO_DISPLAY * display, float x_mouse, float y_mouse, std::queue<hanabi_game_event_t> &button_event_queue);

private:
	
	Eda_Button * cancel;


};

#endif /* EDA_MENU_WAITING_CONNECCTION_H */

