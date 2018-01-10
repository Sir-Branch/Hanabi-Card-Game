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
 * @Tokens class. A token can only have two sides, head or cross.
 * The class has two methods. It was decided to use a class in case we want to add more options in the future
 */
class Token {
public:
    Token();
    
    void flip_token(void); 
    bool token_heads(); 
    
    
protected:
    bool pos_heads; //Depending on the side, pos_heads is true or false
};

#endif /* TOKEN_H */

