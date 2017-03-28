//
//  parser.cpp
//  Lexer
//
//  Created by Jasmine Jans on 4/14/16.
//  Copyright © 2016 Jasmine Jans. All rights reserved.
//

#include <iostream>
#include <string>
#include <memory>
#include "token.h"
#include "lexer.h"
#include "exception.h"
#include "parser.h"

Parser::Parser(Lexer& lexer):lexer(lexer), current_token(TokenType::EOS, "", 0, 0)
{
}

//sets current token to the nxt token gotten by the lexer
void Parser::advance()
{
    current_token = lexer.next_token();
}

//eats the current token by advancing to the next token or throwing an error if the parameter token
//type and current token type dont match
void Parser::eat(TokenType token_type, const std::string& msg)
{
    if(token_type == current_token.get_type())
        advance();
    else
        error(msg);
}

//boolean checks if the given token type is the token type of the current token
bool Parser::curr_token_type(TokenType token_type)
{
    return current_token.get_type() == token_type;
}

//error method that throws a parser error with the given message when called
void Parser:: error(const std::string& msg)
{
    std::string error_str = msg + " found '" + current_token.get_lexeme() + "'";
    int line = current_token.get_line();
    int column = current_token.get_column();
    throw Exception(error_str, line, column, ExceptionType::PARSER);
}

//calls advance to the next token and runs the non terminal stmts as a start and then eats an
//EOS once stmts has ended
void Parser::parse()
{
    advance();
    stmts();
    eat(TokenType::EOS, "expepecting end of file, ");
}

//checks what kind of statement the token stream is creating if any
void Parser::stmt(){
    if(curr_token_type(TokenType::PRINT) || curr_token_type(TokenType::PRINTLN)){
        output();
    }
    else if(curr_token_type(TokenType::ID)){
        assign();
    }
    else if(curr_token_type(TokenType::IF)){
        cond();
    }
    else if(curr_token_type(TokenType::WHILE)){
        loop();
    }
    else{
        error("Not a valid statement");
    }
}

//checks if the token stream is creating a statment
void Parser::stmts(){
    if(curr_token_type(TokenType::PRINT) || curr_token_type(TokenType::PRINTLN)){
        stmt();
        stmts();
    }
    else if(curr_token_type(TokenType::ID)){
        stmt();
        stmts();
    }
    else if(curr_token_type(TokenType::IF)){
        stmt();
        stmts();
    }
    else if(curr_token_type(TokenType::WHILE)){
        stmt();
        stmts();
    }
}

//checks for a correct output grammar
void Parser::output(){
    if(curr_token_type(TokenType::PRINT)){
        advance();
        eat(TokenType::LPAREN, "Expected symbol: (");
        expr();
        eat(TokenType::RPAREN, "Expected Symbol: )");
        eat(TokenType::SEMICOLON, "Expected Symbol: ;");
    }
    else if(curr_token_type(TokenType::PRINTLN)){
        advance();
        eat(TokenType::LPAREN, "Expected symbol: (");
        expr();
        eat(TokenType::RPAREN, "Expected Symbol: )");
        eat(TokenType::SEMICOLON, "Expected Symbol: ;");
    }
    else{
        error("Expecting output tokens");
    }
}

//checks for a correct input grammar
void Parser::input(){
    if(curr_token_type(TokenType::READINT)){
        advance();
        eat(TokenType::LPAREN, "Expected symbol: (");
        eat(TokenType::STRING, "Expected String");
        eat(TokenType::RPAREN, "Expected Symbol: )");
    }
    else if(curr_token_type(TokenType::READSTR)){
        advance();
        eat(TokenType::LPAREN, "Expected symbol: (");
        eat(TokenType::STRING, "Expected String");
        eat(TokenType::RPAREN, "Expected Symbol: )");
    }
    else{
        error("Expecting input tokens");
    }
}

//checks for a correct assignment grammar
void Parser::assign(){
    if(curr_token_type(TokenType::ID)){
        advance();
        listindex();
        eat(TokenType::ASSIGN, "Expecting symbol: =");
        expr();
        eat(TokenType::SEMICOLON, "Expecting symbol: ;");
    }
    else{
        error("Expecting assignment");
    }
}

//checks for a correct list construction
void Parser::listindex(){
    if(curr_token_type(TokenType::LBRACKET)){
        advance();
        expr();
        eat(TokenType::RBRACKET, "Expected symbol: ]");
    }
}

//checks for an expression
void Parser::expr(){
    value();
    exprt();
}

//keeps going to more expressions if there is a math operator
void Parser::exprt(){
    if(math_rel()){
        expr();
    }
}

//checks for a valid value grammar (a string, bool, int or list)
void Parser::value(){
    if(curr_token_type(TokenType::ID)){
        advance();
        listindex();
    }
    else if(curr_token_type(TokenType::STRING) || curr_token_type(TokenType::INT) || curr_token_type(TokenType::BOOL)){
        advance();
    }
    else if(curr_token_type(TokenType::LBRACKET)){
        advance();
        exprlist();
        eat(TokenType::RBRACKET, "Symbol expected: ]");
    }
    else if(curr_token_type(TokenType::READINT) || curr_token_type(TokenType::READSTR)){
        input();
    }
    else{
        error("Expecting value");
    }
}

//checks for a valid expression for within a list
void Parser::exprlist(){
    if(curr_token_type(TokenType::ID) || curr_token_type(TokenType::INT) || curr_token_type(TokenType::STRING) || curr_token_type(TokenType::BOOL)){
        expr();
        exprtail();
    }
}

//if there are commas it continues in a list so it has correct syntax
void Parser::exprtail(){
    if(curr_token_type(TokenType::COMMA)){
        advance();
        expr();
        exprtail();
    }
}

//checks to see if the token is a mathematical operation
bool Parser::math_rel(){
    if(curr_token_type(TokenType::PLUS) || curr_token_type(TokenType::MINUS) || curr_token_type(TokenType::DIVIDE) || curr_token_type(TokenType::MULTIPLY)){
        advance();
        return true;
    }
    return false;
}

//checks for a correct beginnning of a conditionl statment
void Parser::cond(){
    if(curr_token_type(TokenType::IF)){
        advance();
        bexpr();
        eat(TokenType::THEN, "No then found");
        stmts();
        condt();
        eat(TokenType::END, "not end found");
    }
    else{
        error("Expecting Conditional");
    }
}

//checks for either an elif or else at the end of a conditional statment
void Parser::condt(){
    if(curr_token_type(TokenType::ELIF)){
        advance();
        bexpr();
        eat(TokenType::THEN, "no then found");
        stmts();
        condt();
    }
    else if(curr_token_type(TokenType::ELSE)){
        advance();
        stmts();
    }
}

//checks for a correct boolean expression
void Parser::bexpr(){
    if(curr_token_type(TokenType::ID) || curr_token_type(TokenType::INT) || curr_token_type(TokenType::STRING) || curr_token_type(TokenType::BOOL)){
        expr();
        bexprt();
    }
    else if(curr_token_type(TokenType::NOT)){
        eat(TokenType::NOT, "Expecting not");
        expr();
        bexprt();
    }
    else{
        error("Expecting bool expression");
    }
}

//checks to see if the boolean expression continues with boolean connectors
void Parser::bexprt(){
    if(bool_rel()){
        expr();
        bconnct();
    }
}

//checks for correct boolean connectors if any
void Parser::bconnct(){
    if(curr_token_type(TokenType::AND)){
        advance();
        bexpr();
    }
    else if(curr_token_type(TokenType::OR)){
        advance();
        bexpr();
    }
}

//returns true if the current token is a boolean operator
bool Parser::bool_rel(){
    if(curr_token_type(TokenType::EQUAL) || curr_token_type(TokenType::LESS_THAN) || curr_token_type(TokenType::LESS_THAN_EQUAL) || curr_token_type(TokenType::GREATER_THAN) || curr_token_type(TokenType::GREATER_THAN_EQUAL) || curr_token_type(TokenType::NOT_EQUAL)){
        advance();
        return true;
    }
    else{
        return false;
    }
}

//checks for a correct loop statment
void Parser::loop(){
    if(curr_token_type(TokenType::WHILE)){
        advance();
        bexpr();
        eat(TokenType::DO, "no do found");
        stmts();
        eat(TokenType::END, "no end found");
    }
    else{
        error("excepting loop expression");
    }
}