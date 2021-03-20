#pragma once

#include <string>
#include <vector>
#include "Sxpressions.h"

class ReadTokenizeParse {
public:
    void readAndTokenize();
    Expression* parseExpression(int& index);

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
