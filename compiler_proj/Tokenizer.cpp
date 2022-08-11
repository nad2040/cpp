#include "Tokenizer.h"

Tokenizer::Tokenizer(std::string &expr) {
    this->expr = expr;
}

std::queue<Token> Tokenizer::tokenize() {
    std::queue<Token> tokens;
    Token t;
    while (1) {
        t=nextToken(expr);
        if (t.token_type == TokenType::WHITESPACE) continue;
        if (t.token_type == TokenType::FILE_END) break;
        tokens.push(t);
    }
    return tokens;
}

Token Tokenizer::nextToken(std::string &s) {
    std::smatch match;
    std::regex re;
    Token result;

    if (s.empty()) return Token(std::string(""), TokenType::FILE_END);

    re = std::regex(R"(^\s+)"); // match whitespace
    if (std::regex_search(s, match, re)) {
        result = Token(match.str(0), TokenType::WHITESPACE);
        s = s.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^[A-Za-z]+)"); // match identifier
    if (std::regex_search(s, match, re)) {
        result = Token(match.str(0), TokenType::IDENTIFIER);
        s = s.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^\d+)"); // match one or more digits
    if (std::regex_search(s, match, re)) {
        result = Token(match.str(0), TokenType::INT_LITERAL);
        s = s.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^\+)"); // match plus
    if (std::regex_search(s, match, re)) {
        result = Token(match.str(0), TokenType::PLUS);
        s = s.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^\-)"); // match minus
    if (std::regex_search(s, match, re)) {
        result = Token(match.str(0), TokenType::MINUS);
        s = s.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^\*)"); // match mult
    if (std::regex_search(s, match, re)) {
        result = Token(match.str(0), TokenType::MUL);
        s = s.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^\/)"); // match div
    if (std::regex_search(s, match, re)) {
        result = Token(match.str(0), TokenType::DIV);
        s = s.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^\()"); // match (
    if (std::regex_search(s, match, re)) {
        result = Token(match.str(0), TokenType::LEFT_PAREN);
        s = s.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^\))"); // match )
    if (std::regex_search(s, match, re)) {
        result = Token(match.str(0), TokenType::RIGHT_PAREN);
        s = s.substr(match.str(0).size());
        return result;
    }

    char c = s[0];
    s = s.substr(1);
    return Token(c, TokenType::UNKNOWN);
}


Token Tokenizer::parseOperatorToken(std::string &str) {
    return Token();
}