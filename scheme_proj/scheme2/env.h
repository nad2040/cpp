#pragma once
#include "Sxpressions.h"

extern Expression* empty_list;

class theEnv {
public:
    theEnv() {
        empty_env = empty_list;
        global_env = makeEnv();
    }

    //required by primitive
    Expression* setupEnv(); //nullEnvProc
    Expression* makeEnv(); //envProc

    //required by eval
    Expression* extendEnv(Expression *vars, Expression *vals, Expression *base_env); 
    Expression* lookupVarValue(Expression *var, Expression *env); 
    void defVar(Expression *var, Expression *val, Expression *env); 
    void setVarValue(Expression *var, Expression *val, Expression *env); 

    Expression* empty_env;
    Expression* global_env;

private:
    void populateEnv(Expression* env);

    Expression* makeFrame(Expression *variables, Expression *values);
    Expression* frameVar(Expression *frame); 
    Expression* frameValues(Expression *frame); 
    void addBindingToFrame(Expression *var, Expression *val, Expression *frame); 
    Expression* enclosingEnvironment(Expression *env);
    Expression* firstFrame(Expression *env); 
};

