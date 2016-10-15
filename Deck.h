/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Deck.h
 * Author: r2d2
 *
 * Created on July 1, 2016, 9:01 PM
 */

#ifndef DECK_H
#define DECK_H

#include <list>
// ANTES DE QUE ME RE CAGUES A PEDOS AGUSTIN: Cuando trabajo con tamplates no puedo separar en .cpp y .h sino te rompe las pelotas el compilador 
//http://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file


template <class CARD_T>
class Deck {
public:
    Deck();
    virtual ~Deck();
	
    unsigned int size();
	void addcard_end(const CARD_T& cardtoadd);
	void addcard_front(const CARD_T& cardtoadd);
	
	bool draw(CARD_T& card_taken);
	bool draw_ncard(unsigned int place, CARD_T& card_taken); //starts from 0
	bool draw_rand_card(CARD_T& card_taken);
    bool remove_ncard(unsigned int place);
	bool remove_specific_card(CARD_T card_to_remove);

protected:
    Deck(const Deck& orig); //Too lazy not gonna use it, if I need it along the line I'll probably be pissed...
    typename std::list<CARD_T> deck;
    typename std::list<CARD_T>::iterator it;	
};


template <class CARD_T>
Deck<CARD_T>::Deck() {
}

template <class CARD_T>
Deck<CARD_T>::~Deck(){
}

template <class CARD_T>
unsigned int Deck<CARD_T>::size(){
	return deck.size();
}


template <class CARD_T>
void Deck<CARD_T>::addcard_end(const CARD_T& cardtoadd){
	deck.push_back(cardtoadd); 	
}

template <class CARD_T>
void Deck<CARD_T>::addcard_front(const CARD_T& cardtoadd){
	deck.push_front(cardtoadd); 	
}

template <class CARD_T>
bool Deck<CARD_T>::remove_specific_card(CARD_T card_to_remove)
{
	bool card_found = false;
	if( deck.size() )
		for(it = deck.begin() ; card_found == false && it!= deck.end(); it++ )
			if(*it == card_to_remove)
			{
				card_found = true;
				deck.erase(it++);
			}
	
	return card_found;
}

//STARTS FROM 0
template <class CARD_T>
bool Deck<CARD_T>::draw_ncard(unsigned int place, CARD_T& card_taken)
{
	bool grabbed_card = false;
	if( deck.size() > place) 
	{
		it = deck.begin();
		std::advance(it,place);
		card_taken = *it;
		grabbed_card = true;
		it =  deck.erase(it++);
	}
	return grabbed_card;
}

#include <stdlib.h>
template <class CARD_T>
bool  Deck<CARD_T>::draw_rand_card(CARD_T& card_taken)
{
	bool able_to_draw = false;
	if(deck.size())
		able_to_draw = draw_ncard(rand()%deck.size(), card_taken);
	
	return able_to_draw;
}

template <class CARD_T>
bool Deck<CARD_T>::remove_ncard(unsigned int place)
{
	bool erased_card = false;
	if(place && deck.size() >= place)
	{
		it = deck.begin();
		std::advance(it,place-1);
		erased_card = true;
		it =  deck.erase(it++);
	}
	return erased_card;
}

//STARTS FROM 1
template <class CARD_T>
bool Deck<CARD_T>::draw(CARD_T& card_taken)
{
	bool grabbed_card = false;
	if( deck.size()) // no puede ser 0 place
	{
		grabbed_card = true;
		card_taken = * deck.begin();
		deck.pop_front();
	}
	return grabbed_card;
}



/* Prueba de funcionamiento cards + deck 
 int main(int argc, char** argv) {

	Deck hanabideck;
	std::cout << hanabideck.size() << std::endl;
	hanabideck.addcard(Card(Card::BLUE,Card::ONE));
		std::cout << hanabideck.size() << std::endl;
	hanabideck.addcard(Card(Card::BLUE,Card::TWO));
		std::cout << hanabideck.size() << std::endl;

	hanabideck.addcard(Card(Card::BLUE,Card::THREE));
		std::cout << hanabideck.size() << std::endl;
		
		Card card1,card2,card3;
		hanabideck.removecard(1);
		
		hanabideck.getcard(1,card1);
			std::cout << hanabideck.size() << std::endl;
		hanabideck.drawcard(1,card2);
		std::cout << hanabideck.size() << std::endl;
		if(!hanabideck.drawcard(1,card3))
			std::cout << "Unable to get card " <<std::endl;
		std::cout << hanabideck.size() << std::endl;
		
	
	return 0;
} */

#endif /* DECK_H */

