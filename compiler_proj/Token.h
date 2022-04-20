#pragma once
#include <string>
#include <cassert>

enum TokenType {
    UNKNOWN = 0,
    NEWLINE = '\n',
    SPACE = ' ',
    DOUBLE_QUOTE = '"',
    SINGLE_QUOTE = '\'',
    OPEN_PAREN = '(',
    CLOSE_PAREN = ')',
    COMMA = ',',
    PERIOD = '.',
    FSLASH = '/',
    BSLASH = '\\',
    UNDERSCORE = '_',
    COLON = ':',
    SEMICOLON = ';',
    OPEN_DIAMOND = '<',
    CLOSE_DIAMOND = '>',
    QUESTION = '?',
    OPEN_BRAKET = '[',
    CLOSE_BRAKET = ']',
    OPEN_BRACE = '{',
    CLOSE_BRACE = '}',
    

    IDENTIFIER = 256,

    KEYWORD,

    // CONTROL FLOW
    FOR,WHILE,DO,CONTINUE, // loop
    IF,ELSE,SWITCH,CASE,DEFAULT, // conditional jumps
    LABEL,GOTO,BREAK,RETURN, // unconditional jumps
    
    // OPERATORS
    OPERATOR, // special keyword
    ASSIGN, // =
    LT,GT,LEQ,GEQ,EQ, // < > <= >= ==
    ADD,SUB,NEG,MUL,DIV,MOD, // + - -() * / %
    INCREMENT,DECREMENT, // ++ --
    AND,OR,NOT,XOR, // && || ! ^
    BITAND,BITOR,BITNOT,SHIFTL,SHIFTR, // & | ~ << >>

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
    TokenType token_type;
    std::string token_value;

    Token();
    Token(const std::string&, TokenType);

    bool is_keyword();
    bool is_operator();
    bool is_identifier();
    bool is_type();
    bool is_type_modifier();
    void set_type(TokenType);
};

template<typename First, typename ... T>
bool is_in(First &&first, T && ... t)
{
    return ((first == t) || ...);
}