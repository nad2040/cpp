#include "Token.h"

Token::Token() : token_value(std::string()), token_type(TokenType::UNKNOWN) {}
Token::Token(std::string str, TokenType type) : token_value(str), token_type(type) {}
Token::Token(char c, TokenType type) : token_value(std::string(c,1)), token_type(type) {}

void Token::set_type(TokenType type) { token_type = type; }

bool Token::is_keyword() {
    assert(token_type != TokenType::UNKNOWN);
    return is_in(token_type,
        TokenType::KEYWORD,
        TokenType::FOR,
        TokenType::WHILE,
        TokenType::DO,
        TokenType::CONTINUE,
        TokenType::IF,
        TokenType::ELSE,
        TokenType::SWITCH,
        TokenType::CASE,
        TokenType::DEFAULT,
        TokenType::LABEL,
        TokenType::GOTO,
        TokenType::BREAK,
        TokenType::RETURN,
        TokenType::OPERATOR
    );
}
bool Token::is_operator() {
    assert(token_type != TokenType::UNKNOWN);
    return is_in(token_type,
        TokenType::OPERATOR,
        TokenType::ADDRESS,
        TokenType::DEREF,
        TokenType::MEMBER,
        TokenType::DEREF_MEMBER,
        TokenType::ASSIGN,
        TokenType::ADD_ASSIGN,
        TokenType::SUB_ASSIGN,
        TokenType::MUL_ASSIGN,
        TokenType::DIV_ASSIGN,
        TokenType::MOD_ASSIGN,
        TokenType::INCREMENT,
        TokenType::DECREMENT,
        TokenType::ADD,
        TokenType::SUB,
        TokenType::MUL,
        TokenType::DIV,
        TokenType::MOD,
        TokenType::UNARY_PLUS,
        TokenType::UNARY_MINUS,
        TokenType::LT,
        TokenType::GT,
        TokenType::LEQ,
        TokenType::GEQ,
        TokenType::EQ,
        TokenType::NEQ,
        TokenType::AND,
        TokenType::OR,
        TokenType::NOT,
        TokenType::XOR,
        TokenType::BITAND,
        TokenType::BITOR,
        TokenType::BITNOT,
        TokenType::LSHF,
        TokenType::RSHF
    );
}
bool Token::is_identifier() {
    assert(token_type != TokenType::UNKNOWN);
    return token_type == TokenType::IDENTIFIER;
}
bool Token::is_type() {
    assert(token_type != TokenType::UNKNOWN);
    return is_in(token_type,
        TokenType::VAR,
        TokenType::VOID,
        TokenType::BOOL,
        TokenType::BYTE,
        TokenType::SHORT,
        TokenType::INT,
        TokenType::LONG,
        TokenType::FLOAT,
        TokenType::DOUBLE,
        TokenType::CHAR,
        TokenType::STRING,
        TokenType::FN,
        TokenType::CLASS
    );
}
bool Token::is_type_modifier() {
    assert(token_type != TokenType::UNKNOWN);
    return is_in(token_type,
        TokenType::CONST,
        TokenType::STATIC,
        TokenType::PRIVATE
    );
}
int Token::precedence() {
    switch (token_type) {
        case TokenType::ADD:
        case TokenType::SUB:
            return 1;
        case TokenType::MUL:
        case TokenType::DIV:
            return 2;
        default: return -1;
    }
}
Associative Token::associativity() {
    return Associative::LEFT;
}

std::ostream& operator<<(std::ostream &out, Token token) {
    switch (token.token_type) {
        case TokenType::UNKNOWN:
            out << "UNK";
            return out;
        case TokenType::FILE_END:
            out << "EOF";
            return out;
        case TokenType::WHITESPACE:
            out << "WS";
            return out;
        case TokenType::INT_LITERAL:
            out << "IntLiteral: " << token.token_value;
            return out;
        case TokenType::IDENTIFIER:
            out << "Identifier: " << token.token_value;
            return out;
        case TokenType::LEFT_PAREN:
            out << "LeftParen";
            return out;
        case TokenType::RIGHT_PAREN:
            out << "RightParen";
            return out;
        default:
            out << token.token_value;
            return out;
    }
}
