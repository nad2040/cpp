#include "BufferReader.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

extern Expression *empty_list;
extern Expression *_false;
extern Expression *_true;
extern Expression *quote_symbol;

void BufferReader::readBuffer() {
    std::string line;
    std::getline(std::cin, line);
    buffer_ += line;
}

int listEnd(std::string& buffer, int pos) {
    assert(buffer[pos] == '(');
    int idx = pos+1;
    int count = 1;
    while (idx < buffer.size()) {
        if (buffer[idx] == '(') ++count;
        else if (buffer[idx] == ')') --count;
        if (count == 0) return ++idx;
        ++idx;
    }
    return pos;
}

int stringEnd(std::string& buffer, int pos) {
    assert(buffer[pos] == '"');
    int idx = pos+1;
    //do we need to handle \"
    while (idx < buffer.size()) {
        if (buffer[idx] == '"' && buffer[idx-1] != '\\') return ++idx;
        ++idx;
    }
    return pos;
}

int atomEnd(std::string& buffer, int pos) {
    assert(!isspace(buffer[pos]));
    int idx = pos+1;
    while (idx < buffer.size() && !isspace(buffer[idx])) ++idx;
    return idx;
}

Expression* BufferReader::parseList(const std::string& buffer) {
    //parse (), (car . cdr), or list (car (cdr))
    //first check empty list
    //read car
    //if . read cdr
    //read pair
    return new Expression(Atom(buffer));
}

Expression* BufferReader::readList() {
    assert(buffer_[readPos_] == '(');
    int listBeg = readPos_;
    int listEnd = ::listEnd(buffer_, listBeg);
    //std::cout << "list begin:" << listBeg << " end:" << listEnd << '\n';
    if (listBeg != listEnd) {
        readPos_ = listEnd;
        return parseList(buffer_.substr(listBeg, listEnd));
    }
    return nullptr;
}

Expression* BufferReader::readString() {
    assert(buffer_[readPos_] == '"');
    int stringBeg = readPos_;
    int stringEnd = ::stringEnd(buffer_, stringBeg);
    if (stringBeg != stringEnd) {
        readPos_ = stringEnd;
        return new Expression(Atom(buffer_.substr(stringBeg, stringEnd)));
    }
    return nullptr;
}

Expression* BufferReader::readQuotedExpression() {
    char c = buffer_[readPos_];
    assert(c == '\'');
    ++readPos_;
    Expression* expr = nextExpression();
    if (expr) return cons(quote_symbol, cons(expr, empty_list));
    else --readPos_; 
    return nullptr;
}

Expression* BufferReader::readNumber() {
    int atomBeg = readPos_;
    int atomEnd = ::atomEnd(buffer_, atomBeg);
    std::string token = buffer_.substr(atomBeg, atomEnd);
    readPos_ = atomEnd; //skipped validation of token as number
    return new Expression(Atom((long)atoi(token.c_str())));
}

/*
Expression* BufferReader::readCharacter() {
    char c = buffer_[readPos_];
    assert(c == '#');
    int atomBeg = readPos_;
    int atomEnd = ::atomEnd(buffer_, atomBeg);
    std::string token = buffer_.substr(atomBeg, atomEnd);
    if (token == "#\\space") {
        readPos_ = atomEnd;
        return new Expression(Atom(' '));
    } else if (token == "#\\newline") {
        readPos_ = atomEnd;
        return new Expression(Atom('\n'));
    }
    if (token.size() != 3) {
        std::cerr << "unexpexted character " << token << '\n';
        return nullptr;
    }
    readPos_ = atomEnd;
    return new Expression(Atom(token[2]));
}

Expression* BufferReader::readBoolean() {
    char c = buffer_[readPos_];
    assert(c == '#');
    char n = buffer_[readPos_+1];
    if (n == 't') { ++readPos_; return _true; }
    else if (n == 'f') { ++readPos_; return _false; }
    std::cerr << "unexpected #" << n << '\n';
    return nullptr;
}
*/

Expression* BufferReader::readHash() {
    char c = buffer_[readPos_];
    assert(c == '#');
    int atomBeg = readPos_;
    int atomEnd = ::atomEnd(buffer_, atomBeg);
    if (atomBeg != atomEnd) {
        std::string token = buffer_.substr(atomBeg, atomEnd);
        if (token == "#t") { readPos_ = atomEnd; return _true; }
        else if (token == "#f") { readPos_ = atomEnd; return _false; }
        else if (token == "#\\space") { readPos_ = atomEnd; return new Expression(Atom(' ')); }
        else if (token == "#\\newline") { readPos_ = atomEnd; return new Expression(Atom('\n')); }
        else if (token.size() == 3 && token[1] == '\\') { readPos_ = atomEnd; return new Expression(Atom(token[2])); }
        else {
            std::cerr << "discard unexpected " << token << '\n';
            readPos_ = atomEnd;
            return nullptr;
        }
    } else return nullptr;
}

Expression* BufferReader::readSymbol() {
    char c = buffer_[readPos_];
    assert(!isspace(c));
    int atomBeg = readPos_;
    int atomEnd = ::atomEnd(buffer_, atomBeg);
    if (atomBeg != atomEnd) {
        readPos_ = atomEnd;
        return makeSymbol(buffer_.substr(atomBeg, atomEnd));
    } else return nullptr;
}

//when fail should not change readPos_
Expression* BufferReader::nextExpression() {
    while (readPos_ < buffer_.size() && isspace(buffer_[readPos_])) ++readPos_;
    if (readPos_ == buffer_.size()) return nullptr; //at the end of buffer
    char c = buffer_[readPos_];
    char n = buffer_[readPos_+1]; //make sure within the bound
    if (c == '(') return readList();
    else if (c == '"') return readString();
    else if (c == '\'') return readQuotedExpression(); 
    else if ((c == '-' && isdigit(n) || isdigit(c))) return readNumber();
    else if (c == '#') return readHash();
    else return readSymbol();
    return nullptr;
}

