#pragma once
#include "Expression.h"

class theEnv {
public:
    //required by primitive
    static Expression* setupEnv(); //nullEnvProc
    static Expression* makeEnv(); //envProc

    //required by eval
    static Expression* extendEnv(Expression *vars, Expression *vals, Expression *base_env); 
    static Expression* lookupVarValue(Expression *var, Expression *env); 
    static void defVar(Expression *var, Expression *val, Expression *env); 
    static void setVarValue(Expression *var, Expression *val, Expression *env); 

    static Expression* global_env() {
        static Expression* global_env = makeEnv();
        return global_env;
    }
    static Expression* empty_env() {
        return Expression::empty_list();
    }

private:
    static void populateEnv(Expression* env);

    static Expression* makeFrame(Expression *variables, Expression *values);
    static Expression* frameVar(Expression *frame); 
    static Expression* frameValues(Expression *frame); 
    static void addBindingToFrame(Expression *var, Expression *val, Expression *frame); 
    static Expression* enclosingEnvironment(Expression *env);
    static Expression* firstFrame(Expression *env); 

    static Expression* interactionEnvProc(Expression *args);
    static Expression* nullEnvProc(Expression *args);
    static Expression* envProc(Expression *args);
};

