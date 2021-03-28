#pragma once
#include "Sxpressions.h"

class Evaluator {
public:
    static Expression* eval(Expression *expr);
    static Expression* eval(Expression *expr, Expression *env);
private:
    static bool isSelfEval(Expression *expr);
    static bool isVar(Expression *expr); 
    static bool isTaggedList(Expression *expr, Expression *tag); 
    
    static bool isQuoted(Expression *expr); 
    static Expression* textOfQuote(Expression *expr); 
   
    static bool isAssign(Expression *expr); 
    static Expression* assignmentVar(Expression *expr); 
    static Expression* assignmentValue(Expression *expr); 
    
    static bool isDefine(Expression *expr); 
    static Expression* definitionVar(Expression *expr); 
    static Expression* definitionValue(Expression *expr); 
    
    static Expression* makeIf(Expression *predicate, Expression *consequent, Expression *alternative); 
    static bool isIf(Expression *expr); 
    static Expression* ifPredicate(Expression *expr); 
    static Expression* ifConsequent(Expression *expr); 
    static Expression* ifAlternative(Expression *expr); 
    
    static Expression* makeLambda(Expression *params, Expression *body);
    static bool isLambda(Expression *expr); 
    static Expression* lambdaParams(Expression *expr); 
    static Expression* lambdaBody(Expression *expr); 
    
    static Expression* makeBegin(Expression *expr); 
    static bool isBegin(Expression *expr); 
    static Expression* beginActions(Expression *expr); 
    
    static bool isLastExpr(Expression *seq); 
    static Expression* firstExpr(Expression *seq); 
    static Expression* restExprs(Expression *seq); 
    
    static bool isCond(Expression *expr); 
    static Expression* condClauses(Expression *expr); 
    static Expression* condPredicate(Expression *clause); 
    static Expression* condActions(Expression *clause); 
    static bool isCondElseClause(Expression *clause); 
    static Expression* seqToExpr(Expression *seq); 
    static Expression* expandClauses(Expression *clauses); 
    static Expression* condToIf(Expression *expr); 
    
    static Expression* makeApplication(Expression *operation, Expression *operands); 
    static bool isApplication(Expression *expr); 
    static Expression* operation(Expression *expr); 
    static Expression* operands(Expression *expr); 
    static bool noOperands(Expression *ops); 
    static Expression* firstOperand(Expression *ops); 
    static Expression* otherOperands(Expression *ops); 
    
    static bool isLet(Expression *expr); 
    static Expression* letBindings(Expression *expr); 
    static Expression* letBody(Expression *expr); 
    static Expression* bindingParam(Expression *binding); 
    static Expression* bindingArg(Expression *binding); 
    static Expression* bindingsParams(Expression *bindings); 
    static Expression* bindingsArgs(Expression *bindings); 
    static Expression* letParams(Expression *expr); 
    static Expression* letArgs(Expression *expr); 
    static Expression* letToApplication(Expression *expr); 
    
    static bool isAnd(Expression *expr); 
    static Expression* andTests(Expression *expr); 
    static bool isOr(Expression *expr); 
    static Expression* orTests(Expression *expr); 
    
    static Expression* applyOperator(Expression *args);
    static Expression* prepApplyOperands(Expression *args);
    static Expression* applyOperands(Expression *args);
    
    static Expression* evalExpr(Expression *args);
    static Expression* evalEnv(Expression *args);
    static Expression* listOfValues(Expression *expr, Expression *env); 
    
    static Expression* evalAssignment(Expression *expr, Expression *env); 
    static Expression* evalDefinition(Expression *expr, Expression *env); 
};
