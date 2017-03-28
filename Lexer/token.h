//
//  token.h
//  Lexer
//
//  Created by Jasmine Jans on 4/10/16.
//  Copyright © 2016 Jasmine Jans. All rights reserved.
//

#ifndef token_h
#define token_h

#include <string>

enum class TokenType {
    PRINT, PRINTLN, READINT, READSTR, LPAREN, RPAREN, SEMICOLON, ID, LBRACKET, RBRACKET, STRING, INT, BOOL, COMMA, ASSIGN, PLUS, MINUS, DIVIDE, MULTIPLY, IF, THEN, ELIF, ELSE, END, NOT, AND, OR, EQUAL, LESS_THAN, GREATER_THAN, LESS_THAN_EQUAL, GREATER_THAN_EQUAL, NOT_EQUAL, WHILE, DO, EOS
};

class Token{
public:
    Token();
    Token(TokenType type, std::string lexeme, int line, int column);
    std::string get_lexeme() const;
    TokenType get_type() const;
    int get_line() const;
    int get_column() const;
private:
    std::string lexeme;
    TokenType type;
    int line;
    int column;

};

#endif /* token_h */
