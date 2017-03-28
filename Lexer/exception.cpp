//
//  exception.cpp
//  Lexer
//
//  Created by Jasmine Jans on 4/10/16.
//  Copyright © 2016 Jasmine Jans. All rights reserved.
//

#include "exception.h"

Exception::Exception(std::string msg, int line, int column, ExceptionType type)
: msg(msg), line(line), column(column), type(type)
{
}

const char* Exception::what() const throw()
{
    std::string result = "";
    if(type == ExceptionType::LEXER)
        result += "Lexical error at line ";
    else if(type == ExceptionType::PARSER)
        result += "Syntax error at line ";
        result += std::to_string((long long int)line);
        result += ", colum ";
        result += std::to_string((long long int)column);
        result += ": " + msg;
        return result.c_str();
}

Exception::~Exception() throw()
{
}


