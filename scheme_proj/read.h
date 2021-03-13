#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Sxpressions.h"

extern std::ifstream nullIn;
extern std::ifstream _ifs;

bool isDelimiter(char c);
int parenCount(std::string line);

class Reader {
public:
    int i;
    std::string line;
    std::ifstream* in;

    Reader() : i(0), line(""), in(&nullIn) {}
    Reader(std::ifstream& ifs) : i(0), line(""), in(&ifs) {}
    Reader(std::string filename) : i(0), line("") {
        _ifs.open(filename, std::ifstream::in);
        in = &_ifs;
    }

    void getInput();
    void fileInput();

    void eatWhiteSpace();
    void eatString(std::string check);
    void peekDelimiter();
    Expression* readCharacter();
    Expression* readIn();
    Expression* readPair();

    void fillBuff() {
        if (in == &nullIn) getInput();
        else fileInput();
    }
};