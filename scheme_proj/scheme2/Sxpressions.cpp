#include <string>
#include "Sxpressions.h"
#include "globals.h"

bool isInitial(char c) {
    return isalpha(c) || c == '*' || c == '/' || c == '>' || c == '<' || c == '=' || c == '?' || c == '!';
}

bool isSym(std::string &str) {
    char c; int i=0;
    while (isInitial(c = str[i]) || c == '+' || c == '-') {
        i++;
    }
    return i == str.length();
}

Expression* car(Expression* expr) {
    return expr->getCar();
}

void setcar(Expression *expr, Expression* value) {
    expr->setCar(value);
}

Expression* cdr(Expression* expr) {
    return expr->getCdr();
}

void setcdr(Expression *expr, Expression* value) {
    expr->setCdr(value);
}

Expression* cons(Expression *car, Expression *cdr) {
    Expression::List myList { car, cdr };
    Expression* consObj = new Expression(myList);
    return consObj;
}

bool isList(Expression *expr) { return expr->exprType_ == Expression::LIST; }
bool isAtom(Expression *expr) { return expr->exprType_ == Expression::ATOM; }
bool isBool(Expression *expr) { return isAtom(expr) && expr->getAtom().atomType_ == BOOL; }
bool isNum(Expression *expr) { return isAtom(expr) && expr->getAtom().atomType_ == NUM; }
bool isChar(Expression *expr) { return isAtom(expr) && expr->getAtom().atomType_ == CHAR; }
bool isString(Expression *expr) { return isAtom(expr) && expr->getAtom().atomType_ == STR; }
bool isSymbol(Expression *expr) { return isAtom(expr) && expr->getAtom().atomType_ == SYMBOL; }
bool isPrimProc(Expression *expr) { return isAtom(expr) && expr->getAtom().atomType_ == PRIM_PROC; }
bool isCompProc(Expression *expr) { return isAtom(expr) && expr->getAtom().atomType_ == COMP_PROC; }

bool isFalse(Expression *expr) { return expr == _false; }
bool isTrue(Expression *expr) { return !isFalse(expr); }

bool isEmptyList(Expression *expr) { return isList(expr) && expr->getCar() == nullptr && expr->getCdr() == nullptr; }
bool isInputPort(Expression *expr) { return isAtom(expr) && expr->getAtom().atomType_ == INPUT; }
bool isOutputPort(Expression *expr) { return isAtom(expr) && expr->getAtom().atomType_ == OUTPUT; }
bool isEOFObject(Expression *expr) { return expr == eof_object; }

Expression* makeSymbol(std::string value) {
    Expression *element;
    Expression *symbol;
    /* search for they symbol in the symbol table */
    element = symbol_table;
    while (element != nullptr) {
        assert(isList(element));
        Expression* first=car(element);
        if (first && isAtom(first) && first->getAtom().getString() == value) {
            return first;
        }
        element = cdr(element);
    };
    
    /* create the symbol and add it to the symbol table */
    symbol = new Expression(Atom(value));
    symbol_table = cons(symbol, symbol_table);
    return symbol;
}

Expression* makeEOF() {
    Expression* expr = new Expression(Atom());
    expr->getAtom().atomType_ = EOF_OBJECT;
    return expr;
}

Expression* makePrimProc(Expression *(*fn)(Expression *args)) { return new Expression(Atom(fn)); }

