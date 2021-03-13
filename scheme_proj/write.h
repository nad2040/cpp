#pragma once
#include <fstream>
#include <iostream>
#include "Sxpressions.h"

extern std::ofstream nullOut;
extern std::ofstream _ofs;

class Writer {
public:
    std::ostream* out;
    
    Writer() : out(&std::cout) {}
    Writer(std::string filename) {
        _ofs.open(filename, std::ofstream::app);
        out = &_ofs;
    }
    Writer(std::ostream& os) : out(&os) {}

    void write(Expression *expr);
    void writeList(Expression *list);
};