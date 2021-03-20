#pragma once

#include <string>
#include <vector>
#include "Sxpressions.h"

class BufferReader {
public:
    void readBuffer();

    //work on string buf
    Expression* nextExpression();

    //work on vector of tokens
    Expression* nextExpressionT(int& index);

private:
    //nextExpression helper funcions
    Expression* readCdr();
    Expression* readString();
    Expression* readQuotedExpression();
    Expression* readNumber();
    Expression* readHash();
    Expression* readSymbol();

    //nextExpressionT helper funcions
    Expression* readCdrT(int& index);
    //Expression* readQuotedExpressionT(int& index);
    Expression* readHashT(int& index);

    std::string buffer_; //switch to efficient solution later
    int readPos_{0};

    std::vector<std::string> tokens_;
    int tokenIdx_{0};
    
    //last active buffer_ token_ range
    //drop bad input and continue
};
