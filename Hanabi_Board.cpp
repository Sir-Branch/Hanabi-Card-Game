/* 
 * File:   Hanabiboard.cpp
 * Author: r2d2
 * 
 * Created on July 25, 2016, 7:25 PM
 */

#include "Hanabi_Board.h"
#include <time.h>
#include <iostream>
#include "Hanabi_Card.h"
#include "Hanabi_Network_Defines.h"
#include "Hanabi_You_Have_Packet.h"
#include "TFTP_Packet.h"
#include "Hanabi_Network_Defines.h"

Hanabi_Board::Hanabi_Board() {	
#warning "Move at end stage to main srand"
	srand(time(NULL)); 
	lost_game = false;
	last_hand = false;
}


/*
 * Player action functions. The following functions are called to get how many clues are left, if there are clues 
 * left, if there are not clues left, to add a clue or to remove a clue. 
 *
 */
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
bool Hanabi_Board::add_clue_token(void)
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
bool Hanabi_Board::remove_clue_token(void)
{
	bool clue_removed = false;
	for( int i = 0 ; i < HANABI_LIGHT_TOKENS && clue_removed == false; i++)
		if(clue_tokens[i].token_heads()) //Check if the token is heads up (true)
		{
			clue_tokens[i].flip_token(); //Flip token to cross (false) 
			clue_removed = true;
		}
	return clue_removed;
}

/*
 * This function checks if the clue the player wants to send is valid. First checks if it is a value or suits clue
 * then checks if the clue corresponds with the others player hand. If something of the above is not fulfilled, it returns false.
 *
 * Input:
 *	-unsigned char value_or_suit: Card value goes from 0 to 5 and suits values are 0, Y, R, B, W, G. 
 * 
 * Return:
 *	-bool: Returns true if the clue corresponds to the other players hand, false if its not.
 *
 */
bool Hanabi_Board::validate_give_clue(unsigned char value_or_suit)
{
    bool valid = false;
    bool value = (value_or_suit <= 5) ? true : false; //Check if is value or suit

    for(int i = 0; !valid && i < 6 ; i++)
    {
        if(value)
        {
            if(otherplayers_hand[i].get_value() == value_or_suit) //Check the other players hand if the value clue the player 
				//wants to send corresponds with the other players hand. 
				valid = true;
        }
        else
        {
            if(otherplayers_hand[i].get_suit() == value_or_suit) //Check the other players hand if the suit clue the player 
				//wants to send corresponds with the other players hand.
				valid = true;
        }
	}
    return valid;
}


/*
 * This function checks how many clues are left. Returns this value 
 *
 * Input:
 *	-void 
 * 
 * Return:
 *	-unsigned int: Returns the number of clues left max 10. 
 *
 */
unsigned int Hanabi_Board::number_clues_left(void)
{
	unsigned int clues_left = 0;
	for(int i = 0; i < HANABI_CLUE_TOKENS ; i++) //Checks all clue tokens
		if(clue_tokens[i].token_heads()) //True equals head (token is available) 
			clues_left++;// Could use directly i and break;
	
	return clues_left;
	
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
void Hanabi_Board::discard_card(unsigned int card_my_hand)
{
	Hanabi_Card * card = &my_cards[card_my_hand].playing_card;
	grave_yard[ card->get_suit_number() ].addcard_front( *card);
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
		if ( central_cards[ card->get_suit_number() ].get_value() == (card->get_value()-1) )
			can_place_card = true;//If the card of the same suit in the central array is the previous value then I can place the card.
		
	return can_place_card;
}

/*
 * Receive action functions. The following functions are called upon receiving the other player's actions.
 * Possibles actions that can be receive are: get a clue, draw a card, play a card and discard a card. 
 */

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
void Hanabi_Board::receive_action_get_clue(unsigned char value_or_suit)
{
	if(value_or_suit >= 'A' && value_or_suit <= 'Z') //if its a suit/color hint
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

/*
 * This function receives a Hanabi_Card draw by the other player. Then, the card is removed from the deck and from the other 
 * players hand. 
 * 
 * Input:
 *	-Hanabi_card: receives the card draw from the other player
 * 
 * Return:
 *	-void
 *
 */
void Hanabi_Board::receive_action_draw_card(Hanabi_Card card_drawn)
{
	if(hanabi_game_deck.remove_specific_card(card_drawn)) //Check if the card was successfully removed
            otherplayers_hand[otherplayers_card_replace] = card_drawn; //Set other player hand as drawn 
	
	else //The card could not be removed.
	{
            #warning "que pasa si no se pudo sacar del mazo una carta, paquete de error ??"
		;//ERROR
	}
}

/*
 * This function receives the number of the other player played card. The function checks if the card could 
 * be placed and then is added to the central deck or the card is send to the graveyard.
 * 
 * Input:
 *	-unsigned int: receives the card number played by the other player.
 * 
 * Return:
 *	-void
 *
 */
void Hanabi_Board::receive_action_play_card(unsigned int card_other_hand)
{
	bool could_place_card;
	
	if( could_place_card = can_place_card(card_other_hand) ) // If the card could be placed we add it to the central deck.
	{
		central_cards[ otherplayers_hand[card_other_hand].get_suit_number() ] = otherplayers_hand[card_other_hand];
	}
	else
	{
		//Adds card to graveyard, no monster reborn in this game
		grave_yard[ otherplayers_hand[card_other_hand].get_suit_number() ].addcard_end( otherplayers_hand[card_other_hand] );
		this->lose_live(); //Both players lose a live.
	}
	
	otherplayers_card_replace = card_other_hand; //Will receieve a Draw after this (the other player will draw a new card), so we must know in which position to place the drawn card.
}

/*
 * This function receives the number of the other player played card. The function checks if the card could 
 * be placed and then is added to the central deck or the 
 * 
 * Input:
 *	-unsigned int: receives the card number played by the other player.
 * 
 * Return:
 *	-void
 *
 */
void Hanabi_Board::receive_action_discard_card(unsigned int card_other_hand)
{
	otherplayers_card_replace = card_other_hand; //Will receive a Draw after this, so we must know in which position to place the drawn card.
	if ( !this->add_clue_token()) //Checks if a clue can be added. In fact this code will never we executed since before the other player
            //discards a card, clue tokens are previously checked. 
            std::cerr << "Could not add a clue since there are already the max number of clues" << std::endl;	 
            
}


/*
 * Player action functions. The following functions are called after triging player's actions.
 * Player possible actions are: play card, discard card and give hint.
 *
 */

/*
 * This function carries out one of the three possible player actions: Play card
 * 
 * Play card action:	1) Tries to play card in center, if not possible loses a life and discard the card
 *			2) Draw card
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
            central_cards[ my_cards[card_my_hand].playing_card.get_suit_number() ] = my_cards[card_my_hand].playing_card;
	}
	else
	{
            this->discard_card(card_my_hand); //Could not play card, the card is discarded.
            this->lose_live(); //A life is lost.
	}
	
	//Either way the card is draw.
        draw_card(card_my_hand); //Draw a new card. If there are no more card in the deck the function draw_card changes the flag
	return could_place_card;
}
/*
 * This function carries out one of the three possible player actions: Discard card
 * 
 * Discard card action:	1) Discards specific card in hand
 *			2) Flips clue tokens (adds a clue, max 8 or 9 depending on settings)
 *			3) Draw Card
 *
 * Input:
 *	-unsigned int card_my_hand: Card position in hand, goes from 0 to 5. 
 * 
 * Return:
 *	-void
 */
void  Hanabi_Board::player_action_discard_card(unsigned int card_my_hand)
{
    discard_card(card_my_hand); //Discards a card.
    if(!add_clue_token())
    {
        //Checks if a clue can be added. In fact this code will never we executed since before the other player
        //discards a card, clue tokens are previously checked. 
        std::cerr << "Could not add a clue since there are already the max number of clues" << std::endl;
    }

    draw_card(card_my_hand); //Draw a new card. If there are no more card in the deck the function draw_card changes the flag

}
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
bool Hanabi_Board::player_action_give_clue(unsigned char value_or_suit, TFTPCxn * cxn)
{
	Hanabi_You_Have_Packet * to_send = new Hanabi_You_Have_Packet(value_or_suit);
	return (APR_SUCCESS == cxn->send_packet(to_send));
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
	in_game_hanabi_Card_t card_to_draw = {false, false}; 
	
	if( !(could_draw_card = hanabi_game_deck.draw_rand_card(card_to_draw.playing_card) ))
	{
            last_hand = true; //Flag to know is the last hand
            card_to_draw.playing_card = Hanabi_Card(); //Puts in the deck a"black" card
            
            #warning "que hacemos cuando no hay mas cartas"
	}
	my_cards[card_my_hand] = card_to_draw;
	return could_draw_card;
}


/*
 * Live  functions. The following functions are called to know how many lives are left, if there are lives left or to lose a live.
 *
 */

/*
 * This function checks how many lives are left. Returns this value 
 *
 * Input:
 *	-void 
 * 
 * Return:
 *	-unsigned int: Returns the number of lives left max 3. 
 *
 */
unsigned int Hanabi_Board::number_lives_left(void)
{
	unsigned int lifes_left = 0;
	for(int i = 0; i < HANABI_LIGHT_TOKENS ; i++) //Checks all clue tokens
		if( light_tokens[i].token_heads()) //True equals head (token is available)
			lifes_left++;// could use directly i and break;
	
	return lifes_left;
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
bool Hanabi_Board::any_lives_left(void)
{
	bool any_lifes_left = false;
	for(int i = 0 ; (any_lifes_left == false) && i < HANABI_LIGHT_TOKENS ; i++)
		if( light_tokens[i].token_heads())
			any_lifes_left = true;
	
	return any_lifes_left;
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
 * This function calculates the score checking the central cards
 *
 * Input:
 *	-void 
 * 
 * Return:
 *	-unsigned int: Returns the score (from 0 to 25)
 *
 */
unsigned int Hanabi_Board::calculate_score()
{
	unsigned int score = 0;
	for( int i = 0 ; i < HANABI_NUMBER_COLORS ; i++)
		score += central_cards[i].get_value();
	return score; 
}


/*
 * Debugging  functions.  
 *
 */
#warning "Funcion de debug, se puede borrar"
void Hanabi_Board::print_my_hand(void)
{
	std::cout << "\nPrinting my hand \n";
	for(int i = 0 ; i < HANABI_HAND_SIZE ; i++)
		my_cards[i].playing_card.print_card();
}