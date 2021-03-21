#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <variant>
#include <cassert>

bool isInitial(char c); 
bool isSym(std::string &str);

class Expression;
enum AtomType {UNK, BOOL, SYMBOL, NUM, CHAR, STR, PRIM_PROC, COMP_PROC, INPUT, OUTPUT, EOF_OBJECT};
class Atom {
public:
    AtomType atomType_;
    struct Compound {
        Expression *params;
        Expression *body;
        Expression *env;
        bool operator==(const Compound& c) const { return params == c.params && body == c.body && env == c.env; }
    };
    typedef Expression *(*Primitive)(Expression* args);
    std::variant<char, long, std::string, Primitive, Compound, std::ifstream*, std::ofstream*> value_;
    std::string atomValue_;

    bool operator==(const Atom& a) const {
        if (atomType_ != a.atomType_) return false;
        switch(atomType_) {
            case UNK: return false;
            case BOOL: 
            case CHAR: return std::get<char>(value_) == std::get<char>(a.value_);
            case SYMBOL:
            case STR: return std::get<std::string>(value_) == std::get<std::string>(a.value_);
            case NUM: return std::get<long>(value_) == std::get<long>(a.value_);
            case INPUT: return std::get<std::ifstream*>(value_) == std::get<std::ifstream*>(a.value_);
            case OUTPUT: return std::get<std::ofstream*>(value_) == std::get<std::ofstream*>(a.value_);
            case PRIM_PROC: return std::get<Primitive>(value_) == std::get<Primitive>(a.value_);
            case COMP_PROC: return std::get<Compound>(value_) == std::get<Compound>(a.value_);
        }
        return false;
    }

    Atom() : atomType_(UNK), atomValue_(""), value_() {}

    Atom(long num) : atomType_(NUM), atomValue_(std::to_string(num)), value_(num) {}

    Atom(std::string str) {
        if (str[0] == '"') { atomType_ = STR; value_ = str.substr(1, str.size()-2); atomValue_ = str.substr(1, str.size()-2); }
        else if (isSym(str)) { atomType_ = SYMBOL; atomValue_ = str; value_ = str; }
        else { atomType_ = UNK; atomValue_ = str; }
    }

    Atom(bool b) : atomType_(BOOL), atomValue_((b == true) ? "#t" : "#f"), value_((char)b) {}

    Atom(char c) : atomType_(CHAR), atomValue_(1, c), value_(c) {}

    Atom(Primitive fnptr) : atomType_(PRIM_PROC), atomValue_("#<procedure>"), value_(fnptr) {}

    Atom(Expression* _params, Expression* _body, Expression* _env) : atomType_(COMP_PROC), atomValue_("#<procedure>") {
        value_ = Compound{_params, _body, _env};
    }

    Atom(std::ifstream* in) : atomType_(INPUT), atomValue_("#<input-port>"), value_(in) {}

    Atom(std::ofstream* out) : atomType_(OUTPUT), atomValue_("#<output-port>"), value_(out) {}

    std::string getValue() { return atomValue_; }

    long getInt() {
        switch (atomType_) {
            case NUM:
                return std::get<long>(value_);
            case BOOL:
                return std::get<char>(value_);
            default:
                return 0;
        }
        return stoi(atomValue_); //???
    }

    bool getBool() {
        assert(atomType_ == BOOL);
        return std::get<char>(value_);
    }

    std::ifstream* in_port() {
        assert(atomType_ == INPUT);
        return std::get<std::ifstream*>(value_);
    }

    std::ofstream* out_port() {
        assert(atomType_ == OUTPUT);
        return std::get<std::ofstream*>(value_);
    }

    Primitive primitive() {
        assert(atomType_ == PRIM_PROC);
        return std::get<Primitive>(value_);
    }

    Compound compound() {
        assert(atomType_ == COMP_PROC);
        return std::get<Compound>(value_);
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

