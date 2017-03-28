//
//  lexer.cpp
//  Lexer
//
//  Created by Jasmine Jans on 4/10/16.
//  Copyright © 2016 Jasmine Jans. All rights reserved.
//

#include <istream>
#include <iostream>
#include <string>
#include <cstdio>
#include "token.h"
#include "lexer.h"
#include "exception.h"

Lexer::Lexer(std::istream& input_stream) :
input_stream(input_stream), line(1), column(0)
{
    
}

Token Lexer::next_token()
{
    if(input_stream.peek() == EOF){
        return Token(TokenType::EOS, "", line, column);
    }
    
    char symbol = input_stream.get();
    
    if(symbol == '\n'){
        column = 0;
        line++;
        return next_token();
    }
    
    if(symbol == ' ' || symbol == '\t') {
        column++;
        return next_token();
    }


    else if(symbol == '#'){
        while(input_stream.peek()!= '\n'){
            input_stream.get();
        }
        return next_token();
    }
    
    else if(symbol == '>'){
        symbol = input_stream.get();
        column++;
        if(symbol == '='){
            return Token(TokenType::GREATER_THAN_EQUAL, ">=", line, column);
        }
        else{
            input_stream.putback(symbol);
            column--;
            return Token(TokenType::GREATER_THAN, ">", line, column);
        }
    }
    
    else if(symbol == '<'){
        symbol = input_stream.get();
        column++;
        if(symbol == '='){
            return Token(TokenType::LESS_THAN_EQUAL, "<=", line, column);
        }
        else{
            input_stream.putback(symbol);
            column--;
            return Token(TokenType::LESS_THAN, "<", line, column);
        }
    }
    
    else if(symbol == ']'){
        column++;
        return Token(TokenType::RBRACKET, "]", line, column);
    }
    
    else if(symbol == '['){
        column++;
        return Token(TokenType::LBRACKET, "[", line, column);
    }
    
    else if(symbol == '('){
        column++;
        return Token(TokenType::LPAREN, "(", line, column);
    }
    
    else if(symbol == ')'){
        column++;
        return Token(TokenType::RPAREN, ")", line, column);
    }
    
    else if(symbol == '*'){
        column++;
        return Token(TokenType::MULTIPLY, "*", line, column);
    }
    
    else if(symbol == '/'){
        column++;
        return Token(TokenType::DIVIDE, "/", line, column);
    }
    
    else if(symbol == '+'){
        column++;
        return Token(TokenType::PLUS, "+", line, column);
    }
    
    else if(symbol == '-'){
        column++;
        return Token(TokenType::MINUS, "-", line, column);
    }
    
    else if(symbol == ';'){
        column++;
        return Token(TokenType::SEMICOLON, ";", line, column);
    }
    
    else if(symbol == '='){
        symbol = input_stream.get();
        column++;
        if(symbol == '=')
        {
            return Token(TokenType::EQUAL, "==", line, column);
        }
        input_stream.putback(symbol);
        column--;
        return Token(TokenType::ASSIGN, "=", line, column);
    }
    
    else if(symbol == '!'){
        char firstsymbol = symbol;
        symbol = input_stream.get();
        column++;
        if(symbol == '=')
        {
            return Token(TokenType::NOT_EQUAL, "!=", line, column);
        }
        std::string s = "Unexpected Symbol '";
        s += firstsymbol;
        s += "'";
        throw Exception(s, line, column, ExceptionType::LEXER);
    }
    
    else if(symbol == ','){
        column++;
        return Token(TokenType::COMMA, ",", line, column);
    }
    
    else if(isdigit(symbol)){
        std::string number = "";
        number += symbol;
        column++;
        int realcolumn = column;
        while(isdigit(input_stream.peek())){
            number += input_stream.get();
            column++;
        }
        if(isalpha(input_stream.peek()) || input_stream.peek() == '\n'){
            std::string s = "Expected Digit '";
            s += number;
            s += "'";
            throw Exception(s, line, column, ExceptionType::LEXER);
        }
        return Token(TokenType::INT, number, line, realcolumn);
    }
    
    else if(symbol == '\"'){
        column++;
        int realcolumn = column;
        symbol = input_stream.get();
        std::string string = "";
        string += symbol;
        while(input_stream.peek() != '\"'){
            if(input_stream.peek() == '\n' || input_stream.peek() == EOF){
                std::string s = "string can only be on one line '";
                s += string;
                s += "'";
                throw Exception(s, line, realcolumn, ExceptionType::LEXER);
            }
            string += input_stream.get();
            column++;
        }
        input_stream.get();
        column++;
        return Token(TokenType::STRING, string, line, realcolumn);
    }
    
    else if(symbol == 'r'){
        column++;
        int realcolumn = column;
        if(input_stream.peek() == 'e'){
            column++;
            input_stream.get();
            if(input_stream.peek() == 'a'){
                column++;
                input_stream.get();
                if(input_stream.peek() == 'd'){
                    column++;
                    input_stream.get();
                    if(input_stream.peek() == 'i'){
                        column++;
                        input_stream.get();
                        if(input_stream.peek() == 'n'){
                            column++;
                            input_stream.get();
                            if(input_stream.peek() == 't'){
                                column++;
                                input_stream.get();
                                return Token(TokenType::READINT, "readint", line, realcolumn);
                            }
                            else{
                                input_stream.putback('n');
                                input_stream.putback('i');
                                input_stream.putback('d');
                                input_stream.putback('a');
                                input_stream.putback('e');
                                column -= 5;
                                return id_token(symbol);
                            }
                        }
                        else{
                            input_stream.putback('i');
                            input_stream.putback('d');
                            input_stream.putback('a');
                            input_stream.putback('e');
                            column -= 4;
                            return id_token(symbol);
                        }
                    }
                    else if(input_stream.peek() == 's'){
                        column++;
                        input_stream.get();
                        if(input_stream.peek() == 't'){
                            column++;
                            input_stream.get();
                            if(input_stream.peek() == 'r'){
                                column++;
                                input_stream.get();
                                return Token(TokenType::READSTR, "readint", line, realcolumn);
                            }
                            else{
                                input_stream.putback('t');
                                input_stream.putback('s');
                                input_stream.putback('d');
                                input_stream.putback('a');
                                input_stream.putback('e');
                                column -= 5;
                                return id_token(symbol);
                            }
                        }
                        else{
                            input_stream.putback('s');
                            input_stream.putback('d');
                            input_stream.putback('a');
                            input_stream.putback('e');
                            column -= 4;
                            return id_token(symbol);
                        }
                    }
                    else{
                        input_stream.putback('d');
                        input_stream.putback('a');
                        input_stream.putback('e');
                        column -= 3;
                        return id_token(symbol);
                    }
                }
                else{
                    input_stream.putback('a');
                    input_stream.putback('e');
                    column -= 2;
                    return id_token(symbol);
                }
            }
            else{
                input_stream.putback('e');
                column -= 1;
                return id_token(symbol);
            }
        }
        else{
            return id_token(symbol);
        }
    }

    else if(symbol == 'p'){
        column++;
        int realcolumn = column;
        if(input_stream.peek() == 'r'){
            column++;
            input_stream.get();
            if(input_stream.peek() == 'i'){
                column++;
                input_stream.get();
                if(input_stream.peek() == 'n'){
                    column++;
                    input_stream.get();
                    if(input_stream.peek() == 't'){
                        column++;
                        input_stream.get();
                        if(input_stream.peek() == 'l'){
                            column++;
                            input_stream.get();
                            if(input_stream.peek() == 'n'){
                                column++;
                                input_stream.get();
                                return Token(TokenType::PRINTLN, "println", line, realcolumn);
                            }
                            else{
                                input_stream.putback('l');
                                input_stream.putback('t');
                                input_stream.putback('n');
                                input_stream.putback('i');
                                input_stream.putback('r');
                                column -= 5;
                                return id_token(symbol);
                            }
                        }
                        else{
                            return Token(TokenType::PRINT, "print", line, realcolumn);
                        }
                    }
                    else{
                        input_stream.putback('n');
                        input_stream.putback('i');
                        input_stream.putback('r');
                        column -= 3;
                        return id_token(symbol);
                    }
                }
                else{
                    input_stream.putback('i');
                    input_stream.putback('r');
                    column -= 2;
                    return id_token(symbol);
                }
            }
            else{
                input_stream.putback('r');
                column -= 1;
                return id_token(symbol);
            }
        }
        else{
            return id_token(symbol);
        }
    }
    
    else if(symbol == 'i'){
        column ++;
        if(input_stream.peek() == 'f'){
            column++;
            input_stream.get();
            return Token(TokenType::IF, "if", line, column);
        }
        return id_token(symbol);
    }
    
    else if(symbol == 'd'){
        column ++;
        if(input_stream.peek() == 'o'){
            column++;
            input_stream.get();
            return Token(TokenType::DO, "do", line, column);
        }
        return id_token(symbol);
    }
    
    else if(symbol == 'e'){
        column ++;
        if(input_stream.peek() == 'l'){
            column++;
            input_stream.get();
            if(input_stream.peek() == 'i'){
                column++;
                input_stream.get();
                if(input_stream.peek() == 'f'){
                    column++;
                    input_stream.get();
                    return Token(TokenType::ELIF, "elif", line, column);
                }
                else{
                    input_stream.putback('i');
                    input_stream.putback('l');
                    column -= 2;
                    return id_token(symbol);
                }
            }
            else if(input_stream.peek() == 's'){
                column++;
                input_stream.get();
                if(input_stream.peek() == 'e'){
                    column++;
                    input_stream.get();
                    return Token(TokenType::ELSE, "else", line, column);
                }
                else{
                    input_stream.putback('s');
                    input_stream.putback('l');
                    column -= 2;
                    return id_token(symbol);
                }
            }
            else{
                input_stream.putback('l');
                column -= 1;
                return id_token(symbol);
            }
        }
        else if(input_stream.peek() == 'n'){
            column++;
            input_stream.get();
            if(input_stream.peek() == 'd'){
                column++;
                input_stream.get();
                return Token(TokenType::END, "end", line, column);
            }
            else{
                input_stream.putback('n');
                column -= 1;
                return id_token(symbol);
            }
        }
        else{
            return id_token(symbol);
        }
    }
    
    else if(symbol == 'w'){
        column ++;
        if(input_stream.peek() == 'h'){
            column++;
            input_stream.get();
            if(input_stream.peek() == 'i'){
                column++;
                input_stream.get();
                if(input_stream.peek() == 'l'){
                    column++;
                    input_stream.get();
                    if(input_stream.peek() == 'e'){
                        column++;
                        input_stream.get();
                        return Token(TokenType::WHILE, "while", line, column);
                    }
                    else{
                        input_stream.putback('l');
                        input_stream.putback('i');
                        input_stream.putback('h');
                        column -= 3;
                        return id_token(symbol);
                    }
                }
                else{
                    input_stream.putback('i');
                    input_stream.putback('h');
                    column -= 2;
                    return id_token(symbol);
                }
            }
            else{
                input_stream.putback('h');
                column -= 1;
                return id_token(symbol);
            }
        }
        else{
            return id_token(symbol);
        }
    }
    else if(symbol == 'o'){
        column ++;
        if(input_stream.peek() == 'r'){
            column++;
            input_stream.get();
            return Token(TokenType::OR, "or", line, column);
        }
        return id_token(symbol);
    }
    
    else if(symbol == 'f'){
        column ++;
        if(input_stream.peek() == 'a'){
            column++;
            input_stream.get();
            if(input_stream.peek() == 'l'){
                column++;
                input_stream.get();
                if(input_stream.peek() == 's'){
                    column++;
                    input_stream.get();
                    if(input_stream.peek() == 'e'){
                        column++;
                        input_stream.get();
                        return Token(TokenType::BOOL, "false", line, column);
                    }
                    else{
                        input_stream.putback('s');
                        input_stream.putback('l');
                        input_stream.putback('a');
                        column -= 3;
                        return id_token(symbol);
                    }
                }
                else{
                    input_stream.putback('l');
                    input_stream.putback('a');
                    column -= 2;
                    return id_token(symbol);
                }
            }
            else{
                input_stream.putback('a');
                column -= 1;
                return id_token(symbol);
            }
        }
        else{
            return id_token(symbol);
        }
    }
    
    else if(symbol == 't'){
        column ++;
        if(input_stream.peek() == 'r'){
            column++;
            input_stream.get();
            if(input_stream.peek() == 'u'){
                column++;
                input_stream.get();
                if(input_stream.peek() == 'e'){
                    column++;
                    input_stream.get();
                    return Token(TokenType::BOOL, "true", line, column);
                }
                else{
                    input_stream.putback('u');
                    input_stream.putback('r');
                    column -= 2;
                    return id_token(symbol);
                }
            }
            else{
                input_stream.putback('r');
                column -= 1;
                return id_token(symbol);
            }
        }
        else if(input_stream.peek() == 'h'){
            column++;
            input_stream.get();
            if(input_stream.peek() == 'e'){
                column++;
                input_stream.get();
                if(input_stream.peek() == 'n'){
                    column++;
                    input_stream.get();
                    return Token(TokenType::THEN, "then", line, column);
                }
                else{
                    input_stream.putback('e');
                    input_stream.putback('h');
                    column -= 2;
                    return id_token(symbol);
                }
            }
            else{
                input_stream.putback('h');
                column -= 1;
                return id_token(symbol);
            }
        }
        else{
            return id_token(symbol);
        }
    }
    
    else if(symbol == 'n'){
        column ++;
        if(input_stream.peek() == 'o'){
            column++;
            input_stream.get();
            if(input_stream.peek() == 't'){
                column++;
                input_stream.get();
                return Token(TokenType::NOT, "not", line, column);
            }
            else{
                input_stream.putback('o');
                column -= 1;
                return id_token(symbol);
            }
        }
        else{
            return id_token(symbol);
        }
    }
    
    else if(symbol == 'a'){
        column ++;
        if(input_stream.peek() == 'n'){
            column++;
            input_stream.get();
            if(input_stream.peek() == 'd'){
                column++;
                input_stream.get();
                return Token(TokenType::AND, "and", line, column);
            }
            else{
                input_stream.putback('n');
                column -= 1;
                return id_token(symbol);
            }
        }
        else{
            return id_token(symbol);
        }
    }
    
    else{
        if(isdigit(symbol)){
            std::string s = "Unexpected Symbol '";
            s += symbol;
            s += "'";
            throw Exception(s, line, column, ExceptionType::LEXER);
        }
        
        return id_token(symbol);
    }
    
    
    return id_token(symbol);
}


Token Lexer::id_token(char symbol)
{
    std::string value = "";
    value += symbol;
    while(isalnum(input_stream.peek()) || input_stream.peek() == '_'){
        column++;
        value += input_stream.get();
        if(input_stream.peek() == '\n'){
            column++;
            std::string s = "ERROR '";
            s += symbol;
            s += "'";
            throw Exception(s, line, column, ExceptionType::LEXER);
        }
    }
    return Token(TokenType::ID, value, line, column);
}
