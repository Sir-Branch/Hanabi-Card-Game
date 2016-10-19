/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hanabi_Deck.cpp
 * Author: r2d2
 * 
 * Created on July 25, 2016, 8:02 PM
 */
#include "Hanabi_Card.h"
#include "Hanabi_Deck.h"

/*
 * Constructor for a hanabi deck, loads all the cards needed to start the game.
 */
Hanabi_Deck::Hanabi_Deck() 
{
	hanabi_suits_t hanabi_suits[HANABI_CARD_NUM_SUITS] = { HANABI_CARD_YELLOW, HANABI_CARD_RED, HANABI_CARD_BLUE, HANABI_CARD_WHITE, HANABI_CARD_GREEN};
	for(unsigned int current_suit=0; current_suit < HANABI_CARD_NUM_SUITS; current_suit++)
	{
		this->addcard_front(Hanabi_Card(hanabi_suits[current_suit], HANABI_CARD_ONE));
		this->addcard_front(Hanabi_Card(hanabi_suits[current_suit], HANABI_CARD_ONE));
		this->addcard_front(Hanabi_Card(hanabi_suits[current_suit], HANABI_CARD_ONE));
		this->addcard_front(Hanabi_Card(hanabi_suits[current_suit], HANABI_CARD_TWO));
		this->addcard_front(Hanabi_Card(hanabi_suits[current_suit], HANABI_CARD_TWO));
		this->addcard_front(Hanabi_Card(hanabi_suits[current_suit], HANABI_CARD_THREE));
		this->addcard_front(Hanabi_Card(hanabi_suits[current_suit], HANABI_CARD_THREE));
		this->addcard_front(Hanabi_Card(hanabi_suits[current_suit], HANABI_CARD_FOUR));
		this->addcard_front(Hanabi_Card(hanabi_suits[current_suit], HANABI_CARD_FOUR));
		this->addcard_front(Hanabi_Card(hanabi_suits[current_suit], HANABI_CARD_FIVE));
	}
}

//No me gusta como esta, ver bien como hacer 
Hanabi_Deck::Hanabi_Deck(bool true_or_false_for_empty_deck)
{
	
}
#include <iostream>
void Hanabi_Deck::print_deck(void)
{
	std::cout << "\nDeck size is: " << deck.size() << std::endl;
	for(it = deck.begin() ; it!= deck.end(); it++ )
		it->print_card();
}


/*
#include <cstdlib>
#include <iostream>
#include "Hanabi_Deck.h"
#include "Hanabi_Card.h"
using namespace std;

int main(int argc, char** argv) {

	Hanabi_Deck	game_deck;
	
	std::cout << "Deck size:" << game_deck.size() << std::endl;
	
	game_deck.print_deck();
	std::cout <<"\n\n\n\n";
	
	if( game_deck.remove_specific_card(Hanabi_Card( (hanabi_suits_t)'R', HANABI_CARD_FIVE )) )
		std::cout<<"Removed Red 5\n";
	std::cout << "Deck size:" << game_deck.size() << std::endl;
	game_deck.print_deck();
	std::cout <<"\n\n\n\n";
	
	if( !game_deck.remove_specific_card(Hanabi_Card((hanabi_suits_t)'R', HANABI_CARD_FIVE )) )
		std::cout<<"Unable to removed Red 5\n";
	std::cout << "Deck size:" << game_deck.size() << std::endl;
	game_deck.print_deck();
	std::cout <<"\n\n\n\n";
			
			
	return 0;
}

*/