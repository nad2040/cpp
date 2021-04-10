#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Sxpressions.h"

class ReadTokenizeParse {
public:
    void readAndTokenize();
    void readAndTokenize(std::istream& is);
    Expression* parseExpression(int& index);

    std::string& getBuffer() { return buffer_; }
    int getReadPos() { return readPos_; }

    std::vector<std::string>& getTokens() { return tokens_; }
    int getTokenPos() { return tokenPos_; }

private:
    Expression* parseCdr(int& index);
    Expression* parseHash(int& index);

    std::string buffer_; //switch to efficient solution later
    int readPos_{0};

    std::vector<std::string> tokens_;
    int tokenPos_{0};
    
    //last active buffer_ token_ range
    //drop bad input and continue
};
