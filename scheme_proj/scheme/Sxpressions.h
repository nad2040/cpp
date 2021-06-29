#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <variant>
#include <tuple>

bool isInitial(char c); 
bool isSym(std::string &str);

class Expression;

Expression* makeSymbol(std::string value);
struct Symbol { 
    std::string symbol;
    static Expression *quote_symbol() { return makeSymbol("quote"); }
    static Expression *define_symbol() { return makeSymbol("define"); }
    static Expression *set_symbol() { return makeSymbol("set!"); }
    static Expression *ok_symbol() { return makeSymbol("ok"); }
    static Expression *if_symbol() { return makeSymbol("if"); }
    static Expression *lambda_symbol() { return makeSymbol("lambda"); }
    static Expression *begin_symbol() { return makeSymbol("begin"); }
    static Expression *cond_symbol() { return makeSymbol("cond"); }
    static Expression *else_symbol() { return makeSymbol("else"); }
    static Expression *let_symbol() { return makeSymbol("let"); }
    static Expression *and_symbol() { return makeSymbol("and"); }
    static Expression *or_symbol() { return makeSymbol("or"); }

    friend std::ostream& operator<< (std::ostream& os, const Symbol& s) {
        os << s.symbol;
        return os;
    }
};

using Primitive = Expression *(*)(Expression* args);
struct Compound {
    Expression *params;
    Expression *body;
    Expression *env;
    
    Compound() : params(nullptr), body(nullptr), env(nullptr) {}
    Compound(Expression* p, Expression* b, Expression* e) : params(p), body(b), env(e) {}

    bool operator==(const Compound& c) const {
        return params == c.params && body == c.body && env == c.env;
    }
    friend std::ostream& operator<< (std::ostream& os, const Compound& c) {
        os << c.params << c.body << c.env;
        return os;
    }
};

using var_t = std::variant<bool, long, char, std::string, Symbol, Primitive, Compound, std::ifstream*, std::ofstream*>;
enum AtomType {UNK, BOOL, NUM, CHAR, STR, SYMBOL, PRIM_PROC, COMP_PROC, INPUT, OUTPUT, EOF_OBJECT};
class Atom {
public:
    AtomType atomType_;
    var_t atomValue_;

    Atom() : atomType_(UNK), atomValue_() {}
    Atom(long num) : atomType_(NUM), atomValue_(num) {}
    Atom(bool b) : atomType_(BOOL), atomValue_(b) {}
    Atom(char c) : atomType_(CHAR), atomValue_(c) {}
    Atom(std::string str) : atomType_(STR), atomValue_(str) {}
    Atom(Symbol sym) : atomType_(SYMBOL), atomValue_(sym) {}
    Atom(std::ifstream* in) : atomType_(INPUT), atomValue_(in) {}
    Atom(std::ofstream* out) : atomType_(OUTPUT), atomValue_(out) {}
    Atom(Primitive fnptr) : atomType_(PRIM_PROC), atomValue_(fnptr) {}
    Atom(Expression* _params, Expression* _body, Expression* _env) : atomType_(COMP_PROC), atomValue_(Compound{_params, _body, _env}) {}

    bool operator==(const Atom& a) const {
        if (atomType_ != a.atomType_) return false;
        switch(atomType_) {
            case UNK: return false;
            case BOOL: return std::get<bool>(atomValue_) == std::get<bool>(a.atomValue_);
            case CHAR: return std::get<char>(atomValue_) == std::get<char>(a.atomValue_);
            case SYMBOL: return std::get<Symbol>(atomValue_).symbol == std::get<Symbol>(atomValue_).symbol;
            case STR: return std::get<std::string>(atomValue_) == std::get<std::string>(a.atomValue_);
            case NUM: return std::get<long>(atomValue_) == std::get<long>(a.atomValue_);
            case INPUT: return std::get<std::ifstream*>(atomValue_) == std::get<std::ifstream*>(a.atomValue_);
            case OUTPUT: return std::get<std::ofstream*>(atomValue_) == std::get<std::ofstream*>(a.atomValue_);
            case PRIM_PROC: return std::get<Primitive>(atomValue_) == std::get<Primitive>(a.atomValue_);
            case COMP_PROC: return std::get<Compound>(atomValue_) == std::get<Compound>(a.atomValue_);
            case EOF_OBJECT: return true;
        }
        return false;
    }

    void withType(AtomType t) { atomType_ = t; }

    template<typename T>
    T get() { return std::get<T>(atomValue_); }

    bool isBool() { return atomType_ == BOOL; }
    bool isNum() { return atomType_ == NUM; }
    bool isChar() { return atomType_ == CHAR; }
    bool isString() { return atomType_ == STR; }
    bool isSymbol() { return atomType_ == SYMBOL; }
    bool isPrimProc() { return atomType_ == PRIM_PROC; }
    bool isCompProc() { return atomType_ == COMP_PROC; }
    bool isInputPort() { return atomType_ == INPUT; }
    bool isOutputPort() { return atomType_ == OUTPUT; }
};

enum ExpressionType {ATOM, LIST};
class Expression {
public:
    struct List {
        Expression* car;
        Expression* cdr;
    };

    std::variant<Atom, List> value_;
    ExpressionType exprType_;

    Expression() : value_(List{nullptr, nullptr}), exprType_(LIST) {}
    Expression(Atom atom) : value_(atom), exprType_(ATOM) {}
    Expression(List list) : value_(list), exprType_(LIST) {}

    template<typename T>
    T get() { return std::get<T>(value_); }

    Expression* car() {
        return std::get<List>(value_).car;
    }
    void setCar(Expression* value) {
        std::get<List>(value_).car = value;
    }
    Expression* cdr() {
        return std::get<List>(value_).cdr;
    }
    void setCdr(Expression* value) {
        std::get<List>(value_).cdr = value;
    }

    static Expression* empty_list() {
        static Expression* empty_list = new Expression();
        return empty_list;
    }
    static Expression* _false() {
        static Expression* _false = new Expression(Atom(false));
        return _false;
    }
    static Expression* _true() {
        static Expression* _true = new Expression(Atom(true));
        return _true;
    }
    static Expression* eof_object() {
        static Expression* eof_object = makeEOF();
        return eof_object;
    }

    bool isAtom() { return exprType_ == ATOM; }
    bool isList() { return exprType_ == LIST; }
    
private:
    static Expression* makeEOF() {
        static Expression* expr = new Expression(Atom());
        expr->get<Atom>().withType(EOF_OBJECT);
        return expr;
    }
};

Expression* car(Expression* expr);
void setcar(Expression *expr, Expression* value);
Expression* cdr(Expression* expr);
void setcdr(Expression *expr, Expression* value);
Expression* cons(Expression *car, Expression *cdr);

bool isList(Expression *expr);
bool isAtom(Expression *expr);
bool isEmptyList(Expression *expr);

bool isBool(Expression *expr);
bool isNum(Expression *expr);
bool isChar(Expression *expr);
bool isString(Expression *expr);
bool isSymbol(Expression *expr);
bool isPrimProc(Expression *expr);
bool isCompProc(Expression *expr);
bool isInputPort(Expression *expr);
bool isOutputPort(Expression *expr);
bool isEOFObject(Expression *expr);

bool isTrue(Expression *expr);
bool isFalse(Expression *expr);

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