/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Token.h
 * Author: r2d2
 *
 * Created on July 25, 2016, 6:21 PM
 */

#ifndef TOKEN_H
#define TOKEN_H


/* 
 * Puede parecer medio innecesario el uso de una clase para tokens, pero esta bueno dejar abierta la posibilidad de modificar
 * cosa que no se puede lograr en un arreglo de bools
 * 
 * Token basico solamente puede tener dos lados 
 *      -Cara
 *      -Cruz  
 * 
 */
class Token {
public:
    Token();
    
    void flip_token(void);
    bool token_heads(); //true si esta en heads/cara
    
    
protected:
    bool pos_heads; //true or false segun el lado
};

#endif /* TOKEN_H */

