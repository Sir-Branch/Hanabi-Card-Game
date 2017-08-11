/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hanabi_Card.h
 * Author: r2d2
 *
 * Created on July 1, 2016, 8:24 PM
 */

#ifndef CARD_H
#define CARD_H

//Hanabi_Card class for Hanabi Board 

#define HANABI_CARD_NUM_SUITS 5
#define HANABI_CARD_NUM_VALUES 5

typedef enum hanabi_suits{HANABI_CARD_SUIT_EMPTY = 0, HANABI_CARD_YELLOW='Y', HANABI_CARD_RED='R', HANABI_CARD_BLUE ='B', HANABI_CARD_WHITE='W', HANABI_CARD_GREEN='G'}hanabi_suits_t;
typedef enum hanabi_values{HANABI_CARD_VALUE_EMPTY = 0 ,HANABI_CARD_ONE = 1, HANABI_CARD_TWO, HANABI_CARD_THREE, HANABI_CARD_FOUR, HANABI_CARD_FIVE}hanabi_values_t;
	
class Hanabi_Card {
public:

    Hanabi_Card(hanabi_suits_t suit = HANABI_CARD_SUIT_EMPTY, hanabi_values_t hanabi_values  = HANABI_CARD_VALUE_EMPTY);
    bool operator==(const Hanabi_Card& card);
    bool operator!=(const Hanabi_Card& card);
    //operator= no need to overwrite 
	hanabi_suits_t get_suit(void);
	hanabi_values_t get_value(void);
	int get_suit_number(void);
	void print_card(void);
	
private:
    hanabi_suits_t suit;
    hanabi_values_t value;
};

#endif /* CARD_H */

