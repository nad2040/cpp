#pragma once
#include "env.h"

//inline Expression *empty_list;
inline Expression *_false;
inline Expression *_true;
inline Expression *quote_symbol;
inline Expression *symbol_table;
inline Expression *define_symbol;
inline Expression *set_symbol;
inline Expression *ok_symbol;
inline Expression *if_symbol;
inline Expression *lambda_symbol;
inline Expression *begin_symbol;
inline Expression *cond_symbol;
inline Expression *else_symbol;
inline Expression *let_symbol;
inline Expression *and_symbol;
inline Expression *or_symbol;
inline Expression *eof_object;

inline theEnv *the_env;

inline void init() {
    //empty_list = new Expression();
    _false = new Expression(Atom(false));
    _true = new Expression(Atom(true));

    symbol_table = Expression::getEmptyList();
    quote_symbol = makeSymbol("quote");
    define_symbol = makeSymbol("define");
    set_symbol = makeSymbol("set!");
    ok_symbol = makeSymbol("ok");
    if_symbol = makeSymbol("if");
    lambda_symbol = makeSymbol("lambda");
    begin_symbol = makeSymbol("begin");
    cond_symbol = makeSymbol("cond");
    else_symbol = makeSymbol("else");
    let_symbol = makeSymbol("let");
    and_symbol = makeSymbol("and");
    or_symbol = makeSymbol("or");

    eof_object = makeEOF();

    the_env = new theEnv();
}
