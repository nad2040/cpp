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

/* //recursion inside ostream seems not working
std::ostream& operator<<(std::ostream& os, const Atom& atom) {
    atom.print(os);
    return os;
}

void Atom::print(std::ostream& os) const {
    os << "atomtype:" << atomType_ << '\n';
    switch (atomType_) {
        case BOOL:
        case SYMBOL:
        case NUM:
        case PRIM_PROC:
        case COMP_PROC:
        case EOF_OBJECT:
            os << atomValue_;
            break;
        case CHAR:
        {
            char c = atomValue_[0];
            os << "#\\";
            switch (c) {
                case '\n':
                    os << "newline";
                    break;
                case ' ':
                    os << "space";
                    break;
                default:
                    os << c;
            }
        } break;
        case STR:
        {
            std::string str = atomValue_;
            int i=0;
            char c;
            os << '"';
            while ((c = str[i++]) != '\0') {
                switch (c) {
                    case '\n':
                        os << "\\n";
                        break;
                    case '\\':
                        os << "\\\\";
                        break;
                    case '"':
                        os << "\\\"";
                        break;
                    default:
                        os << c;
                }
            }
            os << '"';
        } break;
        default:
            std::cerr << "cannot write unknown atom type\n"; exit(1);
    }
    os.flush();
}

std::ostream& operator<<(std::ostream& os, const Expression& expr) {
    expr.print(os);
    return os;
}

void Expression::print(std::ostream& os) const {
    os << "exprtype:" << exprType_ << '\n';
    if (exprType_ == ATOM)
        os << ' ' << atom;
    else if (exprType_ == LIST) {
        if (list && list->car && list->cdr)
            os << '(' << *(list->car) << ' ' << *(list->cdr) << ')';
        else 
            os << "list object has nullptr inside\n";
    }
    else
        std::cerr << "cannot write unknown expressoin type\n"; exit(1);
    os.flush();
}
*/