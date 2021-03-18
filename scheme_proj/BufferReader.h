#pragma once

#include <string>
#include "Sxpressions.h"

class BufferReader {
public:
    void readBuffer();
    Expression* nextExpression();
private:
    Expression* parseList(const std::string& buffer);
    Expression* readCdr();
    Expression* readList();
    Expression* readString();
    Expression* readQuotedExpression();
    Expression* readNumber();
    Expression* readHash();
    Expression* readSymbol();

    std::string buffer_; //switch to efficient solution later
    int readPos_{0};
};
