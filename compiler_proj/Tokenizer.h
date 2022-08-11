#pragma once
#include "Token.h"
#include <queue>
#include <regex>

class Tokenizer {
public:
    std::string expr;

    Tokenizer(std::string &);

    std::queue<Token> tokenize();

    Token nextToken(std::string &);
    Token parseOperatorToken(std::string &);
    
};