#include <string>
#include "Sxpressions.h"

extern Expression *_false;
extern Expression *_true;
extern Expression *symbol_table;
extern Expression *eof_object;

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

bool isFalse(Expression *expr) { return expr == _false; }
bool isTrue(Expression *expr) { return !isFalse(expr); }

bool isEmptyList(Expression *expr) { return isList(expr) && (expr->list == nullptr); }
bool isInputPort(Expression *expr) { return isAtom(expr) && expr->atom.atomType_ == INPUT; }
bool isOutputPort(Expression *expr) { return isAtom(expr) && expr->atom.atomType_ == OUTPUT; }
bool isEOFObject(Expression *expr) { return expr == eof_object; }

Expression* makeSymbol(std::string value) {
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
Expression* makeEOF() {
    Expression* expr = new Expression(Atom());
    expr->atom.atomType_ = EOF_OBJECT;
    expr->atom.atomValue_ = "#<eof>";
    return expr;
}
Expression* makePrimProc(Expression *(*fn)(Expression *args)) { return new Expression(Atom(fn)); }
