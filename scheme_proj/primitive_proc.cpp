#include <iostream>
#include <fstream>
#include <string>
#include "primitive_proc.h"

extern Expression *_false;
extern Expression *_true;
extern Expression *ok_symbol;

Expression* isNullProc(Expression *args) { return isEmptyList(car(args)) ? _true : _false; }
Expression* isBoolProc(Expression *args) { return isBool(car(args)) ? _true : _false; }
Expression* isSymbolProc(Expression *args) { return isSymbol(car(args)) ? _true : _false; }
Expression* isIntegerProc(Expression *args) { return isNum(car(args)) ? _true : _false; }
Expression* isCharProc(Expression *args) { return isChar(car(args)) ? _true : _false; }
Expression* isStringProc(Expression *args) { return isString(car(args)) ? _true : _false; }
Expression* isPairProc(Expression *args) { return isList(car(args)) ? _true : _false; }
Expression* isProcedureProc(Expression *args) { Expression* a = car(args); return (isPrimProc(a) || isCompProc(a)) ? _true : _false; }

Expression* charToIntProc(Expression *args) { return new Expression(Atom((int) car(args)->atom.atomValue_.at(0))); }
Expression* intToCharProc(Expression *args) { return new Expression(Atom((char) stoi(car(args)->atom.atomValue_))); }
Expression* numToStrProc(Expression *args) { return new Expression(Atom('"' + car(args)->atom.atomValue_)); }
Expression* strToNumProc(Expression *args) { return new Expression(Atom(stoi(car(args)->atom.atomValue_))); }
Expression* symbolToStrProc(Expression *args) { return new Expression(Atom('"' + car(args)->atom.atomValue_)); }
Expression* strToSymbolProc(Expression *args) { return new Expression(Atom(car(args)->atom.atomValue_)); }

Expression* addProc(Expression *args) {
    int result = 0;
    while (!isEmptyList(args)) {
        if (!isNum(car(args))) { fprintf(stderr, "incorrect type in addition\n"); exit(1); }
        result += car(args)->atom.getInt();
        args = cdr(args);
    }
    return new Expression(Atom(result));
}

Expression* subProc(Expression *args) {
    int result;
    result = car(args)->atom.getInt();
    while (!isEmptyList(args = cdr(args))) {
        if (!isNum(car(args))) { fprintf(stderr, "incorrect type in subtraction\n"); exit(1); }
        result -= car(args)->atom.getInt();
    }
    return new Expression(Atom(result));
}

Expression* multProc(Expression *args) {
    int result = 1;
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
    if (expr1->atom.atomType_ != expr2->atom.atomType_) return _false;
    else if (expr1->atom.atomValue_ == expr2->atom.atomValue_) return _true;
    else return (expr1 == expr2) ? _true : _false;
}
