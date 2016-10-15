/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hanabiboard.cpp
 * Author: r2d2
 * 
 * Created on July 25, 2016, 7:25 PM
 */

#include "Hanabi_Board.h"
#include <time.h>
Hanabi_Board::Hanabi_Board() {
	
	srand(time(NULL));
	lost_game = false;
	
	
}

bool Hanabi_Board::any_lifes_left(void)
{
	bool any_lifes_left = false;
	for(int i = 0 ; (any_lifes_left == false) && i < HANABI_LIGHT_TOKENS ; i++)
		if( light_tokens[i].token_heads())
			any_lifes_left = true;
	
	return any_lifes_left;
}


bool Hanabi_Board::any_clues_left(void)
{
	bool any_clues_left = false;
	for(int i = 0 ; (any_clues_left == false) && i < HANABI_CLUE_TOKENS ; i++)
		if( clue_tokens[i].token_heads())
			any_clues_left = true;
	
	return any_clues_left;
}

bool Hanabi_Board::all_clues_left(void)
{
	bool all_clues_left = true;
	for(int i = 0 ; (all_clues_left == true) && i < HANABI_CLUE_TOKENS ; i++)
		if( !clue_tokens[i].token_heads())
			all_clues_left = false;
	
	return all_clues_left;
}

void Hanabi_Board::lose_life(void)
{
	int i;
	for( i = 0 ; i < HANABI_LIGHT_TOKENS ; i++)
		if(light_tokens[i].token_heads())
		{
			light_tokens[i].flip_token();
			break;
		}
	if( i == (HANABI_LIGHT_TOKENS-1) )
		lost_game = true;
	
}

//true one less clue, tails one more
//false one more clue
void Hanabi_Board::flip_clue_tokens(bool remove_clue )
{
	for( int i = 0 ; i < HANABI_LIGHT_TOKENS ; i++)
		if(clue_tokens[i].token_heads() == remove_clue)
		{
			clue_tokens[i].flip_token();
			break;
		}
}

/* Seems really shitty but don't know what else to do
 */
int Hanabi_Board::get_suit_number_array(hanabi_suits_t suit)
{
	
	switch(suit)
	{
		case HANABI_CARD_YELLOW:
			return 0;
			break;
			
		case HANABI_CARD_RED:
			return 1;
			break;
			
		case HANABI_CARD_BLUE:
			return 2;
			break;
			
		case HANABI_CARD_WHITE:
			return 3;
			break;
			
		case HANABI_CARD_GREEN:
			return 4;
			break;
			
		default:
			return -1;
			break;
			
	}
	
}

void Hanabi_Board::discard_card(unsigned int card_my_hand){
	
	Hanabi_Card * card = &my_cards[card_my_hand].playing_card;
	grave_yard[ get_suit_number_array(card->get_suit()) ].addcard_front( *card);
}

bool Hanabi_Board::can_place_card(unsigned int card_my_hand)
{
	bool can_place_card = false;
	Hanabi_Card * card = &my_cards[card_my_hand].playing_card;
	if( card->get_suit() != HANABI_CARD_SUIT_EMPTY)
		if ( central_cards[ get_suit_number_array( card->get_suit()) ].get_value() == (card->get_value()-1) )
			can_place_card = true;//If the card of the same suit in the central array is the previous value then I can place the card.
		
	return can_place_card;
}

//From 0 to 5
bool Hanabi_Board::draw_card(unsigned int card_my_hand)
{
	bool could_draw_card;
	in_game_hanabi_Card_t card_to_draw = {false,false};
	
	if( !(could_draw_card = hanabi_game_deck.draw_rand_card(card_to_draw.playing_card) ))
	{
		#warning "ADD flag if no cards are left in deck thus only 2 hands remain"
		card_to_draw.playing_card = Hanabi_Card();

	}
	my_cards[card_my_hand] = card_to_draw;
	return could_draw_card;
}

#include "Hanabi_Card.h"
#include "Hanabi_Network_Defines.h"

void Hanabi_Board::receive_action_get_clue(char value_or_suit)
{
	if(value_or_suit >= 'A' && value_or_suit <= 'Z') //if suit/color
	{
		for(int i = 0 ; i < HANABI_HAND_SIZE ; i++ )
			if(my_cards[i].playing_card.get_suit() == value_or_suit)
				my_cards[i].color_hint = true;
	}
	else // is a value hint
	{
		for(int i = 0 ; i < HANABI_HAND_SIZE ; i++ )
			if(my_cards[i].playing_card.get_value() == value_or_suit)
				my_cards[i].num_hint = true;
	}
	
}

//PLAYERS possible ACTION 

bool Hanabi_Board::player_action_play_card(unsigned int card_my_hand)
{
	bool could_place_card;
	if( could_place_card=can_place_card(card_my_hand) )
	{
		central_cards[ get_suit_number_array(  my_cards[card_my_hand].playing_card.get_suit() )] = my_cards[card_my_hand].playing_card;
		
	}
	else
	{
		this->discard_card(card_my_hand);
		this->lose_life();
	}
	
	draw_card(card_my_hand); //EXPLOTA tdoa revisar
	return could_place_card;
}

#include <iostream>

void  Hanabi_Board::player_action_discard_card(unsigned int card_my_hand)
{
	discard_card(card_my_hand);
	flip_clue_tokens(false); //False adds new clue
	draw_card(card_my_hand);

}



#include "Hanabi_You_Have_Packet.h"
#include "TFTP_Packet.h"
#include "Hanabi_Network_Defines.h"

void Hanabi_Board::player_action_give_clue(char value_or_suit,TFTPCxn * cxn )
{
	Hanabi_You_Have_Packet * to_send = new Hanabi_You_Have_Packet(value_or_suit);
	to_send->send_packet(cxn->get_cxn_socket());
}

#include <iostream>
void Hanabi_Board::print_my_hand(void)
{
	std::cout << "\nPrinting my hand \n";
	for(int i = 0 ; i < HANABI_HAND_SIZE ; i++)
		my_cards[i].playing_card.print_card();
}