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
/*
 *@Hanabi_Card class for Hanabi Board. Saves the suit and value of a card. 
 *Has getters to know this information and operator to change these values.
 */

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
	hanabi_suits_t get_suit(void) const; //Getter 
	hanabi_values_t get_value(void) const; //Getter
	int get_suit_number(void); //Getter
	void print_card(void); //Debugging method
	
private:
    hanabi_suits_t suit;
    hanabi_values_t value;
};

/*
 *Para optimizacion de memoria y velocidad no vale la pena que las cartas que no esten en mano
 *tengan este formato, razon por la cual solamente se utilizaran para la mano del jugador que no ve sus cartas(mano propia).
 *(Esto deja emplementar la opcion de poder tener ayuda de memoria, sin un sacrificio de optimizacion)
 */
typedef struct
{
    bool color_hint;
    bool num_hint;
    int number_time_hint;
    int color_time_hint;
    Hanabi_Card playing_card;
}in_game_hanabi_Card_t;

#endif /* CARD_H */

