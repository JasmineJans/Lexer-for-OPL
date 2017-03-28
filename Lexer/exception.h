//
//  Exception.h
//  Lexer
//
//  Created by Jasmine Jans on 4/10/16.
//  Copyright © 2016 Jasmine Jans. All rights reserved.
//

#ifndef Exception_h
#define Exception_h

#include <exception>
#include <string>

enum class ExceptionType {
    LEXER, PARSER
};

class Exception : public std::exception
{
public:
    Exception(std::string msg, int line, int column, ExceptionType type);
    virtual const char* what() const throw();
    ~Exception() throw();
    
private:
    std::string msg;
    int line;
    int column;
    ExceptionType type;
};

#endif /* exception_h */
