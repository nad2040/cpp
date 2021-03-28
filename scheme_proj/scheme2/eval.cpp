#include "eval.h"
#include "primitive_proc.h"

extern theEnv* the_env;

bool isSelfEval(Expression *expr) {
    return isBool(expr) || isNum(expr) ||
           isChar(expr) || isString(expr);
}

bool isVar(Expression *expr) { return isSymbol(expr); }

bool isTaggedList(Expression *expr, Expression *tag) {
    Expression *_car;
    if (isList(expr)) {
        _car = car(expr);
        return isSymbol(_car) && (_car == tag);
    }
    return false;
}

bool isQuoted(Expression *expr) { return isTaggedList(expr, Symbol::quote_symbol()); }
Expression* textOfQuote(Expression *expr) { return cadr(expr); }

bool isAssign(Expression *expr) { return isTaggedList(expr,Symbol::set_symbol()); }
Expression* assignmentVar(Expression *expr) { return cadr(expr); }
Expression* assignmentValue(Expression *expr) { return caddr(expr); }

bool isDefine(Expression *expr) { return isTaggedList(expr,Symbol::define_symbol()); }
Expression* definitionVar(Expression *expr) { if (isSymbol(cadr(expr))) return cadr(expr); else return caadr(expr); }
Expression* makeLambda(Expression *params, Expression *body);
Expression* definitionValue(Expression *expr) { if (isSymbol(cadr(expr))) return caddr(expr); else return makeLambda(cdadr(expr), cddr(expr)); }

Expression* makeIf(Expression *predicate, Expression *consequent, Expression *alternative) {
    return cons(Symbol::if_symbol(), cons(predicate, cons(consequent, cons(alternative, Expression::getEmptyList()))));
}
bool isIf(Expression *expr) { return isTaggedList(expr, Symbol::if_symbol()); }
Expression* ifPredicate(Expression *expr) { return cadr(expr); }
Expression* ifConsequent(Expression *expr) { return caddr(expr); }
Expression* ifAlternative(Expression *expr) { return (isEmptyList(cdddr(expr))) ? Expression::_false() : cadddr(expr); }

Expression* makeLambda(Expression *params, Expression *body) { return cons(Symbol::lambda_symbol(), cons(params, body)); };
bool isLambda(Expression *expr) { return isTaggedList(expr, Symbol::lambda_symbol()); }
Expression* lambdaParams(Expression *expr) { return cadr(expr); }
Expression* lambdaBody(Expression *expr) { return cddr(expr); }

Expression* makeBegin(Expression *expr) { return cons(Symbol::begin_symbol(), expr); }
bool isBegin(Expression *expr) { return isTaggedList(expr, Symbol::begin_symbol()); }
Expression* beginActions(Expression *expr) { return cdr(expr); }

bool isLastExpr(Expression *seq) { return isEmptyList(cdr(seq)); }
Expression* firstExpr(Expression *seq) { return car(seq); }
Expression* restExprs(Expression *seq) { return cdr(seq); }

bool isCond(Expression *expr) { return isTaggedList(expr, Symbol::cond_symbol()); }
Expression* condClauses(Expression *expr) { return cdr(expr); }
Expression* condPredicate(Expression *clause) { return car(clause); }
Expression* condActions(Expression *clause) { return cdr(clause); }
bool isCondElseClause(Expression *clause) { return condPredicate(clause) == Symbol::else_symbol(); }
Expression* seqToExpr(Expression *seq) {
    if (isEmptyList(seq)) return seq;
    else if (isLastExpr(seq)) return firstExpr(seq);
    else return makeBegin(seq);
}
Expression* expandClauses(Expression *clauses) {
    Expression *first, *rest;
    if (isEmptyList(clauses)) return Expression::_false();
    else {
        first = car(clauses);
        rest = cdr(clauses);
        if (isCondElseClause(first)) {
            if (isEmptyList(rest)) return seqToExpr(condActions(first));
            else { std::cerr << "else clause isn't last cond->if"; exit(1); }
        }
        else { return makeIf(condPredicate(first), seqToExpr(condActions(first)), expandClauses(rest)); }
    }
}
Expression* condToIf(Expression *expr) { return expandClauses(condClauses(expr)); }

Expression* makeApplication(Expression *operation, Expression *operands) { return cons(operation, operands); }
bool isApplication(Expression *expr) { return isList(expr); }
Expression* operation(Expression *expr) { return car(expr); }
Expression* operands(Expression *expr) { return cdr(expr); }
bool noOperands(Expression *ops) { return isEmptyList(ops); }
Expression* firstOperand(Expression *ops) { return car(ops); }
Expression* otherOperands(Expression *ops) { return cdr(ops); }

bool isLet(Expression *expr) { return isTaggedList(expr, Symbol::let_symbol()); }
Expression* letBindings(Expression *expr) { return cadr(expr); }
Expression* letBody(Expression *expr) { return cddr(expr); }
Expression* bindingParam(Expression *binding) { return car(binding); }
Expression* bindingArg(Expression *binding) { return cadr(binding); }
Expression* bindingsParams(Expression *bindings) {
    return isEmptyList(bindings) ? Expression::getEmptyList() : cons(bindingParam(car(bindings)), bindingsParams(cdr(bindings)));
}
Expression* bindingsArgs(Expression *bindings) {
    return isEmptyList(bindings) ? Expression::getEmptyList() : cons(bindingArg(car(bindings)), bindingsArgs(cdr(bindings)));
}
Expression* letParams(Expression *expr) { return bindingsParams(letBindings(expr)); }
Expression* letArgs(Expression *expr) { return bindingsArgs(letBindings(expr)); }
Expression* letToApplication(Expression *expr) { return makeApplication(makeLambda(letParams(expr), letBody(expr)), letArgs(expr)); }

bool isAnd(Expression *expr) { return isTaggedList(expr, Symbol::and_symbol()); }
Expression* andTests(Expression *expr) { return cdr(expr); }
bool isOr(Expression *expr) { return isTaggedList(expr, Symbol::or_symbol()); }
Expression* orTests(Expression *expr) { return cdr(expr); }

Expression* applyOperator(Expression *args) { return car(args); }
Expression* prepApplyOperands(Expression *args) {
    if (isEmptyList(cdr(args))) return car(args);
    else return cons(car(args), prepApplyOperands(cdr(args)));
}
Expression* applyOperands(Expression *args) { return prepApplyOperands(cdr(args)); }

Expression* evalExpr(Expression *args) { return car(args); }
Expression* evalEnv(Expression *args) { return cadr(args); }

// eval dependent

Expression* listOfValues(Expression *expr, Expression *env) {
    return (noOperands(expr)) ? Expression::getEmptyList() :
            cons(eval(firstOperand(expr), env), listOfValues(otherOperands(expr), env));
}

Expression* evalAssignment(Expression *expr, Expression *env) {
    the_env->setVarValue(assignmentVar(expr), eval(assignmentValue(expr), env), env);
    return Symbol::ok_symbol();
}
Expression* evalDefinition(Expression *expr, Expression *env) {    
    the_env->defVar(definitionVar(expr), eval(definitionValue(expr), env), env);
    return Symbol::ok_symbol();
}

Expression* eval(Expression *expr, Expression *env) {
    Expression *proc, *args, *result;

tailcall:
    if (isSelfEval(expr)) return expr;
    else if (isVar(expr)) return the_env->lookupVarValue(expr, env);
    else if (isQuoted(expr)) return textOfQuote(expr);
    else if (isAssign(expr)) return evalAssignment(expr, env);
    else if (isDefine(expr)) return evalDefinition(expr, env);
    else if (isIf(expr)) { expr = isFalse(eval(ifPredicate(expr), env)) ? ifAlternative(expr) : ifConsequent(expr); goto tailcall; }
    else if (isLambda(expr)) { return new Expression(Atom(lambdaParams(expr), lambdaBody(expr), env)); }
    else if (isBegin(expr)) {
        expr = beginActions(expr);
        while (!isLastExpr(expr)) { eval(firstExpr(expr), env); expr = restExprs(expr); }
        expr = firstExpr(expr); goto tailcall;
    }
    else if (isCond(expr)) { expr = condToIf(expr); goto tailcall; }
    else if (isLet(expr)) { expr = letToApplication(expr); goto tailcall; }
    else if (isAnd(expr)) {
        expr = andTests(expr);
        if (isEmptyList(expr)) return Expression::_true();
        while (!isLastExpr(expr)) {
            result = eval(firstExpr(expr), env);
            if (isFalse(result)) return result;
            expr = restExprs(expr);
        }
        expr = firstExpr(expr);
        goto tailcall;
    }
    else if (isOr(expr)) {
        expr = orTests(expr);
        if (isEmptyList(expr)) return Expression::_false();
        while (!isLastExpr(expr)) {
            result = eval(firstExpr(expr), env);
            if (isTrue(result)) return result;
            expr = restExprs(expr);
        }
        expr = firstExpr(expr);
        goto tailcall;
    }
    else if (isApplication(expr)) {
        proc = eval(operation(expr), env);
        args = listOfValues(operands(expr), env);

        if (isPrimProc(proc) && proc->getPrimitive() == evalProc) {
            expr = evalExpr(args);
            env = evalEnv(args);
            goto tailcall;
        }
        if (isPrimProc(proc) && proc->getPrimitive() == applyProc) {
            proc = applyOperator(args);
            args = applyOperands(args);
        }

        if (isPrimProc(proc)) return (proc->getPrimitive())(args);
        else if (isCompProc(proc)) {
            Expression *compParams, *compBody, *compEnv;
            proc->getCompound(compParams, compBody, compEnv);
            env = the_env->extendEnv(compParams, args, compEnv);
            expr = makeBegin(compBody);
            goto tailcall;
        } else { std::cerr << "unknown procedure type\n"; exit(1); }
    }
    else { std::cerr << "cannot eval unknown expression type\n"; exit(1); }
    std::cerr << "eval illegal state\n"; exit(1);
}
