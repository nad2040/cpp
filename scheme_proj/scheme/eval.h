#pragma once
#include "Sxpressions.h"

bool isSelfEval(Expression *expr);

bool isVar(Expression *expr); 

bool isTaggedList(Expression *expr, Expression *tag); 

bool isQuoted(Expression *expr); 
Expression* textOfQuote(Expression *expr); 

bool isAssign(Expression *expr); 
Expression* assignmentVar(Expression *expr); 
Expression* assignmentValue(Expression *expr); 

bool isDefine(Expression *expr); 
Expression* definitionVar(Expression *expr); 
Expression* makeLambda(Expression *params, Expression *body);
Expression* definitionValue(Expression *expr); 

Expression* makeIf(Expression *predicate, Expression *consequent, Expression *alternative); 
bool isIf(Expression *expr); 
Expression* ifPredicate(Expression *expr); 
Expression* ifConsequent(Expression *expr); 
Expression* ifAlternative(Expression *expr); 

Expression* makeLambda(Expression *params, Expression *body) ;;
bool isLambda(Expression *expr); 
Expression* lambdaParams(Expression *expr); 
Expression* lambdaBody(Expression *expr); 

Expression* makeBegin(Expression *expr); 
bool isBegin(Expression *expr); 
Expression* beginActions(Expression *expr); 

bool isLastExpr(Expression *seq); 
Expression* firstExpr(Expression *seq); 
Expression* restExprs(Expression *seq); 

bool isCond(Expression *expr); 
Expression* condClauses(Expression *expr); 
Expression* condPredicate(Expression *clause); 
Expression* condActions(Expression *clause); 
bool isCondElseClause(Expression *clause); 
Expression* seqToExpr(Expression *seq); 
Expression* expandClauses(Expression *clauses); 
Expression* condToIf(Expression *expr); 

Expression* makeApplication(Expression *operation, Expression *operands); 
bool isApplication(Expression *expr); 
Expression* operation(Expression *expr); 
Expression* operands(Expression *expr); 
bool noOperands(Expression *ops); 
Expression* firstOperand(Expression *ops); 
Expression* otherOperands(Expression *ops); 

bool isLet(Expression *expr); 
Expression* letBindings(Expression *expr); 
Expression* letBody(Expression *expr); 
Expression* bindingParam(Expression *binding); 
Expression* bindingArg(Expression *binding); 
Expression* bindingsParams(Expression *bindings); 
Expression* bindingsArgs(Expression *bindings); 
Expression* letParams(Expression *expr); 
Expression* letArgs(Expression *expr); 
Expression* letToApplication(Expression *expr); 

bool isAnd(Expression *expr); 
Expression* andTests(Expression *expr); 
bool isOr(Expression *expr); 
Expression* orTests(Expression *expr); 

Expression* applyOperator(Expression *args);
Expression* prepApplyOperands(Expression *args);
Expression* applyOperands(Expression *args);

Expression* evalExpr(Expression *args);
Expression* evalEnv(Expression *args);

Expression* eval(Expression *expr, Expression *env);

Expression* listOfValues(Expression *expr, Expression *env); 

Expression* evalAssignment(Expression *expr, Expression *env); 
Expression* evalDefinition(Expression *expr, Expression *env); 
