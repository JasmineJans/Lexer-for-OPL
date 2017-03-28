//
//  parser.hpp
//  Lexer
//
//  Created by Jasmine Jans on 4/14/16.
//  Copyright © 2016 Jasmine Jans. All rights reserved.
//

#ifndef parser_h
#define parser_h

#include <memory>
#include "lexer.h"
#include "token.h"

class Parser{
    public:
        Parser(Lexer& lexer);
        void parse();
    private:
        //the lexer for lexing through the tokens
        Lexer& lexer;
    
        //the current token the lexer is on
        Token current_token;
    
        //this calls next token, moves through the file
        void advance();
    
        //this calls advance or throws a given error if the current_token type is the token type given
        void eat(TokenType token_type, const std::string& msg);
    
        //a bool function to return weather the current token type is the passed in type
        bool curr_token_type(TokenType token_type);
    
        //error method to throw errors if a grammar fails
        void error(const std::string& msg);
    
        //all of the non terminals as void or bool functions
        void stmts();
        void stmt();
        void output();
        void input();
        void assign();
        void listindex();
        void expr();
        void exprt();
        void value();
        void exprlist();
        void exprtail();
        bool math_rel();
        void cond();
        void condt();
        void bexpr();
        void bexprt();
        void bconnct();
        bool bool_rel();
        void loop();
};

#endif /* parser_h */
