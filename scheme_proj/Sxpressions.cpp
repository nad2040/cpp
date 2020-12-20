#include <string>
#include <iostream>

#include "Sxpressions.h"

using namespace std;

extern Expression *_false;
extern Expression *_true;

bool isInitial(char c) {
    return isalpha(c) || c == '*' || c == '/' || c == '>' || c == '<' || c == '=' || c == '?' || c == '!';
}

bool isSym(string &str) {
    char c; int i=0;
    while (isInitial(c = str[i]) || c == '+' || c == '-') {
        i++;
    }
    return i == str.length();
}

Expression* car(Expression* expr) {
    return expr->list->car;
}
void setcar(Expression *expr, Expression* value) {
    expr->list->car = value;
}
Expression* cdr(Expression* expr) {
    return expr->list->cdr;
}
void setcdr(Expression *expr, Expression* value) {
    expr->list->cdr = value;
}
Expression* cons(Expression *car, Expression *cdr) {
    Expression::List *myList = new Expression::List();
    myList->car = car;
    myList->cdr = cdr;
    Expression* consObj = new Expression(myList);
    return consObj;
}
bool isList(Expression *expr) { return expr->exprType_ == LIST; }
bool isAtom(Expression *expr) { return expr->exprType_ == ATOM; }
bool isBool(Expression *expr) { return isAtom(expr) && expr->atom.atomType_ == BOOL; }
bool isNum(Expression *expr) { return isAtom(expr) && expr->atom.atomType_ == NUM; }
bool isChar(Expression *expr) { return isAtom(expr) && expr->atom.atomType_ == CHAR; }
bool isString(Expression *expr) { return isAtom(expr) && expr->atom.atomType_ == STR; }
bool isSymbol(Expression *expr) { return isAtom(expr) && expr->atom.atomType_ == SYMBOL; }
bool isPrimProc(Expression *expr) { return isAtom(expr) && expr->atom.atomType_ == PRIM_PROC; }
bool isCompProc(Expression *expr) { return isAtom(expr) && expr->atom.atomType_ == COMP_PROC; }


bool isTrue(Expression *expr) { return expr == _true; }
bool isFalse(Expression *expr) { return expr == _false; }

bool isEmptyList(Expression *expr) {
    return isList(expr) && (expr->list == nullptr);
}

