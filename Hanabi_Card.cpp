/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hanabi_Card.cpp
 * Author: r2d2
 * 
 * Created on July 1, 2016, 8:24 PM
 */

#include "Hanabi_Card.h"

//Hanabi_Card::Hanabi_Card(){}

/*
 * Constructor. A card is initialized with value = empty and suit = empty
 *
 */
Hanabi_Card::Hanabi_Card(hanabi_suits_t suit , hanabi_values_t value){
	this->suit=suit;
	this->value=value;
}

/*
Hanabi_Card::Hanabi_Card(const Hanabi_Card& orig) {
	suit=orig.suit;
	value=orig.value;
}*/


bool Hanabi_Card::operator==(const Hanabi_Card& card2){
	return value==card2.value && suit==card2.suit;
}

bool Hanabi_Card::operator!=(const Hanabi_Card& card2){
	return value!=card2.value || suit!=card2.suit;
}

/*
 * This getter function returns the suit of a card. 
 *
 * Input:
 *	-void
 * 
 * Return:
 *	-hanabi_suits_t: Returns the suit of a card. Can go from 0 to 5.
 */
hanabi_suits_t Hanabi_Card::get_suit(void){
	return suit;	
}

/*
 * This getter function returns the value of a card. 
 *
 * Input:
 *	-void
 * 
 * Return:
 *	-hanabi_values_t: Returns the value of a card. Can go from 0 to 5.
 */
hanabi_values_t Hanabi_Card::get_value(void){
	return value;
}
	
#include <iostream>
void Hanabi_Card::print_card(void)
{
	std::cout << (char)suit << (int) value <<std::endl;  
}


/*
 * This function returns the corresponding placement inside arrays according to suit.
 * Examples:
 *	 -In what position is the 'R' (red) suit in the graveyard array, or central card array.
 * Remember that the board has Hanabi_Card central_cards[HANABI_NUMBER_COLORS]; so for example 
 * to add a Red card we must would use central_cards[ get_suit_number_array('R')] = red_to_add;
 *
 * Input:
 *	-void
 * 
 * Return:
 *	-void
 */
int Hanabi_Card::get_suit_number(void)
{
	
	switch(this->suit)
	{
		case HANABI_CARD_WHITE:
			return 0;
			break;
			
		case HANABI_CARD_BLUE:
			return 1;
			break;
			
		case HANABI_CARD_GREEN:
			return 2;
			break;
			
		case HANABI_CARD_YELLOW:
			return 3;
			break;
			
		case HANABI_CARD_RED:
			return 4;
			break;
			
		default:
			return -1;
			break;
			
	}
	
}