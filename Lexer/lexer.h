//
//  lexer.h
//  Lexer
//
//  Created by Jasmine Jans on 4/10/16.
//  Copyright © 2016 Jasmine Jans. All rights reserved.
//

#ifndef lexer_h
#define lexer_h

#include <istream>
#include "token.h"

class Lexer
{
public:
    Lexer(std::istream& input_stream);
    Token next_token();
    Token id_token(char symbol);
private:
    int line;
    int column;
    std::istream& input_stream;
};

#endif /* lexer_h */
