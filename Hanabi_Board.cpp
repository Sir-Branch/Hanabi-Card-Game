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

/*
 * This function tells us if there are any games lives left(Lightning tokens in hanabi)
 * 
 * Input:
 *	-void
 * 
 * Return:
 *	-Boolean: If true at least 1 live left.
 */
bool Hanabi_Board::any_lifes_left(void)
{
	bool any_lifes_left = false;
	for(int i = 0 ; (any_lifes_left == false) && i < HANABI_LIGHT_TOKENS ; i++)
		if( light_tokens[i].token_heads())
			any_lifes_left = true;
	
	return any_lifes_left;
}


/*
 * This function tells us if there are any games clues tokens left in hanabi game
 * 
 * Input:
 *	-void
 * 
 * Return:
 *	-Boolean: True if at least 1 clue left.
 */
bool Hanabi_Board::any_clues_left(void)
{
	bool any_clues_left = false;
	for(int i = 0 ; (any_clues_left == false) && i < HANABI_CLUE_TOKENS ; i++)
		if( clue_tokens[i].token_heads())
			any_clues_left = true;
	
	return any_clues_left;
}

/*
 * This function tells us if all clues tokens are left in the hanabi game
 * 
 * Input:
 *	-void
 * 
 * Return:
 *	-Boolean: True if all the clues are left.
 */
bool Hanabi_Board::all_clues_left(void)
{
	bool all_clues_left = true;
	for(int i = 0 ; (all_clues_left == true) && i < HANABI_CLUE_TOKENS ; i++)
		if( !clue_tokens[i].token_heads())
			all_clues_left = false;
	
	return all_clues_left;
}

/*
 * This function removes one of the lives, when no lives are left this function sets the lost_game flag to true
 *
 * Input:
 *	-void
 * 
 * Return:
 *	-void
 */
void Hanabi_Board::lose_live(void)
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

/*
 * This function adds(Flips to head) one clue to the clue tokens. If all clues are available this function won't do anything.
 * and return false
 * 
 * Input:
 *	-void
 * 
 * Return:
 *	-bool: If successfully "added"(flips to head) one clue, return true. 
 *	If this function return false it's because all clue were available, thus no more clues can be added.
 * 
 * NOTE CLUE TOKENS:
 *	-Head: Clue available
 *	-Tails: Clue not available/has been used.
 */
bool Hanabi_Board::add_clue_tokens(void)
{
	bool clue_added = false;
	for( int i = 0 ; i < HANABI_LIGHT_TOKENS && clue_added == false ; i++)
		if( !clue_tokens[i].token_heads())
		{
			clue_tokens[i].flip_token();
			clue_added = true;
		}
	return clue_added;
}

/*
 * This function removes(Flips to tails) one clue from the clue tokens. If all clues are not available this function won't do anything.
 * and returnss false
 * 
 * Input:
 *	-void
 * 
 * Return:
 *	-bool: If successfully "removed"(flips to tails) one clue, return true. 
 *	If this function return false it's because all clue were not available, thus no more clues can be removed.
 * 
 * NOTE CLUE TOKENS:
 *	-Head: Clue available
 *	-Tails: Clue not available/has been used.
 */
bool Hanabi_Board::remove_clue_tokens(void)
{
	bool clue_removed = false;
	for( int i = 0 ; i < HANABI_LIGHT_TOKENS && clue_removed == false; i++)
		if(clue_tokens[i].token_heads() )
		{
			clue_tokens[i].flip_token();
			clue_removed = true;
		}
	return clue_removed;
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

/*
 * This function discards a specific card in the players hands, and sends it to the graveyard
 * Note: This game is not Yu-gi-oh, no monster reborn from graveyard.
 *
 * Input:
 *	-unsigned int card_my_hand: Card position in hand, goes from 0 to 5. 
 * 
 * Return:
 *	-void
 *
 */
void Hanabi_Board::discard_card(unsigned int card_my_hand){
	
	Hanabi_Card * card = &my_cards[card_my_hand].playing_card;
	grave_yard[ get_suit_number_array(card->get_suit()) ].addcard_front( *card);
}

/*
 * This function tells us if a specific card in the players hands can be placed in the center decks/piles 
 *
 * Input:
 *	-unsigned int card_my_hand: Card position in hand, goes from 0 to 5. 
 * 
 * Return:
 *	-bool: Returns true if the card can be placed
 *
 */
bool Hanabi_Board::can_place_card(unsigned int card_my_hand)
{
	bool can_place_card = false;
	Hanabi_Card * card = &my_cards[card_my_hand].playing_card;
	if( card->get_suit() != HANABI_CARD_SUIT_EMPTY)
		if ( central_cards[ get_suit_number_array( card->get_suit()) ].get_value() == (card->get_value()-1) )
			can_place_card = true;//If the card of the same suit in the central array is the previous value then I can place the card.
		
	return can_place_card;
}

/*
 * This function draws a card, in case of not being able to draw a card an empty card is left in the position in the hand
 * where the drawn card wanted to be placed.
 *
 * Input:
 *	-unsigned int card_my_hand: Card position in hand, goes from 0 to 5. 
 * 
 * Return:
 *	-bool: Returns true if the card could be drawn, if a card couldn't be drawn it's because the deck is empty.
 *
 */
bool Hanabi_Board::draw_card(unsigned int card_my_hand)
{
	bool could_draw_card;
	in_game_hanabi_Card_t card_to_draw = {false,false};
	
	if( !(could_draw_card = hanabi_game_deck.draw_rand_card(card_to_draw.playing_card) ))
	{
		#warning "ADD flag if no cards are left in deck thus only 1 move each remains"
		card_to_draw.playing_card = Hanabi_Card();

	}
	my_cards[card_my_hand] = card_to_draw;
	return could_draw_card;
}

#include "Hanabi_Card.h"
#include "Hanabi_Network_Defines.h"
/*
 * This function receives a clue and updates the cards in hand to reflect the clues.
 * 

 * Input:
 *	-char value_or_suit: Hint received, can be a value or suit Example 1 or 'R'
 * 
 * Return:
 *	-void
 *
 */
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
//	
//	-Play Card
//	-Discard Card
//	-Give hint


/*
 * This function carries out one of the three possible player actions: Play card
 * 
 * Play card action:	1) Tries to play card in center, if not posible loses live and discard card
 *						2) Draw card
 *
 * Input:
 *	-unsigned int card_my_hand: Card position in hand, goes from 0 to 5. 
 * 
 * Return:
 *	-bool: Returns true if the card could be played.
 *
 */
bool Hanabi_Board::player_action_play_card(unsigned int card_my_hand)
{
	bool could_place_card;
	if( could_place_card = can_place_card(card_my_hand) )
	{
		central_cards[ get_suit_number_array(  my_cards[card_my_hand].playing_card.get_suit() )] = my_cards[card_my_hand].playing_card;
	}
	else
	{
		this->discard_card(card_my_hand);
		this->lose_live();
	}
	
	draw_card(card_my_hand); //EXPLOTA tdoa revisar
	return could_place_card;
}

/*
 * This function carries out one of the three possible player actions: Discard card
 * 
 * Discard card action:	1) Discards specific card in hand
 *						2) Flips clue tokens (adds a clue, max 8 or 9 depending on settings)
 *						3) Draw Card
 *
 * Input:
 *	-unsigned int card_my_hand: Card position in hand, goes from 0 to 5. 
 * 
 * Return:
 *	-void
 */
void  Hanabi_Board::player_action_discard_card(unsigned int card_my_hand)
{
	discard_card(card_my_hand);
	flip_clue_tokens(false); //False adds new clue
	draw_card(card_my_hand);
}


#include <iostream>
#include "Hanabi_You_Have_Packet.h"
#include "TFTP_Packet.h"
#include "Hanabi_Network_Defines.h"

/*
 * This function carries out one of the three possible player actions: Give hint
 * 
 * Discard card action:	Send hint via network
 *					
 * Input:
 *	-char value_or_suit: Hint to be sent, can be a value or suit Example 1 or 'R'
 * 
 * Return:
 *	-bool: Returns true if the hint was sent successfully
 */
bool Hanabi_Board::player_action_give_clue(char value_or_suit,TFTPCxn * cxn )
{
	Hanabi_You_Have_Packet * to_send = new Hanabi_You_Have_Packet(value_or_suit);
	return APR_SUCCESS == to_send->send_packet(cxn->get_cxn_socket());
}

#include <iostream>
void Hanabi_Board::print_my_hand(void)
{
	std::cout << "\nPrinting my hand \n";
	for(int i = 0 ; i < HANABI_HAND_SIZE ; i++)
		my_cards[i].playing_card.print_card();
}