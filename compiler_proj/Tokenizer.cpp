#include "Tokenizer.h"

Tokenizer::Tokenizer(std::string &expr) : expr(expr) {}

std::queue<Token> Tokenizer::tokenize() {
    Token t;
    while (1) {
        t=nextToken();
        if (t.token_type == TokenType::WHITESPACE) continue;
        if (t.token_type == TokenType::FILE_END) break;
        tokens.push(t);
    }
    return tokens;
}

Token Tokenizer::nextToken() {
    std::smatch match;
    std::regex re;
    Token result;

    if (expr.empty()) return Token(std::string(""), TokenType::FILE_END);
    
    re = std::regex(R"(^\()"); // match (
    if (std::regex_search(expr, match, re)) {
        result = Token(match.str(0), TokenType::LEFT_PAREN);
        expr = expr.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^\))"); // match )
    if (std::regex_search(expr, match, re)) {
        result = Token(match.str(0), TokenType::RIGHT_PAREN);
        expr = expr.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^\[)"); // match [
    if (std::regex_search(expr, match, re)) {
        result = Token(match.str(0), TokenType::LEFT_SQUARE_B);
        expr = expr.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^\])"); // match ]
    if (std::regex_search(expr, match, re)) {
        result = Token(match.str(0), TokenType::RIGHT_SQUARE_B);
        expr = expr.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^{)"); // match {
    if (std::regex_search(expr, match, re)) {
        result = Token(match.str(0), TokenType::LEFT_SQUARE_B);
        expr = expr.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^})"); // match }
    if (std::regex_search(expr, match, re)) {
        result = Token(match.str(0), TokenType::RIGHT_SQUARE_B);
        expr = expr.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^([<>%^&*\/=|.,;]|->|<<|>>|\*\*|\|\||&&|--|\+\+|[-+*|&%\/=]=))"); // match binary operator
    if (std::regex_search(expr, match, re)) {
        result = parseOperatorToken(match.str(0));
        expr = expr.substr(match.str(0).size());
    }
    re = std::regex(R"(^[A-Za-z][0-9A-Za-z]+)"); // match identifier
    if (std::regex_search(expr, match, re)) {
        state = State::INFIXBINOP;
        result = Token(match.str(0), TokenType::IDENTIFIER);
        expr = expr.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?)"); // match number
    if (std::regex_search(expr, match, re)) {
        state = State::INFIXBINOP;
        result = Token(match.str(0), TokenType::INT_LITERAL);
        expr = expr.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^\s+)"); // match whitespace
    if (std::regex_search(expr, match, re)) {
        result = Token(match.str(0), TokenType::WHITESPACE);
        expr = expr.substr(match.str(0).size());
        return result;
    }

    char c = expr[0];
    expr = expr.substr(1);
    return Token(c, TokenType::UNKNOWN);
}


Token Tokenizer::parseOperatorToken(std::string str) {
    if (str == "operator") return Token(str, TokenType::OPERATOR);
    else if (str == "&") return Token("ADDRESS", TokenType::ADDRESS);
    else if (str == "*") return Token("DEREF", TokenType::DEREF);
    else if (str == ".") return Token("MEMBER", TokenType::MEMBER);
    else if (str == "->") return Token("DEREF_MEMBER", TokenType::DEREF_MEMBER);
    else if (str == "=") return Token("ASSIGN", TokenType::ASSIGN);
    else if (str == "+=") return Token("ADD_ASSIGN", TokenType::ADD_ASSIGN);
    else if (str == "-=") return Token("SUB_ASSIGN", TokenType::SUB_ASSIGN);
    else if (str == "*=") return Token("MUL_ASSIGN", TokenType::MUL_ASSIGN);
    else if (str == "/=") return Token("DIV_ASSIGN", TokenType::DIV_ASSIGN);
    else if (str == "%=") return Token("MOD_ASSIGN", TokenType::MOD_ASSIGN);
    else if (str == "/") return Token("DIV", TokenType::DIV);
    else if (str == "%") return Token("MOD", TokenType::MOD);
    else if (str == "<") return Token("LESS_THAN", TokenType::LT);
    else if (str == ">") return Token("GREATER_THAN", TokenType::GT);
    else if (str == "<=") return Token("LESS_EQ", TokenType::LEQ);
    else if (str == ">=") return Token("GREATER_EQ", TokenType::GEQ);
    else if (str == "==") return Token("EQ", TokenType::EQ);
    else if (str == "!=") return Token("NOT_EQ", TokenType::NEQ);
    else if (str == "&&") return Token("LOGICAL_AND", TokenType::AND);
    else if (str == "||") return Token("LOGICAL_OR", TokenType::OR);
    else if (str == "^") return Token("BITWISE_XOR", TokenType::XOR);
    else if (str == "&") return Token("BITWISE_AND", TokenType::BITAND);
    else if (str == "|") return Token("BITWISE_OR", TokenType::BITOR);
    else if (str == "<<") return Token("LEFT_SHIFT", TokenType::LSHF);
    else if (str == ">>") return Token("RIGHT_SHIFT", TokenType::RSHF);
    else return Token("", TokenType::UNKNOWN);
}