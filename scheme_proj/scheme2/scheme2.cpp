#include <iostream>
#include "eval.h"
#include "ReadTokenizeParse.h"
#include "output.h"

int main() {
    std::cout << "=== Scheme in C++ === ^C to quit\n";

    ReadTokenizeParse rtp;
    int tokenIdx = 0;
    Expression *expr = nullptr;
    while (!expr) {
        std::cout << "> ";
        rtp.readAndTokenize();
        expr = rtp.parseExpression(tokenIdx);
        if (expr) std::cout << expr << '\n';
        if (expr) std::cout << Evaluator::eval(expr) << '\n';
        expr = nullptr;
    }

    std::cout << "Goodbye\n";
    return 0;
}
