#include <string>
#include "Sxpressions.h"

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

bool isEmptyList(Expression *expr) { return isList(expr) && expr->getCar() == nullptr && expr->getCdr() == nullptr; }
//bool isEmptyList(Expression *expr) { return expr == getEmptyList(); }
bool isList(Expression *expr) { return expr && expr->exprType_ == Expression::LIST; }
bool isAtom(Expression *expr) { return expr && expr->exprType_ == Expression::ATOM; }
bool isBool(Expression *expr) { return isAtom(expr) && expr->getAtom().isBool(); }
bool isNum(Expression *expr) { return isAtom(expr) && expr->getAtom().isNum(); }
bool isChar(Expression *expr) { return isAtom(expr) && expr->getAtom().isChar(); }
bool isString(Expression *expr) { return isAtom(expr) && expr->getAtom().isString(); }
bool isSymbol(Expression *expr) { return isAtom(expr) && expr->getAtom().isSymbol(); }
bool isPrimProc(Expression *expr) { return isAtom(expr) && expr->getAtom().isPrimProc(); }
bool isCompProc(Expression *expr) { return isAtom(expr) && expr->getAtom().isCompProc(); }
bool isInputPort(Expression *expr) { return isAtom(expr) && expr->getAtom().isInputPort(); }
bool isOutputPort(Expression *expr) { return isAtom(expr) && expr->getAtom().isOutputPort(); }
bool isEOFObject(Expression *expr) { return expr && expr == Expression::eof_object(); }

bool isFalse(Expression *expr) { return expr == Expression::_false(); }
bool isTrue(Expression *expr) { return !isFalse(expr); }

Expression* makeSymbol(std::string value) {
    static Expression *symbol_table = Expression::getEmptyList();
    Expression *element = symbol_table;
    /* search for they symbol in the symbol table */
    while (element != nullptr) {
        assert(isList(element));
        Expression* first=car(element);
        if (first && isAtom(first) && first->getAtom().getSymbol() == value) {
            return first;
        }
        element = cdr(element);
    };
    
    /* create the symbol and add it to the symbol table */
    Expression *symbol = new Expression(Atom(Symbol{value}));
    symbol_table = cons(symbol, symbol_table);
    return symbol;
}

//special obj, one instance?
Expression* makeEOF() {
    Expression* expr = new Expression(Atom());
    expr->getAtom().atomType_ = Atom::EOF_OBJECT;
    return expr;
}

Expression* makePrimProc(Expression *(*fn)(Expression *args)) { return new Expression(Atom(fn)); }

