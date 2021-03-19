#pragma once

#include <string>
#include <vector>
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

    std::vector<std::string> tokens_;
    int tokenIdx_{0};

    //last active buffer_ token_ range
    //drop bad input and continue
};
