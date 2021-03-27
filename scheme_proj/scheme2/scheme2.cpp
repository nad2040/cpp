#include <iostream>
#include "eval.h"

#include "ReadTokenizeParse.h"
#include "output.h"
#include "globals.h"

using namespace std;

int main() {
    init();
    cout << "=== Scheme in C++ === ^C to quit\n";

    ReadTokenizeParse rtp;
    int tokenIdx = 0;
    Expression *expr = nullptr;
    while (!expr) {
        cout << "> ";
        rtp.readAndTokenize();
        expr = rtp.parseExpression(tokenIdx);
        if (expr) cout << expr << '\n';
        if (expr) cout << eval(expr, the_env->global_env) << '\n';
        expr = nullptr;
    }

    cout << "Goodbye\n";
    return 0;
}
