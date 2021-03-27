#pragma once
#include "Sxpressions.h"

extern Expression* empty_list;

class theEnv {
public:
    theEnv() {
        empty_env = empty_list;
        global_env = makeEnv();
    }
    Expression* setupEnv(); 
    void populateEnv(Expression* env);
    Expression* makeEnv();

    Expression* extendEnv(Expression *vars, Expression *vals, Expression *base_env); 
    Expression* makeFrame(Expression *variables, Expression *values);
    Expression* frameVar(Expression *frame); 
    Expression* frameValues(Expression *frame); 
    void addBindingToFrame(Expression *var, Expression *val, Expression *frame); 
    Expression* enclosingEnvironment(Expression *env);
    Expression* firstFrame(Expression *env); 

    Expression* lookupVarValue(Expression *var, Expression *env); 
    void setVarValue(Expression *var, Expression *val, Expression *env); 
    void defVar(Expression *var, Expression *val, Expression *env); 

    Expression* empty_env;
    Expression* global_env;
/*
private:
    Expression* env_;
    */
};

