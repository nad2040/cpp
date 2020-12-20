#include <string>
using namespace std;

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

class Expression;

enum AtomType {UNK, BOOL, SYMBOL, NUM, CHAR, STR, PRIM_PROC, COMP_PROC};
class Atom {
public:
    struct Compound {
        Expression *params;
        Expression *body;
        Expression *env;
        Compound() : params(nullptr), body(nullptr), env(nullptr) {}
        Compound(Expression* p, Expression* b, Expression* e) : params(p), body(b), env(e) {}
    };

    string atomValue_;
    AtomType atomType_;
    Expression* (*fn)(Expression* args);
    Compound compound_proc;

    Atom() : atomType_(UNK), atomValue_(""), fn(nullptr), compound_proc() {}
    Atom(int num) : atomType_(NUM), atomValue_(to_string(num)), fn(nullptr), compound_proc() {}
    Atom(string str) : fn(nullptr), compound_proc() {
        if (str[0] == '"') { atomType_ = STR; str.erase(0,1); atomValue_ = str; }
        else if (isSym(str)) { atomType_ = SYMBOL; atomValue_ = str; }
        else { atomType_ = UNK; atomValue_ = str; }
    }
    Atom(bool b) : atomType_(BOOL), atomValue_((b == true) ? "#t" : "#f"), fn(nullptr), compound_proc() {}
    Atom(char c) : fn(nullptr), compound_proc() {
        if (c == ' ' || c == '\n' || isalpha(c) || isdigit(c)) {
            atomType_ = CHAR;
            atomValue_ = c;
        }
        else atomType_ = UNK;
    }
    Atom(Expression* (*fnptr)(Expression* args)) : atomType_(PRIM_PROC), atomValue_("#<procedure>"), fn(fnptr), compound_proc() {}
    Atom(Expression* _params, Expression* _body, Expression* _env) : atomType_(COMP_PROC), atomValue_("#<procedure>"), fn(nullptr), compound_proc(_params,_body,_env) {}

    string getValue() { return atomValue_; }
    int getInt() {
        switch (atomType_) {
            case NUM:
                return stoi(atomValue_);
            case BOOL:
                return (atomValue_ == "#t") ? 1 : 0;
            default:
                return 0;
        }
        return stoi(atomValue_);
    }
    bool getBool() {
        return atomValue_[1] == 't';
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