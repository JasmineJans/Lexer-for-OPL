//
//  hw11.cpp
//  Lexer
//
//  Created by Jasmine Jans on 4/10/16.
//  Copyright © 2016 Jasmine Jans. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <memory>
#include "token.h"
#include "lexer.h"
#include "exception.h"


void print_token(const Token& token);

int main(int argc, char *argv[])
{
    if(argc < 2){
        std::cout << "USAGE: " << argv[0] << " file" << std::endl;
        return -1;
    }
    std::ifstream file(argv[1]);
    if(!file.is_open()) {
        std::cout << "ERROR: Unable to open '" << argv[1] << "'" << std::endl;
        return -1;
    }
    try {
        Lexer the_lexer(file);
        Token t = the_lexer.next_token();
        while(t.get_type() != TokenType::EOS){
            print_token(t);
            t = the_lexer.next_token();
        }
        print_token(t);
    } catch(Exception e){
        std::cout << e.what() << std::endl;
    }
    file.close();
}

void print_token(const Token& the_token)
{
    std::string string = "";
    
    switch(the_token.get_type()){
        case TokenType::EOS: string = "EOS";
            break;
        case TokenType::DO: string = "DO";
            break;
        case TokenType::WHILE: string = "WHILE";
            break;
        case TokenType::IF: string = "IF";
            break;
        case TokenType::ELIF: string = "ELIF";
            break;
        case TokenType::ELSE: string = "ELSE";
            break;
        case TokenType::END: string = "END";
            break;
        case TokenType::PRINTLN: string = "PRINTLN";
            break;
        case TokenType::PRINT: string = "PRINT";
            break;
        case TokenType::READINT: string = "READINT";
            break;
        case TokenType::READSTR: string = "READSTR";
            break;
        case TokenType::INT: string = "INT";
            break;
        case TokenType::STRING: string = "STRING";
            break;
        case TokenType::BOOL: string = "BOOL";
            break;
        case TokenType::GREATER_THAN: string = "GREATER_THAN";
            break;
        case TokenType::GREATER_THAN_EQUAL: string = "GREATER_THAN_EQUAL";
            break;
        case TokenType::LESS_THAN: string = "LESS_THAN";
            break;
        case TokenType::LESS_THAN_EQUAL: string = "LESS_THAN_EQUAL";
            break;
        case TokenType::LPAREN: string = "LPAREN";
            break;
        case TokenType::LBRACKET: string = "LBRACKER";
            break;
        case TokenType::RPAREN: string = "RPAREN";
            break;
        case TokenType::RBRACKET: string = "RBRACKET";
            break;
        case TokenType::MULTIPLY: string = "MULTIPLY";
            break;
        case TokenType::DIVIDE: string = "DIVIDE";
            break;
        case TokenType::MINUS: string = "MINUS";
            break;
        case TokenType::PLUS: string = "PLUS";
            break;
        case TokenType::COMMA: string = "COMMA";
            break;
        case TokenType::SEMICOLON: string = "SEMICOLON";
            break;
        case TokenType::ASSIGN: string = "ASSIGN";
            break;
        case TokenType::EQUAL: string = "EQUAL";
            break;
        case TokenType::NOT: string = "NOT";
            break;
        case TokenType::AND: string = "AND";
            break;
        case TokenType::OR: string = "OR";
            break;
        case TokenType::THEN: string = "THEN";
            break;
        case TokenType::NOT_EQUAL: string = "NOT_EQUAL";
            break;
        case TokenType::ID: string = "ID";
            break;
    }
    std::cout << string << "{" << the_token.get_lexeme() << "} [" << the_token.get_line() << ", " <<the_token.get_column() << "]" << std::endl;
}
