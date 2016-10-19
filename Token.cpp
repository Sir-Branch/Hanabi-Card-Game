/* 
 * File:   Token.cpp
 * Author: r2d2
 * 
 * Created on July 25, 2016, 6:21 PM
 */

#include "Token.h"

Token::Token() : pos_heads(true){
	
}


bool Token::token_heads(void)
{
	return pos_heads;
}

void Token::flip_token(void)
{
	pos_heads ^= true; //xor true: true -> false y false ->true 
}