#pragma once
#include "env.h"

inline Expression *symbol_table;
inline theEnv *the_env;

inline void init() {
    symbol_table = Expression::getEmptyList();
    the_env = new theEnv();
}
