/* 
 * File:   Token.cpp
 * Author: r2d2
 * 
 * Created on July 25, 2016, 6:21 PM
 */

#include "Token.h"
/*
 * This constructor initialize the token head as true (head)
 *
 */
Token::Token() : pos_heads(true){
	
}

/*
 * This getter function returns the state of the token. True equals head and false equals cross.
 *
 * Input:
 *	-void
 * 
 * Return:
 *	-bool: Returns true if the token is heads up or false if it is cross.
 */
bool Token::token_heads(void)
{
	return pos_heads;
}

/*
 * This function changes the state of a token making and Xor. 
 *
 * Input:
 *	-void
 * 
 * Return:
 *	-void
 */
void Token::flip_token(void)
{
	pos_heads ^= true; //Xor is made. True is changed to false and false is changed to true.
   
}