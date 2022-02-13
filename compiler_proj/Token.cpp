#include "Token.h"

Token::Token() : token_type(), token_value() {}
Token::Token(const std::string& str) : token_value(str) {
    // SET ALL TOKEN TYPES HERE
    
}

bool Token::isKeyword() {

}
bool Token::isOperator() {

}
bool Token::isIdentifier() {

}
bool Token::isString() {

}
bool Token::isConstant() {

}