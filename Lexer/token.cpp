//
//  token.cpp
//  Lexer
//
//  Created by Jasmine Jans on 4/10/16.
//  Copyright © 2016 Jasmine Jans. All rights reserved.
//

#include <string>
#include "token.h"

Token::Token() : type(TokenType::EOS), lexeme(""), line(0), column(0)
{
    
}

Token::Token(TokenType type, std::string lexeme, int line, int column) :
type(type), lexeme(lexeme), line(line), column(column)
{
    
}

std::string Token::get_lexeme() const
{
    return lexeme;
}

TokenType Token::get_type() const
{
    return type;
}

int Token::get_line() const
{
    return line;
}

int Token::get_column() const
{
    return column;
}

