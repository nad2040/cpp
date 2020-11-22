#include <string>
using namespace std;

bool isInitial(char c) {
    return ( c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') || c == '*' || c == '/' ||
             c == '>' || c == '<' || c == '=' || c == '?' || c == '!';
}
bool isSym(string &str) {
    char c; int i=0;
    while (isInitial(c = str[i])) {
        i++;
    }
    return i == str.length();
}

enum AtomType {UNK, BOOL, SYMBOL, NUM, CHAR, STR};
class Atom {
public:
    string atomValue_;
    AtomType atomType_;

    string getValue() {
        return atomValue_;
    }

    Atom() : atomType_(UNK), atomValue_("") {}
    Atom(int num) {
        atomType_ = NUM;
        atomValue_ = to_string(num);
    }
    Atom(string str) {
        if (str[0] == '"') { atomType_ = STR; str.erase(0,1); atomValue_ = str; }
        else if (isSym(str)) { atomType_ = SYMBOL; atomValue_ = str; }
        else { atomType_ = UNK; atomValue_ = str; }
    }
    Atom(bool b) {
        atomValue_ = (b == true) ? "#t" : "#f";
        atomType_ = BOOL;
    }
    Atom(char c) {
        if (c == ' ' || c == '\n') {
            atomType_ = CHAR;
            atomValue_ = c;
        } else if ((c >= 'a' && c <= 'z') ||
                   (c >= 'A' && c <= 'Z') ||
                   (c >= '0' && c <= '9')) {
            atomType_ = CHAR;
            atomValue_ += c;
        }
        else atomType_ = UNK;
    }
};

enum ExpressionType {ATOM, LIST};
class Expression {
public:
    struct List {
        Expression* car;
        Expression* cdr;
    };

    Atom atom;
    List *list;
    ExpressionType exprType_;

    Expression() : atom(), list(), exprType_(LIST) {}
    Expression(Atom atom_) : atom(atom_), list(nullptr), exprType_(ATOM) {}
    Expression(List* list_) : atom(), list(list_), exprType_(LIST) {}

    void display(int ind) {
        if (exprType_ == ATOM) {
            for (int i=0; i<ind; i++) cout << "    ";
            cout << atom.getValue() << '\n';
        }
        else {
            if (list != nullptr) {
                this->list->car->display(ind+1);
                this->list->cdr->display(ind);
            } else {
                for (int i=0; i<ind; i++) cout << "    ";
                cout << "()\n";
            }
        }
    }
};

bool isList(Expression *expr) { return expr->exprType_ == LIST; }
bool isAtom(Expression *expr) { return expr->exprType_ == ATOM; }
bool isBool(Expression *expr) { return isAtom(expr) && expr->atom.atomType_ == BOOL; }
bool isNum(Expression *expr) { return isAtom(expr) && expr->atom.atomType_ == NUM; }
bool isChar(Expression *expr) { return isAtom(expr) && expr->atom.atomType_ == CHAR; }
bool isString(Expression *expr) { return isAtom(expr) && expr->atom.atomType_ == STR; }
bool isSymbol(Expression *expr) { return isAtom(expr) && expr->atom.atomType_ == SYMBOL; }

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

#define caar(obj)   car(car(obj))
#define cadr(obj)   car(cdr(obj))
#define cdar(obj)   cdr(car(obj))
#define cddr(obj)   cdr(cdr(obj))
#define caaar(obj)  car(car(car(obj)))
#define caadr(obj)  car(car(cdr(obj)))
#define cadar(obj)  car(cdr(car(obj)))
#define caddr(obj)  car(cdr(cdr(obj)))
#define cdaar(obj)  cdr(car(car(obj)))
#define cdadr(obj)  cdr(car(cdr(obj)))
#define cddar(obj)  cdr(cdr(car(obj)))
#define cdddr(obj)  cdr(cdr(cdr(obj)))
#define caaaar(obj) car(car(car(car(obj))))
#define caaadr(obj) car(car(car(cdr(obj))))
#define caadar(obj) car(car(cdr(car(obj))))
#define caaddr(obj) car(car(cdr(cdr(obj))))
#define cadaar(obj) car(cdr(car(car(obj))))
#define cadadr(obj) car(cdr(car(cdr(obj))))
#define caddar(obj) car(cdr(cdr(car(obj))))
#define cadddr(obj) car(cdr(cdr(cdr(obj))))
#define cdaaar(obj) cdr(car(car(car(obj))))
#define cdaadr(obj) cdr(car(car(cdr(obj))))
#define cdadar(obj) cdr(car(cdr(car(obj))))
#define cdaddr(obj) cdr(car(cdr(cdr(obj))))
#define cddaar(obj) cdr(cdr(car(car(obj))))
#define cddadr(obj) cdr(cdr(car(cdr(obj))))
#define cdddar(obj) cdr(cdr(cdr(car(obj))))
#define cddddr(obj) cdr(cdr(cdr(cdr(obj))))