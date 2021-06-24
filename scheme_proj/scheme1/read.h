#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Sxpressions.h"

extern std::ifstream _ifs;

bool isDelimiter(char c);
void ignorews(std::istream& in);
int parenCount(std::string& line);

class Reader {
public:
    int i;
    std::string line;
    std::istream* in;

    Reader() : i(0), line(""), in(&std::cin) {}
    Reader(std::ifstream& ifs) : i(0), line(""), in(&ifs) {}
    Reader(std::string filename) : i(0), line("") {
        _ifs.open(filename, std::ifstream::in);
        in = &_ifs;
    }

    void fillBuff();
    void emptyBuff();

    void eatWhiteSpace();
    void eatString(std::string check);
    void peekDelimiter();
    Expression* readCharacter();
    Expression* readIn();
    Expression* readPair();
};