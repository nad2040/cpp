#include "primitive_proc.h"
#include "env.h"
#include "eval.h"
#include <iostream>
#include <string>
#include <fstream>
#include "ReadTokenizeParse.h"
#include "output.h"
#include "globals.h"

using namespace std;

Expression* isNullProc(Expression *args) { return isEmptyList(car(args)) ? _true : _false; }
Expression* isBoolProc(Expression *args) { return isBool(car(args)) ? _true : _false; }
Expression* isSymbolProc(Expression *args) { return isSymbol(car(args)) ? _true : _false; }
Expression* isIntegerProc(Expression *args) { return isNum(car(args)) ? _true : _false; }
Expression* isCharProc(Expression *args) { return isChar(car(args)) ? _true : _false; }
Expression* isStringProc(Expression *args) { return isString(car(args)) ? _true : _false; }
Expression* isPairProc(Expression *args) { return isList(car(args)) ? _true : _false; }
Expression* isProcedureProc(Expression *args) { Expression* a = car(args); return (isPrimProc(a) || isCompProc(a)) ? _true : _false; }

Expression* charToIntProc(Expression *args) { return new Expression(Atom((long)(car(args)->getAtom().getChar()))); }
Expression* intToCharProc(Expression *args) { return new Expression(Atom((char)(car(args)->getAtom().getNumber()))); }
Expression* numToStrProc(Expression *args) { return new Expression(Atom(std::to_string(car(args)->getAtom().getNumber()))); }
Expression* strToNumProc(Expression *args) { return new Expression(Atom(stol(car(args)->getAtom().getString().c_str()))); }
Expression* symbolToStrProc(Expression *args) { return new Expression(Atom(car(args)->getAtom().getSymbol())); }
Expression* strToSymbolProc(Expression *args) { return new Expression(Atom(Symbol{car(args)->getAtom().getString()})); }

Expression* addProc(Expression *args) {
    long result = 0;
    while (!isEmptyList(args)) {
        result += car(args)->getAtom().getNumber();
        args = cdr(args);
    }
    return new Expression(Atom(result));
}

Expression* subProc(Expression *args) {
    long result;
    result = car(args)->getAtom().getNumber();
    while (!isEmptyList(args = cdr(args))) {
        result -= car(args)->getAtom().getNumber();
    }
    return new Expression(Atom(result));
}

Expression* multProc(Expression *args) {
    long result = 1;
    while (!isEmptyList(args)) {
        result *= car(args)->getAtom().getNumber();
        args = cdr(args);
    }
    return new Expression(Atom(result));
}

Expression* quotientProc(Expression *args) {
    return new Expression(Atom( car(args)->getAtom().getNumber() / cadr(args)->getAtom().getNumber() ));
}

Expression* remainderProc(Expression *args) {
    return new Expression(Atom( car(args)->getAtom().getNumber() % cadr(args)->getAtom().getNumber() ));
}

Expression* isNumberEqualProc(Expression *args) {
    int value;
    value = car(args)->getAtom().getNumber();
    while (!isEmptyList(args = cdr(args))) {
        if (value != car(args)->getAtom().getNumber()) return _false;
    }
    return _true;
}

Expression* isLessThanProc(Expression *args) {
    int previous;
    int next;
    previous = car(args)->getAtom().getNumber();
    while (!isEmptyList(args = cdr(args))) {
        next = car(args)->getAtom().getNumber();
        if (previous < next) previous = next;
        else return _false;
    }
    return _true;
}

Expression* isGreaterThanProc(Expression *args) {
    int previous;
    int next;
    previous = car(args)->getAtom().getNumber();
    while (!isEmptyList(args = cdr(args))) {
        next = car(args)->getAtom().getNumber();
        if (previous > next) previous = next;
        else return _false;
    }
    return _true;
}

Expression* consProc(Expression *args) { return cons(car(args), cadr(args)); }
Expression* carProc(Expression *args) { return caar(args); }
Expression* cdrProc(Expression *args) { return cdar(args); }
Expression* setcarProc(Expression *args) { setcar(car(args), cadr(args)); return Symbol::ok_symbol(); }
Expression* setcdrProc(Expression *args) { setcdr(car(args), cadr(args)); return Symbol::ok_symbol(); }
Expression* listProc(Expression *args) { return args; }

Expression* isEqProc(Expression *args) {
    Expression *expr1 = car(args), *expr2 = cadr(args);
    if (expr1->getAtom().atomType_ != expr2->getAtom().atomType_) return _false;
    else if (expr1->getAtom() == expr2->getAtom()) return _true;
    else return (expr1 == expr2) ? _true : _false;
}

Expression* applyProc(Expression *args) {
    cerr << "illegal state: The body of the apply primitive procedure should not execute.\n"; exit(1);
}

Expression* interactionEnvProc(Expression *args) { return the_env->getGlobalEnv(); }
//Expression* nullEnvProc(Expression *args) { return the_env->null_env; }
Expression* nullEnvProc(Expression *args) { return the_env->setupEnv(); }
Expression* envProc(Expression *args) { return the_env->makeEnv(); }
Expression* evalProc(Expression *args) {
    cerr << "illegal state: The body of the eval primitive procedure should not execute.\n"; exit(1);
}

Expression* loadProc(Expression *args) {
    string filename = car(args)->getAtom().getString();
    ifstream ifs;
    Expression *expr;
    Expression *result;

    ifs.open(filename, ifstream::in);
    if (ifs.fail()) { cerr << "could not load file \"" << filename << "\""; exit(1); }

    ReadTokenizeParse rtp;
    expr = nullptr;
    int idx = 0;
    //while (!expr) {
    while (!ifs.eof()) {
        rtp.readAndTokenize(ifs);
        expr = rtp.parseExpression(idx);
        if (expr) {
            //std::cout << "eval current expr:" << expr << '\n';
            result = eval(expr, the_env->getGlobalEnv());
        }
    }
    
    ifs.close();
    return result;
}

Expression *openInputPortProc(Expression *args) {
    string filename = car(args)->getAtom().getString();
    ifstream* ifs = new ifstream;
    ifs->open(filename, ofstream::in);
    if (ifs->fail()) { cerr << "could not load file \"" << filename << "\""; exit(1); }
    return new Expression(Atom(ifs));
}

Expression *closeInputPortProc(Expression *args) {
    car(args)->getAtom().in_port()->close();
    if (car(args)->getAtom().in_port()->fail()) { cerr << "could not close input port\n"; exit(1); }
    return Symbol::ok_symbol();
}

Expression *isInputPortProc(Expression *args) { return isInputPort(car(args)) ? _true : _false; }

Expression *readProc(Expression *args) {
    Expression *result;

    istream& ifs = isEmptyList(args) ? std::cin : *(car(args)->getAtom().in_port());
    ReadTokenizeParse rtp;
    Expression* expr = nullptr;
    int idx = 0;
    while (!expr) {
        rtp.readAndTokenize(ifs);
        expr = rtp.parseExpression(idx);
        result = eval(expr, the_env->getGlobalEnv());
    }

    return (result == nullptr) ? eof_object : result;
}

Expression *readCharProc(Expression *args) {
    char c;
    istream& is = isEmptyList(args) ? std::cin : *(car(args)->getAtom().in_port());
    is.get(c);
    return is.eof() ? eof_object : new Expression(Atom(c));
}

Expression *peekCharProc(Expression *args) {
    char c;
    istream& is = isEmptyList(args) ? std::cin : *(car(args)->getAtom().in_port());
    c = is.peek();
    return (c == EOF) ? eof_object : new Expression(Atom(c));
}

Expression *isEOFObjProc(Expression *args) { return isEOFObject(car(args)) ? _true : _false; }

Expression *openOutputPortProc(Expression *args) {
    string filename = car(args)->getAtom().getString();
    ofstream* ofs = new ofstream;
    ofs->open(filename, ofstream::app);
    if (ofs->fail()) { cerr << "could not open file \"" << filename << "\""; exit(1); }
    return new Expression(Atom(ofs));
}

Expression *closeOutputPortProc(Expression *args) {
    car(args)->getAtom().out_port()->close();
    if (car(args)->getAtom().out_port()->fail()) { cerr << "could not close output port\n"; exit(1); }
    return Symbol::ok_symbol();
}

Expression *isOutputPortProc(Expression *args) { return isOutputPort(car(args)) ? _true : _false; }

Expression *writeCharProc(Expression *args) {
    Expression *character = car(args);
    args = cdr(args);
    ostream& os = isEmptyList(args) ? std::cout : *(car(args)->getAtom().out_port());
    os << character->getAtom().getChar();
    return Symbol::ok_symbol();
}
Expression *writeProc(Expression *args) {
    Expression *expr = car(args);
    args = cdr(args);
    ostream& os = isEmptyList(args) ? std::cout : *(car(args)->getAtom().out_port());
    os << expr;
    return Symbol::ok_symbol();
}

Expression *errorProc(Expression *args) {
    ostream& os(cerr);
    os << args;
    /*
    while (!isEmptyList(args)) {
        os << car(args) << ' ';
        args = cdr(args);
    };
    */
     
    cout << "\nexiting\n";
    exit(1);
}
