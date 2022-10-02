#pragma once
#include "Expression.h"

class Writer {
public:
    std::ostream* out;
    
    Writer() : out(&std::cout) {}
    Writer(std::ostream* os) : out(os) {}
    Writer(std::string filename) {
        std::ofstream* ofs = new std::ofstream();
        ofs->open(filename, std::ofstream::app);
        out = ofs;
    }

    void write(Expression *expr);
    void writeList(Expression *list);
};