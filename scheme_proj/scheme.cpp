#include <iostream>
#include <fstream>
#include <string>
#include "primitive_proc.h"
#include "env.h"
#include "read.h"
#include "eval.h"
#include "write.h"

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

    empty_env = empty_list;
    global_env = makeEnv();

}

// *******************LOOP*******************

string getInput() {
    string line = "", temp = "";
    int left = 0, right = 0, i = 2;
    while (true) {
        getline(cin, temp);
        for (int in=0; in<temp.size(); ++in) {
            if (temp[in] == '(') ++left;
            if (temp[in] == ')') ++right;
            if (temp[in] == 5) { line += temp; goto end; }
        }
        line += temp + '\n';
        cout << "  ";
        for (int j = 0; j < left-right; ++j) cout << "    ";
    }
    end:
    line.pop_back();
    return line;
}

int parenCount(string line) {
    int left = 0, right = 0;
    for (int i=0; i<line.size(); ++i) {
        if (line[i] == '(') ++left;
        if (line[i] == ')') ++right;
    }
    return left - right;
}

void fileInput(string file, bool showImportText) {
    ifstream f(file);
    string line, temp = "";
    char c;
    while (f.get(c) && isspace(c));
    while (getline(f,line)) {
        line = c + line;
        while (parenCount(line) > 0) { getline(f,temp); line += '\n' + temp; }
        Reader r = Reader(line);
        Expression *evaluated = eval(r.readIn(),global_env);
        if (showImportText) { cout << "> " << line << '\n'; write(evaluated); cout << '\n'; }
        while (f.get(c) && isspace(c));
    }
}

int main() {
    //system("clear");
    cout << "=== Scheme in C++ === ^C to quit\n";
    string line;
    init();

    //fileInput("scm_files/a.scm", true);
    fileInput("scm_files/testing_input.scm", true);

    while (1) {
        cout << "> ";
        line = getInput();
        Reader r = Reader(line);
        write(eval(r.readIn(), global_env));
        cout << '\n';
    }
}