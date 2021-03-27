#pragma once
#include "env.h"

inline Expression *_false;
inline Expression *_true;
inline Expression *eof_object;

inline Expression *symbol_table;

inline theEnv *the_env;

inline void init() {
    _false = new Expression(Atom(false));
    _true = new Expression(Atom(true));

    symbol_table = Expression::getEmptyList();
    eof_object = makeEOF();

    the_env = new theEnv();
}
