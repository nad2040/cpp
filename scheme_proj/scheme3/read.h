#pragma once
#include "Expression.h"

bool isDelimiter(char c);
bool isInitial(char c);
void ignorews(std::istream& in);
int parenCount(std::string& line);

class Reader {
public:
    int i;
    std::string line;
    std::istream* in;

    Reader() : i(0), line(""), in(&std::cin) {}
    Reader(std::ifstream* ifs) : i(0), line(""), in(ifs) {}
    Reader(std::string filename) : i(0), line("") {
        std::ifstream* ifs = new std::ifstream();
        ifs->open(filename, std::ifstream::in);
        in = ifs;
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