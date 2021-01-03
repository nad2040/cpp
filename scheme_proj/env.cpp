#include "env.h"

extern Expression *empty_list;
extern Expression *empty_env;

Expression* enclosingEnvironment(Expression *env) {
    return cdr(env);
}
Expression* firstFrame(Expression *env) {
    return car(env);
}
Expression* makeFrame(Expression *variables, Expression *values) {
    return cons(variables, values);
}
Expression* frameVar(Expression *frame) {
    return car(frame);
}
Expression* frameValues(Expression *frame) {
    return cdr(frame);
}

void addBindingToFrame(Expression *var, Expression *val, Expression *frame) {
    setcar(frame, cons(var, car(frame)));
    setcdr(frame, cons(val, cdr(frame)));
}

Expression* extendEnv(Expression *vars, Expression *vals, Expression *base_env) {
    return cons(makeFrame(vars, vals), base_env);
}

Expression* lookupVarValue(Expression *var, Expression *env) {
    Expression *frame;
    Expression *vars;
    Expression *vals;

    while (!isEmptyList(env)) {
        frame = firstFrame(env);
        vars = frameVar(frame);
        vals = frameValues(frame);
        while (!isEmptyList(vars)) {
            if (var == car(vars)) {
                return car(vals);
            }
            vars = cdr(vars);
            vals = cdr(vals);
        }
        env = enclosingEnvironment(env);
    }
    fprintf(stderr, "unbound variable\n");
    exit(1);
}

void setVarValue(Expression *var, Expression *val, Expression *env) {
    Expression *frame;
    Expression *vars;
    Expression *vals;

    while (!isEmptyList(env)) {
        frame = firstFrame(env);
        vars = frameVar(frame);
        vals = frameValues(frame);
        while (!isEmptyList(vars)) {
            if (var == car(vars)) {
                setcar(vals, val);
                return;
            }
            vars = cdr(vars);
            vals = cdr(vals);
        }
        env = enclosingEnvironment(env);
    }
    fprintf(stderr, "unbound variable\n");
    exit(1);
}

void defVar(Expression *var, Expression *val, Expression *env) {
    Expression *frame;
    Expression *vars;
    Expression *vals;
    
    frame = firstFrame(env);    
    vars = frameVar(frame);
    vals = frameValues(frame);

    while (!isEmptyList(vars)) {
        if (var == car(vars)) {
            setcar(vals, val);
            return;
        }
        vars = cdr(vars);
        vals = cdr(vals);
    }
    addBindingToFrame(var, val, frame);
}

Expression* setupEnv() {
    Expression *initial_env;

    initial_env = extendEnv(empty_list, empty_list, empty_env);
    return initial_env;
}
 
