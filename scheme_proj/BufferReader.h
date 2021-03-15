#pragma once

#include <string>

class BufferReader {
public:
    void readBuffer();
    std::string nextExpression();
private:
    std::string buffer_; //switch to efficient solution later
    int readPos_{0};
};
