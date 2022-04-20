#include "Token.h"

Token::Token() : token_type(), token_value(0) {}
Token::Token(const std::string& str, TokenType type) : token_value(str), token_type(type) {}

void Token::set_type(TokenType type) { token_type = type; }

bool Token::is_keyword() {
    assert(token_type != UNKNOWN);
    return is_in(token_type,
        KEYWORD,
        FOR,WHILE,DO,CONTINUE,
        IF,ELSE,SWITCH,CASE,DEFAULT,
        LABEL,GOTO,BREAK,RETURN,
        OPERATOR
    );
}
bool Token::is_operator() {
    assert(token_type != UNKNOWN);
    return is_in(token_type,
        ASSIGN,
        LT,GT,LEQ,GEQ,EQ,
        ADD,SUB,NEG,MUL,DIV,MOD,
        INCREMENT,DECREMENT,
        AND,OR,NOT,XOR,
        BITAND,BITOR,BITNOT,SHIFTL,SHIFTR
    );
}
bool Token::is_identifier() {
    assert(token_type != UNKNOWN);
    return token_type == IDENTIFIER;
}
bool Token::is_type() {
    assert(token_type != UNKNOWN);
    return is_in(token_type,
        VAR,VOID,
        BOOL,
        BYTE,SHORT,INT,LONG,
        FLOAT,DOUBLE,
        CHAR,STRING,
        FN,
        CLASS
    );
}
bool Token::is_type_modifier() {
    assert(token_type != UNKNOWN);
    return is_in(token_type, CONST,STATIC,PRIVATE);
}