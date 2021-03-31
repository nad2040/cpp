#pragma once
#include <string>
#include <iostream>
#include <fstream>

bool isInitial(char c); 
bool isSym(std::string &str);

class Expression;
enum AtomType {UNK, BOOL, NUM, CHAR, STR, SYMBOL, PRIM_PROC, COMP_PROC, INPUT, OUTPUT, EOF_OBJECT};
class Atom {
public:
    struct Compound {
        Expression *params;
        Expression *body;
        Expression *env;
        Compound() : params(nullptr), body(nullptr), env(nullptr) {}
        Compound(Expression* p, Expression* b, Expression* e) : params(p), body(b), env(e) {}
    };

    AtomType atomType_;
    std::string atomValue_;
    Expression *(*fn)(Expression* args);
    Compound compound_proc;
    std::ifstream* in_port;
    std::ofstream* out_port;

    Atom() :
        atomType_(UNK), atomValue_(""),
        fn(nullptr), compound_proc(),
        in_port(nullptr), out_port(nullptr) {}

    Atom(long num) :
        atomType_(NUM), atomValue_(std::to_string(num)),
        fn(nullptr), compound_proc(),
        in_port(nullptr), out_port(nullptr) {}

    Atom(std::string str) :
        fn(nullptr), compound_proc(),
        in_port(nullptr), out_port(nullptr) {
        if (str[0] == '"') { atomType_ = STR; str.erase(0,1); atomValue_ = str; }
        else if (isSym(str)) { atomType_ = SYMBOL; atomValue_ = str; }
        else { atomType_ = UNK; atomValue_ = str; }
    }
    Atom(bool b) :
        atomType_(BOOL), atomValue_((b == true) ? "#t" : "#f"),
        fn(nullptr), compound_proc(),
        in_port(nullptr), out_port(nullptr) {}

    Atom(char c) : fn(nullptr), compound_proc(),
        in_port(nullptr), out_port(nullptr) {
        if (c == ' ' || c == '\n' || isalpha(c) || isdigit(c)) {
            atomType_ = CHAR;
            atomValue_ = c;
        } else atomType_ = UNK;
    }
    Atom(Expression* (*fnptr)(Expression* args)) :
        atomType_(PRIM_PROC), atomValue_("#<prim-proc>"),
        fn(fnptr), compound_proc(),
        in_port(nullptr), out_port(nullptr) {}

    Atom(Expression* _params, Expression* _body, Expression* _env) :
        atomType_(COMP_PROC), atomValue_("#<comp-proc>"),
        fn(nullptr), compound_proc(_params,_body,_env),
        in_port(nullptr), out_port(nullptr) {}

    Atom(std::ifstream& in) :
        atomType_(INPUT), atomValue_("#<input-port>"),
        fn(nullptr), compound_proc(),
        in_port(&in), out_port(nullptr) {}

    Atom(std::ofstream& out) :
        atomType_(OUTPUT), atomValue_("#<output-port>"),
        fn(nullptr), compound_proc(),
        in_port(nullptr), out_port(&out) {}

    std::string getValue() { return atomValue_; }
    long getInt() {
        switch (atomType_) {
            case NUM:
                return stol(atomValue_);
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
};

Expression* car(Expression* expr);
void setcar(Expression *expr, Expression* value);
Expression* cdr(Expression* expr);
void setcdr(Expression *expr, Expression* value);
Expression* cons(Expression *car, Expression *cdr);
bool isList(Expression *expr);
bool isAtom(Expression *expr);
bool isBool(Expression *expr);
bool isNum(Expression *expr);
bool isChar(Expression *expr);
bool isString(Expression *expr);
bool isSymbol(Expression *expr);
bool isPrimProc(Expression *expr);
bool isCompProc(Expression *expr);

bool isTrue(Expression *expr);
bool isFalse(Expression *expr);
bool isEmptyList(Expression *expr);
bool isInputPort(Expression *expr);
bool isOutputPort(Expression *expr);
bool isEOFObject(Expression *expr);

Expression* makeSymbol(std::string value);
Expression* makeEOF();
Expression* makePrimProc(Expression *(*fn)(Expression *args));

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