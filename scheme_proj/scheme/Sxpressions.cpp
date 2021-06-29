#include <string>
#include "Sxpressions.h"

bool isInitial(char c) {
    return isalpha(c) || c == '*' || c == '/' || c == '>' || c == '<' || c == '=' || c == '?' || c == '!';
}

bool isSym(std::string &str) {
    char c; int i=0;
    while (isInitial(c = str[i]) || isdigit(c) || c == '+' || c == '-') {
        i++;
    }
    return i == str.length();
}

Expression* car(Expression* expr) {
    return expr->car();
}
void setcar(Expression *expr, Expression* value) {
    expr->setCar(value);
}
Expression* cdr(Expression* expr) {
    if (!expr || !expr->cdr()) return nullptr;
    return expr->cdr();
}
void setcdr(Expression *expr, Expression* value) {
    expr->setCdr(value);
}
Expression* cons(Expression *car, Expression *cdr) {
    Expression::List myList {car, cdr};
    Expression* consObj = new Expression(myList);
    return consObj;
}

bool isList(Expression *expr) { return expr && expr->isList(); }
bool isAtom(Expression *expr) { return expr && expr->isAtom(); }
bool isEmptyList(Expression *expr) { return isList(expr) && expr->car() == nullptr && expr->cdr() == nullptr; }

bool isBool(Expression *expr) { return isAtom(expr) && expr->get<Atom>().isBool(); }
bool isNum(Expression *expr) { return isAtom(expr) && expr->get<Atom>().isNum(); }
bool isChar(Expression *expr) { return isAtom(expr) && expr->get<Atom>().isChar(); }
bool isString(Expression *expr) { return isAtom(expr) && expr->get<Atom>().isString(); }
bool isSymbol(Expression *expr) { return isAtom(expr) && expr->get<Atom>().isSymbol(); }
bool isPrimProc(Expression *expr) { return isAtom(expr) && expr->get<Atom>().isPrimProc(); }
bool isCompProc(Expression *expr) { return isAtom(expr) && expr->get<Atom>().isCompProc(); }
bool isInputPort(Expression *expr) { return isAtom(expr) && expr->get<Atom>().isInputPort(); }
bool isOutputPort(Expression *expr) { return isAtom(expr) && expr->get<Atom>().isOutputPort(); }
bool isEOFObject(Expression *expr) { return expr == Expression::eof_object(); }

bool isFalse(Expression *expr) { return expr == Expression::_false(); }
bool isTrue(Expression *expr) { return !isFalse(expr); }

Expression* makeSymbol(std::string value) {
    static Expression *symbol_table = Expression::empty_list();
    Expression *element = symbol_table;
    /* search for they symbol in the symbol table */
    while (!isEmptyList(element)) {
        if (car(element)->get<Atom>().get<Symbol>().symbol == value) {
            return car(element);
        }
        element = cdr(element);
    }
    
    /* create the symbol and add it to the symbol table */
    Expression *symbol = new Expression(Atom(Symbol{value}));
    symbol_table = cons(symbol, symbol_table);

    return symbol;
}

Expression* makePrimProc(Expression *(*fn)(Expression *args)) { return new Expression(Atom(fn)); }
