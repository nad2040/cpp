#include "eval.h"
#include "env.h"
#include "primitive_proc.h"

extern theEnv* the_env;

bool Evaluator::isSelfEval(Expression *expr) {
    return isBool(expr) || isNum(expr) ||
           isChar(expr) || isString(expr);
}

bool Evaluator::isVar(Expression *expr) { return isSymbol(expr); }

bool Evaluator::isTaggedList(Expression *expr, Expression *tag) {
    Expression *_car;
    if (isList(expr)) {
        _car = car(expr);
        return isSymbol(_car) && (_car == tag);
    }
    return false;
}

bool Evaluator::isQuoted(Expression *expr) { return isTaggedList(expr, Symbol::quote_symbol()); }
Expression* Evaluator::textOfQuote(Expression *expr) { return cadr(expr); }

bool Evaluator::isAssign(Expression *expr) { return isTaggedList(expr,Symbol::set_symbol()); }
Expression* Evaluator::assignmentVar(Expression *expr) { return cadr(expr); }
Expression* Evaluator::assignmentValue(Expression *expr) { return caddr(expr); }

bool Evaluator::isDefine(Expression *expr) { return isTaggedList(expr,Symbol::define_symbol()); }
Expression* Evaluator::definitionVar(Expression *expr) { if (isSymbol(cadr(expr))) return cadr(expr); else return caadr(expr); }
Expression* Evaluator::definitionValue(Expression *expr) { if (isSymbol(cadr(expr))) return caddr(expr); else return makeLambda(cdadr(expr), cddr(expr)); }

Expression* Evaluator::makeIf(Expression *predicate, Expression *consequent, Expression *alternative) {
    return cons(Symbol::if_symbol(), cons(predicate, cons(consequent, cons(alternative, Expression::getEmptyList()))));
}
bool Evaluator::isIf(Expression *expr) { return isTaggedList(expr, Symbol::if_symbol()); }
Expression* Evaluator::ifPredicate(Expression *expr) { return cadr(expr); }
Expression* Evaluator::ifConsequent(Expression *expr) { return caddr(expr); }
Expression* Evaluator::ifAlternative(Expression *expr) { return (isEmptyList(cdddr(expr))) ? Expression::_false() : cadddr(expr); }

Expression* Evaluator::makeLambda(Expression *params, Expression *body) { return cons(Symbol::lambda_symbol(), cons(params, body)); };
bool Evaluator::isLambda(Expression *expr) { return isTaggedList(expr, Symbol::lambda_symbol()); }
Expression* Evaluator::lambdaParams(Expression *expr) { return cadr(expr); }
Expression* Evaluator::lambdaBody(Expression *expr) { return cddr(expr); }

Expression* Evaluator::makeBegin(Expression *expr) { return cons(Symbol::begin_symbol(), expr); }
bool Evaluator::isBegin(Expression *expr) { return isTaggedList(expr, Symbol::begin_symbol()); }
Expression* Evaluator::beginActions(Expression *expr) { return cdr(expr); }

bool Evaluator::isLastExpr(Expression *seq) { return isEmptyList(cdr(seq)); }
Expression* Evaluator::firstExpr(Expression *seq) { return car(seq); }
Expression* Evaluator::restExprs(Expression *seq) { return cdr(seq); }

bool Evaluator::isCond(Expression *expr) { return isTaggedList(expr, Symbol::cond_symbol()); }
Expression* Evaluator::condClauses(Expression *expr) { return cdr(expr); }
Expression* Evaluator::condPredicate(Expression *clause) { return car(clause); }
Expression* Evaluator::condActions(Expression *clause) { return cdr(clause); }
bool Evaluator::isCondElseClause(Expression *clause) { return condPredicate(clause) == Symbol::else_symbol(); }
Expression* Evaluator::seqToExpr(Expression *seq) {
    if (isEmptyList(seq)) return seq;
    else if (isLastExpr(seq)) return firstExpr(seq);
    else return makeBegin(seq);
}
Expression* Evaluator::expandClauses(Expression *clauses) {
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
Expression* Evaluator::condToIf(Expression *expr) { return expandClauses(condClauses(expr)); }

Expression* Evaluator::makeApplication(Expression *operation, Expression *operands) { return cons(operation, operands); }
bool Evaluator::isApplication(Expression *expr) { return isList(expr); }
Expression* Evaluator::operation(Expression *expr) { return car(expr); }
Expression* Evaluator::operands(Expression *expr) { return cdr(expr); }
bool Evaluator::noOperands(Expression *ops) { return isEmptyList(ops); }
Expression* Evaluator::firstOperand(Expression *ops) { return car(ops); }
Expression* Evaluator::otherOperands(Expression *ops) { return cdr(ops); }

bool Evaluator::isLet(Expression *expr) { return isTaggedList(expr, Symbol::let_symbol()); }
Expression* Evaluator::letBindings(Expression *expr) { return cadr(expr); }
Expression* Evaluator::letBody(Expression *expr) { return cddr(expr); }
Expression* Evaluator::bindingParam(Expression *binding) { return car(binding); }
Expression* Evaluator::bindingArg(Expression *binding) { return cadr(binding); }
Expression* Evaluator::bindingsParams(Expression *bindings) {
    return isEmptyList(bindings) ? Expression::getEmptyList() : cons(bindingParam(car(bindings)), bindingsParams(cdr(bindings)));
}
Expression* Evaluator::bindingsArgs(Expression *bindings) {
    return isEmptyList(bindings) ? Expression::getEmptyList() : cons(bindingArg(car(bindings)), bindingsArgs(cdr(bindings)));
}
Expression* Evaluator::letParams(Expression *expr) { return bindingsParams(letBindings(expr)); }
Expression* Evaluator::letArgs(Expression *expr) { return bindingsArgs(letBindings(expr)); }
Expression* Evaluator::letToApplication(Expression *expr) { return makeApplication(makeLambda(letParams(expr), letBody(expr)), letArgs(expr)); }

bool Evaluator::isAnd(Expression *expr) { return isTaggedList(expr, Symbol::and_symbol()); }
Expression* Evaluator::andTests(Expression *expr) { return cdr(expr); }
bool Evaluator::isOr(Expression *expr) { return isTaggedList(expr, Symbol::or_symbol()); }
Expression* Evaluator::orTests(Expression *expr) { return cdr(expr); }

Expression* Evaluator::applyOperator(Expression *args) { return car(args); }
Expression* Evaluator::prepApplyOperands(Expression *args) {
    if (isEmptyList(cdr(args))) return car(args);
    else return cons(car(args), prepApplyOperands(cdr(args)));
}
Expression* Evaluator::applyOperands(Expression *args) { return prepApplyOperands(cdr(args)); }

Expression* Evaluator::evalExpr(Expression *args) { return car(args); }
Expression* Evaluator::evalEnv(Expression *args) { return cadr(args); }

// eval dependent

Expression* Evaluator::listOfValues(Expression *expr, Expression *env) {
    return (noOperands(expr)) ? Expression::getEmptyList() :
            cons(eval(firstOperand(expr), env), listOfValues(otherOperands(expr), env));
}

Expression* Evaluator::evalAssignment(Expression *expr, Expression *env) {
    the_env->setVarValue(assignmentVar(expr), eval(assignmentValue(expr), env), env);
    return Symbol::ok_symbol();
}
Expression* Evaluator::evalDefinition(Expression *expr, Expression *env) {    
    the_env->defVar(definitionVar(expr), eval(definitionValue(expr), env), env);
    return Symbol::ok_symbol();
}

Expression* Evaluator::eval(Expression *expr, Expression *env) {
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
