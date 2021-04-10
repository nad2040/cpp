#include "primitive_proc.h"
#include "env.h"
#include "read.h"
#include "write.h"
#include "eval.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

extern Expression *_false;
extern Expression *_true;
extern Expression *ok_symbol;
extern Expression *global_env;
extern Expression *eof_object;
extern ifstream _ifs_2;
extern ofstream _ofs_2;

Expression* isNullProc(Expression *args) { return isEmptyList(car(args)) ? _true : _false; }
Expression* isBoolProc(Expression *args) { return isBool(car(args)) ? _true : _false; }
Expression* isSymbolProc(Expression *args) { return isSymbol(car(args)) ? _true : _false; }
Expression* isIntegerProc(Expression *args) { return isNum(car(args)) ? _true : _false; }
Expression* isCharProc(Expression *args) { return isChar(car(args)) ? _true : _false; }
Expression* isStringProc(Expression *args) { return isString(car(args)) ? _true : _false; }
Expression* isPairProc(Expression *args) { return isList(car(args)) ? _true : _false; }
Expression* isProcedureProc(Expression *args) { Expression* a = car(args); return (isPrimProc(a) || isCompProc(a)) ? _true : _false; }

Expression* charToIntProc(Expression *args) { return new Expression(Atom((long) car(args)->atom.atomValue_.at(0))); }
Expression* intToCharProc(Expression *args) { return new Expression(Atom((char) stol(car(args)->atom.atomValue_))); }
Expression* numToStrProc(Expression *args) { return new Expression(Atom('"' + car(args)->atom.atomValue_)); }
Expression* strToNumProc(Expression *args) { return new Expression(Atom(stol(car(args)->atom.atomValue_))); }
Expression* symbolToStrProc(Expression *args) { return new Expression(Atom('"' + car(args)->atom.atomValue_)); }
Expression* strToSymbolProc(Expression *args) { return new Expression(Atom(car(args)->atom.atomValue_)); }

Expression* addProc(Expression *args) {
    long result = 0;
    while (!isEmptyList(args)) {
        if (!isNum(car(args))) { cerr << "incorrect type in addition\n"; exit(1); }
        result += car(args)->atom.getInt();
        args = cdr(args);
    }
    return new Expression(Atom(result));
}

Expression* subProc(Expression *args) {
    long result;
    result = car(args)->atom.getInt();
    while (!isEmptyList(args = cdr(args))) {
        if (!isNum(car(args))) { cerr << "incorrect type in subtraction\n"; exit(1); }
        result -= car(args)->atom.getInt();
    }
    return new Expression(Atom(result));
}

Expression* multProc(Expression *args) {
    long result = 1;
    while (!isEmptyList(args)) {
        result *= car(args)->atom.getInt();
        args = cdr(args);
    }
    return new Expression(Atom(result));
}

Expression* quotientProc(Expression *args) {
    return new Expression(Atom( (car(args)->atom.getInt()) / (cadr(args)->atom.getInt()) ));
}

Expression* remainderProc(Expression *args) {
    return new Expression(Atom( (car(args)->atom.getInt()) % (cadr(args)->atom.getInt()) ));
}

Expression* isNumberEqualProc(Expression *args) {
    int value;
    value = car(args)->atom.getInt();
    while (!isEmptyList(args = cdr(args))) {
        if (value != (car(args)->atom.getInt())) return _false;
    }
    return _true;
}

Expression* isLessThanProc(Expression *args) {
    int previous;
    int next;
    previous = car(args)->atom.getInt();
    while (!isEmptyList(args = cdr(args))) {
        next = car(args)->atom.getInt();
        if (previous < next) previous = next;
        else return _false;
    }
    return _true;
}

Expression* isGreaterThanProc(Expression *args) {
    int previous;
    int next;
    previous = car(args)->atom.getInt();
    while (!isEmptyList(args = cdr(args))) {
        next = car(args)->atom.getInt();
        if (previous > next) previous = next;
        else return _false;
    }
    return _true;
}

Expression* consProc(Expression *args) { return cons(car(args), cadr(args)); }
Expression* carProc(Expression *args) { return caar(args); }
Expression* cdrProc(Expression *args) { return cdar(args); }
Expression* setcarProc(Expression *args) { setcar(car(args), cadr(args)); return ok_symbol; }
Expression* setcdrProc(Expression *args) { setcdr(car(args), cadr(args)); return ok_symbol; }
Expression* listProc(Expression *args) { return args; }

Expression* isEqProc(Expression *args) {
    Expression *expr1 = car(args), *expr2 = cadr(args);
    if (expr1->exprType_ != expr2->exprType_) return _false;
    if (expr1->exprType_ == ATOM) {
        if (expr1->atom.atomType_ != expr2->atom.atomType_) return _false;
        else return (expr1->atom.atomValue_ == expr2->atom.atomValue_) ? _true : _false;
    } else return (expr1 == expr2) ? _true : _false;
}

Expression* applyProc(Expression *args) {
    cerr << "illegal state: The body of the apply primitive procedure should not execute.\n"; exit(1);
}

Expression* interactionEnvProc(Expression *args) { return global_env; }
Expression* nullEnvProc(Expression *args) { return setupEnv(); }
Expression* envProc(Expression *args) { return makeEnv(); }
Expression* evalProc(Expression *args) {
    cerr << "illegal state: The body of the eval primitive procedure should not execute.\n"; exit(1);
}

Expression* loadProc(Expression *args) {
    string filename = car(args)->atom.atomValue_;
    ifstream ifs;
    Expression *expr;
    Expression *result;

    ifs.open(filename, ifstream::in);
    if (ifs.fail()) { cerr << "could not load file \"" << filename << "\""; exit(1); }
    Reader r = Reader(ifs);
    while (!r.in->eof()) {
        r.fillBuff();
        expr = r.readIn();
        result = eval(expr, global_env);
        //r.emptyBuff();
    }
    ifs.close();
    return result;
}

Expression *openInputPortProc(Expression *args) {
    string filename = car(args)->atom.atomValue_;
    _ifs_2.open(filename, ofstream::in);
    if (_ifs_2.fail()) { cerr << "could not load file \"" << filename << "\""; exit(1); }
    return new Expression(Atom(_ifs_2));
}
Expression *closeInputPortProc(Expression *args) {
    car(args)->atom.in_port->close();
    if (car(args)->atom.in_port->fail()) { cerr << "could not close input port\n"; exit(1); }
    return ok_symbol;
}
Expression *isInputPortProc(Expression *args) { return isInputPort(car(args)) ? _true : _false; }

Expression *readProc(Expression *args) {
    Expression *result;
    Reader r = isEmptyList(args) ? Reader() : Reader(*car(args)->atom.in_port);
    r.fillBuff();
    result = r.readIn();
    //r.emptyBuff();
    return (result == nullptr) ? eof_object : result;
}
Expression *readCharProc(Expression *args) {
    char c;
    Reader r = isEmptyList(args) ? Reader() : Reader(*car(args)->atom.in_port);
    r.in->get(c);
    return (r.in->eof()) ? eof_object : new Expression(Atom(c));
}
Expression *peekCharProc(Expression *args) {
    char c;
    Reader r = isEmptyList(args) ? Reader() : Reader(*car(args)->atom.in_port);
    c = r.in->peek();
    return (c == EOF) ? eof_object : new Expression(Atom(c));
}

Expression *isEOFObjProc(Expression *args) { return isEOFObject(car(args)) ? _true : _false; }

Expression *openOutputPortProc(Expression *args) {
    string filename = car(args)->atom.atomValue_;
    _ofs_2.open(filename, ofstream::app);
    if (_ofs_2.fail()) { cerr << "could not open file \"" << filename << "\""; exit(1); }
    return new Expression(Atom(_ofs_2));
}
Expression *closeOutputPortProc(Expression *args) {
    car(args)->atom.out_port->close();
    if (car(args)->atom.out_port->fail()) { cerr << "could not close output port\n"; exit(1); }
    return ok_symbol;
}
Expression *isOutputPortProc(Expression *args) { return isOutputPort(car(args)) ? _true : _false; }

Expression *writeCharProc(Expression *args) {
    Expression *character = car(args);
    args = cdr(args);
    Writer w = isEmptyList(args) ? Writer() : Writer(*car(args)->atom.out_port);
    w.out->put(character->atom.atomValue_[0]);
    w.out->flush();
    return ok_symbol;
}
Expression *writeProc(Expression *args) {
    Expression *expr = car(args);
    args = cdr(args);
    Writer w = isEmptyList(args) ? Writer() : Writer(*car(args)->atom.out_port);
    w.write(expr);
    w.out->flush();
    return ok_symbol;
}

Expression *errorProc(Expression *args) {
    Writer w = Writer(cerr);
    while (!isEmptyList(args)) {
        w.write(car(args));
        cerr << " ";
        args = cdr(args);
    };
    cout << "\nexiting\n";
    exit(1);
}