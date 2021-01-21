#include <iostream>
#include <fstream>
#include <string>
#include "primitive_proc.h"
#include "env.h"
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

Expression* makeSymbol(string value) {
    Expression *element;
    Expression *symbol;
    /* search for they symbol in the symbol table */
    element = symbol_table;
    while (element->list != nullptr) {
        if (car(element)->atom.atomValue_ == value) {
            return car(element);
        }
        element = cdr(element);
    };
    
    /* create the symbol and add it to the symbol table */
    symbol = new Expression(Atom(value));
    symbol_table = cons(symbol, symbol_table);
    return symbol;
}

void write(Expression*);

Expression* makePrimProc(Expression *(*fn)(Expression *args)) { return new Expression(Atom(fn)); }

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
    global_env = setupEnv();

    #define createProcedure(scheme_name, name) defVar(makeSymbol(scheme_name),makePrimProc(name),global_env);
    createProcedure("null?",isNullProc);
    createProcedure("boolean?",isBoolProc);
    createProcedure("symbol?",isSymbolProc);
    createProcedure("integer?",isIntegerProc);
    createProcedure("char?",isCharProc);
    createProcedure("string?",isStringProc);
    createProcedure("pair?",isPairProc);
    createProcedure("procedure?",isProcedureProc);

    createProcedure("char->integer",charToIntProc);
    createProcedure("integer->char",intToCharProc);
    createProcedure("number->string",numToStrProc);
    createProcedure("string->number",strToNumProc);
    createProcedure("symbol->string",symbolToStrProc);
    createProcedure("string->symbol",strToSymbolProc);

    createProcedure("+",addProc);
    createProcedure("-",subProc);
    createProcedure("*",multProc);
    createProcedure("quotient",quotientProc);
    createProcedure("remainder",remainderProc);
    createProcedure("=",isNumberEqualProc);
    createProcedure("<",isLessThanProc);
    createProcedure(">",isGreaterThanProc);

    createProcedure("cons",consProc);
    createProcedure("car",carProc);
    createProcedure("cdr",cdrProc);
    createProcedure("set-car!",setcarProc);
    createProcedure("set-cdr!",setcdrProc);
    createProcedure("list",listProc);

    createProcedure("eq?",isEqProc);

}

// *******************READ*******************
int i;

bool isDelimiter(char c) {
    return isspace(c) || c == EOF ||
           c == '('   || c == ')' ||
           c == '"'   || c == ';' ||
           c == '\0';
}

void eatWhiteSpace(string &line) {
    char c;
    while ((c = line[i++]) != '\0') {
        if (isspace(c)) {
            continue;
        }
        else if (c == ';') {
            while ((c = line[i++]) != '\0' && c != '\n');
            continue;
        }
        --i;
        break;
    }
}

void eatString(string &line, string check) {
    int c=0;
    while (c<check.size()) {
        if (line[i++] != check[c++]) {
            fprintf(stderr, "unexpected character '%c'\n", line[i]);
            exit(1);
        }
    }
    ++i;
}

void peekDelimiter(string &line) {
    if (!isDelimiter(line[++i])) {
        fprintf(stderr, "character not followed by delimiter\n");
        exit(1);
    }
}

Expression* readCharacter(string &line) {
    char c;
    switch (c = line[++i]) {
        case '\0':
            fprintf(stderr, "incomplete character literal\n");
            exit(1);
        case 's':
            if (line[++i] == 'p') {
                eatString(line,"pace");
                peekDelimiter(line);
                return new Expression(Atom(' '));
            } break;
        case 'n':
            if (line[++i] == 'e') {
                eatString(line,"ewline");
                peekDelimiter(line);
                return new Expression(Atom('\n'));
            } break;
    }
    peekDelimiter(line);
    return new Expression(Atom(c));
}

Expression* readIn(string& line);

Expression* readPair(string line) {
    char c;
    Expression *car_obj;
    Expression *cdr_obj;
    Expression *expr;
    
    eatWhiteSpace(line);
    c = line[i];
    if (c == ')') { /* read the empty list */
        i++;
        return empty_list;
    }

    car_obj = readIn(line);

    eatWhiteSpace(line);
    c = line[i++];   
    if (c == '.') { /* read improper list */
        c = line[i++];
        if (!isDelimiter(c)) {
            fprintf(stderr, "dot not followed by delimiter\n"); exit(1);
        }
        cdr_obj = readIn(line);
        eatWhiteSpace(line);
        c = line[i];
        if (c != ')') {
            fprintf(stderr, "where was the trailing right paren?\n"); exit(1);
        }
        expr = cons(car_obj, cdr_obj);
        i++;
        return expr;
    }
    else { /* read list */
        --i;
        cdr_obj = readPair(line);
        expr = cons(car_obj, cdr_obj);
        return expr;
    }
}

Expression* readIn(string& line) {
    long n = 0;
    short sign = 1;
    char c;
    string str;

    eatWhiteSpace(line);

    if (line.empty()) { return new Expression(Atom()); }

    c = line[i];
    if (c == '#') { /* read boolean/char */
        c = line[++i];
        if (c == 't') {
            i++;
            return _true;
        } else if (c == 'f') {
            i++;
            return _false;
        } else if (c == '\\') {
            return readCharacter(line);
        } else {
            fprintf(stderr, "unknown bool or char literal\n");
            exit(1);
        }
    }
    else if ((c == '-' && isdigit(line[i+1]) || isdigit(c))) { /* read number */
        if (c == '-') {
            sign = -1;
            i++;
        }
        while (isdigit(c = line[i++])) {
            n = n*10 + (c - '0');
        } --i;
        n *= sign;
        return new Expression(Atom(n));
    }
    else if (isInitial(c) || ((c == '+' || c == '-') && isDelimiter(line[i+1]))) { /* read symbol */
        while (isInitial(c) || isdigit(c) || c == '+' || c == '-') {
            str += c;
            c = line[++i];
        }
        if (isDelimiter(c)) {
            return makeSymbol(str);
        }
        else { fprintf(stderr, "symbol not followed by delimiter. Found '%c'\n", c); exit(1); }
    }
    else if (c == '"') { /* read string */
        i++;
        while (((c = line[i++]) != '"')) {
            if (c == '\\') {
                if ((c = line[i++]) == 'n') c = '\n';
            }
            str += c;
        }
        if (c == EOF) { fprintf(stderr, "non-terminated string literal\n"); exit(1); }
        return new Expression(Atom('"' + str));
    }
    else if (c == '(') { /* read pair/list */
        i++;
        return readPair(line);
    }
    else if (c == '\'') { /* read quoted expression */
        i++;
        return cons(quote_symbol, cons(readIn(line), empty_list));
    }
    else { /* bad input */
        fprintf(stderr, "bad input. Unexpected '%c'\n", c);
        exit(1);
    }
    fprintf(stderr, "read illegal state\n");
    exit(1);
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
        i=0;
        Expression *evaluated = eval(readIn(line),global_env);
        if (showImportText) { cout << "> " << line << '\n'; write(evaluated); cout << '\n'; }
        while (f.get(c) && isspace(c));
    }
}

int main() {
    system("clear");
    cout << "=== Scheme in C++ === ^C to quit\n";
    string line;
    init();

    //fileInput("scm_files/a.scm", true);
    fileInput("scm_files/testing_input.scm", true);

    while (1) {
        i = 0;
        cout << "> ";
        line = getInput();
        write(eval(readIn(line), global_env));
        cout << '\n';
        // write(global_env); cout << '\n';
    }

    // Test Cases
    // fileInput("scm_files/testing_input.txt", true);
}