#pragma once
#include "Token.h"
#include <queue>
#include <regex>
#include <vector>

class Tokenizer {
public:
    std::string expr;
    std::queue<Token> tokens;

    Tokenizer(std::string &);

    std::queue<Token> tokenize();

    Token nextToken();
    Token parseOperatorToken(std::string);
    
private:
    std::string identifierPattern = "[_a-zA-Z][_a-zA-Z0-9]*";
    std::string numberPattern = "-?[0-9]+";
    std::string operatorPattern = "[\\+\\-\\*/\\(\\)]";
    std::string whitespacePattern = "[\\s]+";
    std::string commentPattern = "//.*";
    std::string charPattern = "'.'";

    struct TokenizerRule {
        TokenType tokentype;
        std::string pattern;
    };

    std::vector<TokenizerRule> rules = {
        {TokenType::IDENTIFIER, identifierPattern},
        {TokenType::INT_LITERAL, numberPattern},
        {TokenType::OPERATOR, operatorPattern},
        {TokenType::WHITESPACE, whitespacePattern},
        {TokenType::COMMENT, commentPattern},
        {TokenType::CHAR, charPattern}
    };
};