#include <string>
#include "Expression.h"

Expression* car(Expression* expr) {
    return expr->car();
}
void setcar(Expression *expr, Expression* value) {
    expr->setcar(value);
}
Expression* cdr(Expression* expr) {
    if (!expr || !expr->cdr()) return nullptr;
    return expr->cdr();
}
void setcdr(Expression *expr, Expression* value) {
    expr->setcdr(value);
}
Expression* cons(Expression *car, Expression *cdr) {
    return new Expression(car,cdr);
}

bool isList(Expression *expr) { return expr && expr->isList(); }
bool isAtom(Expression *expr) { return expr && expr->isAtom(); }
bool isEmptyList(Expression *expr) { return isList(expr) && expr->car() == nullptr && expr->cdr() == nullptr; }

bool isBool(Expression *expr) { return isAtom(expr) && expr->isBool(); }
bool isNum(Expression *expr) { return isAtom(expr) && expr->isNum(); }
bool isChar(Expression *expr) { return isAtom(expr) && expr->isChar(); }
bool isString(Expression *expr) { return isAtom(expr) && expr->isString(); }
bool isSymbol(Expression *expr) { return isAtom(expr) && expr->isSymbol(); }
bool isPrimProc(Expression *expr) { return isAtom(expr) && expr->isPrimProc(); }
bool isCompProc(Expression *expr) { return isAtom(expr) && expr->isCompProc(); }
bool isInputPort(Expression *expr) { return isAtom(expr) && expr->isInputPort(); }
bool isOutputPort(Expression *expr) { return isAtom(expr) && expr->isOutputPort(); }
bool isEOFObject(Expression *expr) { return expr == Expression::eof_object(); }

bool isFalse(Expression *expr) { return expr == Expression::_false(); }
bool isTrue(Expression *expr) { return !isFalse(expr); }

Expression* Expression::makeSymbol(std::string value) {
    static Expression *symbol_table = Expression::empty_list();
    Expression *element = symbol_table;
    /* search for the symbol in the symbol table */
    while (!isEmptyList(element)) {
        if (element->car()->data.symbol.val == value) {
            return element->data.list.car;
        }
        element = element->data.list.cdr;
    }
    
    /* create the symbol and add it to the symbol table */
    Expression *symbol = new Expression(value, true);
    symbol_table = cons(symbol, symbol_table);

    return symbol;
}
