#pragma once
#include "Token.h"
#include <queue>
#include <regex>

class Tokenizer {
public:
    std::string expr;
    std::queue<Token> tokens;

    Tokenizer(std::string &);

    std::queue<Token> tokenize();

    Token nextToken();
    Token parseOperatorToken(std::string);
    
private:
    enum class State {DEFAULT,POST,INFIXBINOP} state;
};