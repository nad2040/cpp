#include <iostream>
#include <fstream>
#include <string>
#include "primitive_proc.h"
#include "env.h"
#include "eval.h"

#include "ReadTokenizeParse.h"
#include "output.h"

using namespace std;

Expression *empty_list;
Expression *_false;
Expression *_true;
Expression *quote_symbol;
Expression *symbol_table;
Expression *define_symbol;
Expression *set_symbol;
Expression *ok_symbol;
Expression *if_symbol;
Expression *lambda_symbol;
Expression *begin_symbol;
Expression *cond_symbol;
Expression *else_symbol;
Expression *let_symbol;
Expression *and_symbol;
Expression *or_symbol;
Expression *eof_object;
Expression *empty_env;
Expression *global_env;

void init() {
    empty_list = new Expression();
    _false = new Expression(Atom(false));
    _true = new Expression(Atom(true));

    symbol_table = empty_list;
    quote_symbol = makeSymbol("quote");
    define_symbol = makeSymbol("define");
    set_symbol = makeSymbol("set!");
    ok_symbol = makeSymbol("ok");
    if_symbol = makeSymbol("if");
    lambda_symbol = makeSymbol("lambda");
    begin_symbol = makeSymbol("begin");
    cond_symbol = makeSymbol("cond");
    else_symbol = makeSymbol("else");
    let_symbol = makeSymbol("let");
    and_symbol = makeSymbol("and");
    or_symbol = makeSymbol("or");

    eof_object = makeEOF();

    empty_env = empty_list;
    global_env = makeEnv();

}

// *******************LOOP*******************
ifstream _ifs_2; // for scheme input filestream
ofstream _ofs_2; // for scheme output filestream

int main() {
    cout << "=== Scheme in C++ === ^C to quit\n";

    Expression *expr = nullptr;
    init();

    ReadTokenizeParse rtp;
    int tokenIdx = 0;
    while (!expr) {
        cout << "> ";
        rtp.readAndTokenize();
        expr = rtp.parseExpression(tokenIdx);
        if (expr) cout << expr << '\n';
        if (expr) cout << eval(expr, global_env) << '\n';
        expr = nullptr;
    }

    cout << "Goodbye\n";
    return 0;
}
