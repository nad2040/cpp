#include "ReadTokenizeParse.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

extern Expression *empty_list;
extern Expression *_false;
extern Expression *_true;
extern Expression *quote_symbol;

namespace {

bool isDelimiter(char c) { //treat ` and @ and "
    return (isspace(c) || (c == '(') || (c == ')'));
}

bool isSpecial(char c) { //treat ` and @ and "
    return (c == '\'') || (c == '(') || (c == ')');
}

std::string readTillDelimiter(std::string& buffer, int& idx) {
    int begin = idx;
    ++idx;
    while (idx < buffer.size()) {
        char c = buffer[idx];
        if (isDelimiter(c)) return buffer.substr(begin, idx-begin);
        ++idx;
    }
    return buffer.substr(begin);
}

std::string readStringToken(std::string& buffer, int& idx) {
    assert(buffer[idx] == '"');
    //do we need to handle \"
    int begin = idx;
    ++idx;
    while (idx < buffer.size()) {
        if (buffer[idx] == '"' && buffer[idx-1] != '\\') { 
            int count = idx-begin+1;
            ++idx;
            return buffer.substr(begin, count);
        }
        ++idx;
    }
    idx = begin;
    return "";
}

std::string nextToken(std::string& buffer, int& idx) {
    while (idx < buffer.size()) {
        char c = buffer[idx];
        if (isspace(c)) ++idx;
        else if (isSpecial(c)) { ++idx; return std::string(1, c); }
        else if (c == '"') return readStringToken(buffer, idx);
        else return readTillDelimiter(buffer, idx);
    }
    return "";
}

}

void ReadTokenizeParse::readAndTokenize() {
    //read
    std::string line;
    std::getline(std::cin, line);
    buffer_ += line;
    //tokenize
    while(true) {
        std::string token = nextToken(buffer_, tokenPos_);
        if (token.empty()) break;
        //std::cout << "add token:" << token << " token.size:" << token.size() << '\n';
        tokens_.push_back(token);
    }
    //dump tokens
    std::cout << "tokens:"; for(auto& elem : tokens_) std::cout << '_' << elem; std::cout << '\n';
}

void ReadTokenizeParse::readAndTokenize(std::istream& is) {
    //read
    std::string line;
    std::getline(is, line);
    buffer_ += line;
    //tokenize
    while(true) {
        std::string token = nextToken(buffer_, tokenPos_);
        if (token.empty()) break;
        //std::cout << "add token:" << token << " token.size:" << token.size() << '\n';
        tokens_.push_back(token);
    }
    //dump tokens
    std::cout << "tokens:"; for(auto& elem : tokens_) std::cout << '_' << elem; std::cout << '\n';
}

Expression* ReadTokenizeParse::parseCdr(int& index) {
    int oldReadPos = index;
    std::string ctoken = tokens_[index];
    std::cout << "current token:" << ctoken << " index:" << index << '\n';
    //first check empty list
    if (ctoken[0] == ')') {
        ++index;
        std::cout << "list reach end\n";
        return empty_list;
    }
    //parse car
    std::cout << "parse car current token:" << tokens_[index] << " index:" << index << '\n';
    Expression* first = parseExpression(index);
    if (!first) {
        index = oldReadPos;
        std::cout << "list car empty\n";
        return nullptr;
    }
    //parse cdr
    std::cout << "parse cdr current token:" << tokens_[index] << " index:" << index << '\n';
    Expression* rest = parseCdr(index);
    if (!rest) {
        index = oldReadPos; 
        std::cout << "list cdr empty\n";
        return nullptr;
    }
    //std::cout << "return from readCdrT, current token:" << tokens_[index] << " index:" << index << '\n'; //out of boundar 4, 'a, (* 6 7)
    return cons(first, rest);
}

Expression* ReadTokenizeParse::parseHash(int& index) {
    std::string ctoken = tokens_[index];
    if (ctoken == "#t") { ++index; return _true; }
    else if (ctoken == "#f") { ++index; return _false; }
    else if (ctoken == "#\\space") { ++index; return new Expression(Atom(' ')); }
    else if (ctoken == "#\\newline") { ++index; return new Expression(Atom('\n')); }
    else if (ctoken.size() == 3 && ctoken[1] == '\\') { ++index; return new Expression(Atom(ctoken[2])); }
    else {
        std::cerr << "discard unexpected " << ctoken << '\n';
        ++index;
        return nullptr;
    }
}

Expression* ReadTokenizeParse::parseExpression(int& index) {
    if (index == tokens_.size()) return nullptr;
    int base = index;
    std::string ctoken = tokens_[index];
    if (ctoken[0] == '(') {
        ++index; 
        Expression* expr = parseCdr(index); 
        if (expr) return expr; else { index = base; return nullptr; } 
    }
    else if (ctoken[0] == '"') {
        ++index;
        return new Expression(Atom(ctoken));
    }
    else if (ctoken[0] == '\'') { 
        ++index;
        Expression* expr = parseExpression(index);
        if (expr) return cons(quote_symbol, cons(expr, empty_list)); 
        else { --index; return nullptr; }
    }
    else if ((ctoken[0] == '-') && isdigit(ctoken[1]) || isdigit(ctoken[0])) {
        ++index;
        return new Expression(Atom((long)atoi(ctoken.c_str())));
    }
    else if (ctoken[0] == '#') return parseHash(index);
    else {
        ++index;
        return makeSymbol(ctoken);
    }
}

