#pragma once
#include <string>
#include "Sxpressions.h"

bool isDelimiter(char c);

class Reader {
private:
    int i;
    std::string line;

public:
    Reader() : i(0), line("") {}
    Reader(std::string& str) : i(0), line(str) {}

    void eatWhiteSpace();
    void eatString(std::string check);
    void peekDelimiter();
    Expression* readCharacter();
    Expression* readIn();
    Expression* readPair();
};