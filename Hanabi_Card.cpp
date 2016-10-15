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
	
hanabi_suits_t Hanabi_Card::get_suit(void){
	return suit;	
}

hanabi_values_t Hanabi_Card::get_value(void){
	return value;
}
	
#include <iostream>
void Hanabi_Card::print_card(void)
{
	std::cout << (char)suit << (int) value <<std::endl;  
}

