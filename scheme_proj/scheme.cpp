#include <iostream>
#include <fstream>
#include <string>
#include "primitive_proc.h"
#include "env.h"
#include "read.h"
#include "eval.h"
#include "write.h"

//#include "BufferReader.h"

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

ifstream _ifs;
ofstream _ofs;
ifstream _ifs_2; // for scheme input filestream
ofstream _ofs_2; // for scheme output filestream

int main() {
    Expression *expr = nullptr;

    cout << "=== Scheme in C++ === ^C to quit\n";

    init();

    //ifstream ifs("scm_files/testing_input.scm");
    //ofstream ofs("a.txt");
    Reader r = Reader("scm_files/b.scm");
    //Reader r = Reader();
    Writer w = Writer();
    
    while (true) {
        cout << "> ";
        r.fillBuff();
        expr = r.readIn();
        if (expr == nullptr) break;
        w.write(expr); *w.out << '\n'; // Uncomment to see input from file
        w.write(eval(expr, global_env));
        *w.out << '\n';
        //r.emptyBuff();
    }
    
    cout << "Goodbye\n";
    return 0;
}
