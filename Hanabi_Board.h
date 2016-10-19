/* 
 * File:   Hanabiboard.h
 * Author: r2d2
 *
 * Created on July 25, 2016, 7:25 PM
 */

#ifndef HANABIBOARD_H
#define HANABIBOARD_H

#include "Hanabi_Card.h"
#include "Deck.h"
#include "Token.h"
#include "Hanabi_Deck.h"

#define HANABI_LIGHT_TOKENS		3	//These are the "lifes" in hanabi
#define HANABI_CLUE_TOKENS		9	
#define HANABI_NUMBER_COLORS	5	//Yeah colors the u is only if u are British 
#define HANABI_CARDS_PER_HAND	6

/*
 * Para optimizacion de memoria y velocidad no vale la pena que las cartas que no esten en mano
 * tengan este formato, razon por la cual solamente se utilizaran para la mano del jugador que no ve sus cartas(mano propia).
 * (Esto deja emplementar la opcion de poder tener ayuda de memoria, sin un sacrificio de optimizacion)
 */
typedef struct
{
    bool color_hint;
    bool num_hint;
	Hanabi_Card playing_card;
}in_game_hanabi_Card_t;

//The suit of each card has a position for the central array use get_suit_number_array

#warning "Think about making players class"
#include "TFTPCxn.h"

class Hanabi_Board{
public:
    Hanabi_Board();
	
    bool any_lifes_left(void);
    bool any_clues_left(void);
	bool all_clues_left(void);
	
	//Players only have 3 possible actions 
	bool player_action_play_card(unsigned int card_my_hand);
	void player_action_discard_card(unsigned int card_my_hand);
	void player_action_give_clue(char value_or_suit,TFTPCxn * cxn );
#warning "Falta probar give clue"
	
//	void recieve_action_play_card(Hanabi_Card card);
//	void recieve_action_discard_card(Hanabi_Card card);
	void receive_action_get_clue(char value_or_suit);//player can only "receive" one action which is a clue
	void print_my_hand(void);
	Hanabi_Deck hanabi_game_deck;
    
public://Public for testing functions
	
	void lose_life(void);
	void flip_clue_tokens(bool flip_head);
	bool can_place_card(unsigned int card_my_hand);
	int get_suit_number_array(hanabi_suits_t suit);
	
	bool draw_card(unsigned int card_my_hand);
	void discard_card(unsigned int card_my_hand);
	
#warning "Hanabi_deck graveyard starting with all cards"
	Hanabi_Deck grave_yard[HANABI_NUMBER_COLORS]; // Uno por color
    Token light_tokens[HANABI_LIGHT_TOKENS];//Representan las vidas 
    Token clue_tokens[HANABI_CLUE_TOKENS];//Maxima numero de pistas que se pueden dar sin tomar carta
    unsigned int score;//0 a 25
   
    Hanabi_Card central_cards[HANABI_NUMBER_COLORS];//De aca se ven las pilas (convendra usarlas como card ya que solamente se ve la de arriba)
	//Convendra usar una de ints del 0 al 5??
	
	Hanabi_Card otherplayers_hand[HANABI_CARDS_PER_HAND];
	in_game_hanabi_Card_t my_cards[HANABI_CARDS_PER_HAND];
	
	bool last_hand; //Deck was emptied one play each left.
    bool lost_game;
};

#endif /* HANABIBOARD_H */

