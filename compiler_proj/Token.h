#pragma once
#include <string>
#include <cassert>
#include <iostream>

enum class TokenType : short {
    UNKNOWN = 0,
    NEWLINE,
    WHITESPACE,
    FILE_END,
    DOUBLE_QUOTE,
    SINGLE_QUOTE,
    LEFT_PAREN,
    RIGHT_PAREN,
    COMMA,
    DOT,
    F_SLASH,
    B_SLASH,
    UNDERSCORE,
    COLON,
    SEMICOLON,
    LEFT_ANGLE_B,
    RIGHT_ANGLE_B,
    QUESTION,
    LEFT_SQUARE_B,
    RIGHT_SQUARE_B,
    LEFT_CURLY_B,
    RIGHT_CURLY_B,

    IDENTIFIER = 256,
    LITERAL,
    INT_LITERAL,
    CHAR_LITERAL,
    STRING_LITERAL,

    KEYWORD,

    // CONTROL FLOW
    FOR,WHILE,DO,CONTINUE, // loop
    IF,ELSE,SWITCH,CASE,DEFAULT, // conditional jumps
    LABEL,GOTO,BREAK,RETURN, // unconditional jumps
    
    // OPERATORS
    OP,
    OPERATOR, // special keyword
    ASSIGN, // =
    LT,GT,LEQ,GEQ,EQ,NEQ, // < > <= >= == !=
    PLUS,MINUS,MUL,DIV,MOD, // + - -() * / %
    INCREMENT,DECREMENT, // ++ --
    AND,OR,NOT,XOR, // && || ! ^
    BITAND,BITOR,BITNOT,LSHF,RSHF, // & | ~ << >>

    // TYPES, CLASSES, MODIFIERS
    VAR,VOID, // special type
    BOOL, // boolean type
    BYTE,SHORT,INT,LONG, // integral type
    FLOAT,DOUBLE, // floating point type
    CHAR,STRING, // text type
    FN, // function type
    CLASS, // class type
    CONST,STATIC,PRIVATE // type modifiers
};

class Token {
public:
    std::string token_value;
    TokenType token_type;

    Token();
    Token(std::string, TokenType);
    Token(char, TokenType);

    bool is_keyword();
    bool is_operator();
    bool is_identifier();
    bool is_type();
    bool is_type_modifier();
    int precedence();

    void set_type(TokenType);

    friend std::ostream& operator<<(std::ostream &out, Token token);
};

template<typename T, typename ...Ts>
bool is_in(T &&check, Ts &&...list) {
    return ((check == list) || ...);
}