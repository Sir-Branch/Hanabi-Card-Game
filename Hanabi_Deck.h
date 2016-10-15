/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hanabi_Deck.h
 * Author: r2d2
 *
 * Created on July 25, 2016, 8:02 PM
 */

#ifndef HANABI_DECK_H
#define HANABI_DECK_H
#include "Deck.h"
#include "Hanabi_Card.h"


class Hanabi_Deck : public Deck<Hanabi_Card> {
public:
    
    Hanabi_Deck();
	Hanabi_Deck(bool true_or_false_for_empty_deck);
	void print_deck(void);
   // Hanabi_Deck(const Hanabi_Deck& orig);
   // virtual ~Hanabi_Deck();
    
private:

};

#endif /* HANABI_DECK_H */

