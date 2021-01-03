#pragma once
#include "Sxpressions.h"

Expression* enclosingEnvironment(Expression *env);
Expression* firstFrame(Expression *env); 
Expression* makeFrame(Expression *variables, Expression *values);
Expression* frameVar(Expression *frame); 
Expression* frameValues(Expression *frame); 

void addBindingToFrame(Expression *var, Expression *val, Expression *frame); 

Expression* extendEnv(Expression *vars, Expression *vals, Expression *base_env); 

Expression* lookupVarValue(Expression *var, Expression *env); 

void setVarValue(Expression *var, Expression *val, Expression *env); 

void defVar(Expression *var, Expression *val, Expression *env); 

Expression* setupEnv(); 
