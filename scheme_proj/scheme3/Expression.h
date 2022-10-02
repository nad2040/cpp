#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <variant>

enum ExpressionType {LIST, BOOL, NUM, CHAR, STRING, SYMBOL, PRIM_PROC, COMP_PROC, INPUT, OUTPUT, EOF_OBJECT, EMPTY_LIST};
class Expression {
public:
    ExpressionType type;
    union Data {
        // Atom Types
        bool boolean;
        long number;
        char character;
        struct { std::string val; } string;
        struct { std::string val; } symbol;
        struct { std::ifstream *stream; } input;
        struct { std::ofstream *stream; } output;
        struct { Expression *(*func)(Expression*); } primitive; // primitive functions
        struct { Expression *params, *body, *env;  } compound;   // compound functions / lambdas
        
        struct { Expression *car, *cdr; } list; // List of sub-expressions Type

        Data() {}
        ~Data() {}
    } data;

    Expression() : type(LIST) {
        data.list.car = nullptr;
        data.list.cdr = nullptr;
    }
    Expression(Expression *car, Expression *cdr) : type(LIST) {
        data.list.car = car;
        data.list.cdr = cdr;
    }
    Expression(bool b) : type(BOOL) {
        data.boolean = b;
    }
    Expression(long n) : type(NUM) {
        data.number = n;
    }
    Expression(char c) : type(CHAR) {
        data.character = c;
    }
    Expression(std::string str, bool isSymbol) {
        // https://stackoverflow.com/questions/3521914/why-compiler-doesnt-allow-stdstring-inside-union#:~:text=you%20have%20to%20call%20the%20constructor%20directly%20on%20that%20memory%3A
        if (isSymbol) {
            type = SYMBOL;
            new(&data.symbol.val) std::string(str);
        } else {
            type = STRING;
            new(&data.string.val) std::string(str);
        }
    }
    Expression(std::ifstream *in) : type(INPUT) {
        data.input.stream = in;
    }
    Expression(std::ofstream *out) : type(OUTPUT) {
        data.output.stream = out;
    }
    Expression(Expression *(*fnptr)(Expression*)) : type(PRIM_PROC) {
        data.primitive.func = fnptr;
    }
    Expression(Expression *params, Expression *body, Expression *env) : type(COMP_PROC) {
        data.compound.params = params;
        data.compound.body = body;
        data.compound.env = env;
    }

    bool operator==(const Expression& expr) const {
        if (type != expr.type) return false;
        else {
            switch (type) {
                case BOOL:      return data.boolean == expr.data.boolean;
                case NUM:       return data.number == expr.data.number;
                case CHAR:      return data.character == expr.data.character;
                case STRING:    return data.string.val == expr.data.string.val;
                case SYMBOL:    return data.symbol.val == expr.data.symbol.val;
                case PRIM_PROC: return data.primitive.func == expr.data.primitive.func;
                case COMP_PROC: return data.compound.params == expr.data.compound.params && data.compound.body == expr.data.compound.body && data.compound.env == expr.data.compound.env;
                case INPUT:     return data.input.stream == expr.data.input.stream;
                case OUTPUT:    return data.output.stream == expr.data.output.stream;
                case LIST:      return data.list.car == expr.data.list.car && data.list.cdr == expr.data.list.cdr;
                default: std::cerr << "unknown expression"; exit(1);
            }
        }
    }
    // friend std::ostream& operator<< (std::ostream& os, const Expression& expr) {
    //     os << c.params << c.body << c.env;
    //     return os;
    // }

    bool isBool() { return type == BOOL; }
    bool isNum() { return type == NUM; }
    bool isChar() { return type == CHAR; }
    bool isString() { return type == STRING; }
    bool isSymbol() { return type == SYMBOL; }
    bool isPrimProc() { return type == PRIM_PROC; }
    bool isCompProc() { return type == COMP_PROC; }
    bool isInputPort() { return type == INPUT; }
    bool isOutputPort() { return type == OUTPUT; }

    bool isList() { return type == LIST || type == EMPTY_LIST; }
    bool isAtom() { return !isList(); }

    Expression* car() {
        return data.list.car;
    }
    void setcar(Expression* value) {
        data.list.car = value;
    }
    Expression* cdr() {
        return data.list.cdr;
    }
    void setcdr(Expression* value) {
        data.list.cdr = value;
    }

    static Expression* _false() {
        static Expression* _false = new Expression(false);
        return _false;
    }
    static Expression* _true() {
        static Expression* _true = new Expression(true);
        return _true;
    }
    static Expression* empty_list() {
        static Expression* empty_list = new Expression();
        empty_list->type = EMPTY_LIST;
        return empty_list;
    }
    static Expression* eof_object() {
        static Expression* eof_object = new Expression();
        eof_object->type = EOF_OBJECT;
        return eof_object;
    }

    static Expression *makeSymbol(std::string value);

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