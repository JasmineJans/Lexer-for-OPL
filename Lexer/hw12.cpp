//
//  hw12.cpp
//  Lexer
//
//  Created by Jasmine Jans on 4/14/16.
//  Copyright © 2016 Jasmine Jans. All rights reserved.
//

#include "hw12.h"
#include <iostream>
#include <fstream>
#include <memory>
#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "exception.h"

//main file checks to make sure the parameters given is a txt file that is openable
int main(int argc, char *argv[]){
    if(argc < 2) {
        std::cout << "USAGE: " << argv[0] << " file" << std::endl;
        return -1;
    }
    
    std::ifstream file (argv[1]);
    
    if(!file.is_open()){
        std::cout << "ERROR: Unable to open '" << argv[1] << "'" << std::endl;
        return -1;
    }
    
    //try to create a lexer, and a parser with that lexer and then parse
    try {
        Lexer the_lexer(file);
        Parser the_parser(the_lexer);
        the_parser.parse();
    //catch any exception thrown and print it
    } catch(Exception e){
        std::cout << e.what() << std::endl;
    }
    file.close();
}
