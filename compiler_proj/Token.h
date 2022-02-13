#pragma once
#include <string>

enum TokenType {
    NULL = 0,
    
    SPACE = ' ',
    DOUBLE_QUOTE = '"',
    SINGLE_QUOTE = '\'',
    OPEN_PAREN = '(',
    CLOSE_PAREN = ')',

    IDENTIFIER = 256,

    // KEYWORDS
    KEYWORD = 257,
    
    // OPERATORS
    OPERATOR,

    // TYPES
    BOOL,
    CHAR,
    INT,
    FLOAT,
    STRING
};

class Token {
public:
    TokenType token_type;
    std::string token_value;

    Token();
    Token(const std::string& str);

    bool isKeyword();
    bool isOperator();
    bool isIdentifier();
    bool isString();
    bool isConstant();
    
};