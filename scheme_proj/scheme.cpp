#include <iostream>
#include <fstream>
#include <string>
#include "primitive_proc.h"

using namespace std;

Expression *empty_list;
Expression *_false;
Expression *_true;
Expression *quote_symbol;
Expression *symbol_table;
Expression *define_symbol;
Expression *set_symbol;
Expression *ok_symbol;
Expression *if_symbol;
Expression *lambda_symbol;
Expression *begin_symbol;
Expression *cond_symbol;
Expression *else_symbol;
Expression *let_symbol;
Expression *empty_env;
Expression *global_env;

int i;

bool isDigit(char c) {
    return (c <= '9' && c >= '0');
}

Expression* makeSymbol(string value) {
    Expression *element;
    Expression *symbol;
    /* search for they symbol in the symbol table */
    element = symbol_table;
    while (element->list != nullptr) {
        if (car(element)->atom.atomValue_ == value) {
            return car(element);
        }
        element = cdr(element);
    };
    
    /* create the symbol and add it to the symbol table */
    symbol = new Expression(Atom(value));
    symbol_table = cons(symbol, symbol_table);
    return symbol;
}

void write(Expression*);

Expression* makePrimProc(Expression *(*fn)(Expression *args)) { return new Expression(Atom(fn)); }

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

void init() {
    empty_list = new Expression();
    _false = new Expression(Atom(false));
    _true = new Expression(Atom(true));

    symbol_table = empty_list;
    quote_symbol = makeSymbol("quote");
    define_symbol = makeSymbol("define");
    set_symbol = makeSymbol("set!");
    ok_symbol = makeSymbol("ok");
    if_symbol = makeSymbol("if");
    lambda_symbol = makeSymbol("lambda");
    begin_symbol = makeSymbol("begin");
    cond_symbol = makeSymbol("cond");
    else_symbol = makeSymbol("else");
    let_symbol = makeSymbol("let");

    empty_env = empty_list;
    global_env = setupEnv();

    #define createProcedure(scheme_name, name) defVar(makeSymbol(scheme_name),makePrimProc(name),global_env);
    createProcedure("null?",isNullProc);
    createProcedure("boolean?",isBoolProc);
    createProcedure("symbol?",isSymbolProc);
    createProcedure("integer?",isIntegerProc);
    createProcedure("char?",isCharProc);
    createProcedure("string?",isStringProc);
    createProcedure("pair?",isPairProc);
    createProcedure("procedure?",isProcedureProc);

    createProcedure("char->integer",charToIntProc);
    createProcedure("integer->char",intToCharProc);
    createProcedure("number->string",numToStrProc);
    createProcedure("string->number",strToNumProc);
    createProcedure("symbol->string",symbolToStrProc);
    createProcedure("string->symbol",strToSymbolProc);

    createProcedure("+",addProc);
    createProcedure("-",subProc);
    createProcedure("*",multProc);
    createProcedure("quotient",quotientProc);
    createProcedure("remainder",remainderProc);
    createProcedure("=",isNumberEqualProc);
    createProcedure("<",isLessThanProc);
    createProcedure(">",isGreaterThanProc);

    createProcedure("cons",consProc);
    createProcedure("car",carProc);
    createProcedure("cdr",cdrProc);
    createProcedure("set-car!",setcarProc);
    createProcedure("set-cdr!",setcdrProc);
    createProcedure("list",listProc);

    createProcedure("eq?",isEqProc);

}

// *******************READ*******************

bool isDelimiter(char c) {
    return isspace(c) || c == EOF ||
           c == '('   || c == ')' ||
           c == '"'   || c == ';' ||
           c == '\0';
}

void eatWhiteSpace(string &line) {
    char c;
    while ((c = line[i++]) != '\0') {
        if (isspace(c)) {
            continue;
        }
        else if (c == ';') {
            while ((c = line[i++]) != '\0' && c != '\n');
            continue;
        }
        --i;
        break;
    }
}

void eatString(string &line, string check) {
    int c=0;
    while (c<check.size()) {
        if (line[i++] != check[c++]) {
            fprintf(stderr, "unexpected character '%c'\n", line[i]);
            exit(1);
        }
    }
    ++i;
}

void peekDelimiter(string &line) {
    if (!isDelimiter(line[++i])) {
        fprintf(stderr, "character not followed by delimiter\n");
        exit(1);
    }
}

Expression* readCharacter(string &line) {
    char c;
    switch (c = line[++i]) {
        case '\0':
            fprintf(stderr, "incomplete character literal\n");
            exit(1);
        case 's':
            if (line[++i] == 'p') {
                eatString(line,"pace");
                peekDelimiter(line);
                return new Expression(Atom(' '));
            } break;
        case 'n':
            if (line[++i] == 'e') {
                eatString(line,"ewline");
                peekDelimiter(line);
                return new Expression(Atom('\n'));
            } break;
    }
    peekDelimiter(line);
    return new Expression(Atom(c));
}

Expression* readIn(string& line);

Expression* readPair(string line) {
    char c;
    Expression *car_obj;
    Expression *cdr_obj;
    Expression *expr;
    
    eatWhiteSpace(line);
    c = line[i];
    if (c == ')') { /* read the empty list */
        i++;
        return empty_list;
    }

    car_obj = readIn(line);

    eatWhiteSpace(line);
    c = line[i++];   
    if (c == '.') { /* read improper list */
        c = line[i++];
        if (!isDelimiter(c)) {
            fprintf(stderr, "dot not followed by delimiter\n"); exit(1);
        }
        cdr_obj = readIn(line);
        eatWhiteSpace(line);
        c = line[i];
        if (c != ')') {
            fprintf(stderr, "where was the trailing right paren?\n"); exit(1);
        }
        expr = cons(car_obj, cdr_obj);
        i++;
        return expr;
    }
    else { /* read list */
        --i;
        cdr_obj = readPair(line);
        expr = cons(car_obj, cdr_obj);
        return expr;
    }
}

Expression* readIn(string& line) {
    int n = 0;
    short sign = 1;
    char c;
    string str;

    eatWhiteSpace(line);

    if (line.empty()) { return new Expression(Atom()); }

    c = line[i];
    if (c == '#') { /* read boolean/char */
        c = line[++i];
        if (c == 't') {
            i++;
            return _true;
        } else if (c == 'f') {
            i++;
            return _false;
        } else if (c == '\\') {
            return readCharacter(line);
        } else {
            fprintf(stderr, "unknown bool or char literal\n");
            exit(1);
        }
    }
    else if ((c == '-' && isDigit(line[i+1]) || isDigit(c))) { /* read number */
        if (c == '-') {
            sign = -1;
            i++;
        }
        while (isDigit(c = line[i++])) {
            n = n*10 + (c - '0');
        } --i;
        n *= sign;
        return new Expression(Atom(n));
    }
    else if (isInitial(c) || ((c == '+' || c == '-') && isDelimiter(line[i+1]))) { /* read symbol */
        while (isInitial(c) || isDigit(c) || c == '+' || c == '-') {
            str += c;
            c = line[++i];
        }
        if (isDelimiter(c)) {
            return makeSymbol(str);
        }
        else { fprintf(stderr, "symbol not followed by delimiter. Found '%c'\n", c); exit(1); }
    }
    else if (c == '"') { /* read string */
        i++;
        while (((c = line[i++]) != '"')) {
            if (c == '\\') {
                if ((c = line[i++]) == 'n') c = '\n';
            }
            str += c;
        }
        if (c == EOF) { fprintf(stderr, "non-terminated string literal\n"); exit(1); }
        return new Expression(Atom('"' + str));
    }
    else if (c == '(') { /* read pair/list */
        i++;
        return readPair(line);
    }
    else if (c == '\'') { /* read quoted expression */
        i++;
        return cons(quote_symbol, cons(readIn(line), empty_list));
    }
    else { /* bad input */
        fprintf(stderr, "bad input. Unexpected '%c'\n", c);
        exit(1);
    }
    fprintf(stderr, "read illegal state\n");
    exit(1);
}

// *****************EVALUATE*****************

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

bool isQuoted(Expression *expr) { return isTaggedList(expr, quote_symbol); }
Expression* textOfQuote(Expression *expr) { return cadr(expr); }

bool isAssign(Expression *expr) { return isTaggedList(expr,set_symbol); }
Expression* assignmentVar(Expression *expr) { return cadr(expr); }
Expression* assignmentValue(Expression *expr) { return caddr(expr); }

bool isDefine(Expression *expr) { return isTaggedList(expr,define_symbol); }
Expression* definitionVar(Expression *expr) { if (isSymbol(cadr(expr))) return cadr(expr); else return caadr(expr); }
Expression* makeLambda(Expression *params, Expression *body);
Expression* definitionValue(Expression *expr) { if (isSymbol(cadr(expr))) return caddr(expr); else return makeLambda(cdadr(expr), cddr(expr)); }

Expression* makeIf(Expression *predicate, Expression *consequent, Expression *alternative) {
    return cons(if_symbol, cons(predicate, cons(consequent, cons(alternative, empty_list))));
}
bool isIf(Expression *expr) { return isTaggedList(expr,if_symbol); }
Expression* ifPredicate(Expression *expr) { return cadr(expr); }
Expression* ifConsequent(Expression *expr) { return caddr(expr); }
Expression* ifAlternative(Expression *expr) { return (isEmptyList(cdddr(expr))) ? _false : cadddr(expr); }

Expression* makeLambda(Expression *params, Expression *body) { return cons(lambda_symbol, cons(params, body)); };
bool isLambda(Expression *expr) { return isTaggedList(expr, lambda_symbol); }
Expression* lambdaParams(Expression *expr) { return cadr(expr); }
Expression* lambdaBody(Expression *expr) { return cddr(expr); }

Expression* makeBegin(Expression *expr) { return cons(begin_symbol, expr); }
bool isBegin(Expression *expr) { return isTaggedList(expr, begin_symbol); }
Expression* beginActions(Expression *expr) { return cdr(expr); }

bool isLastExpr(Expression *seq) { return isEmptyList(cdr(seq)); }
Expression* firstExpr(Expression *seq) { return car(seq); }
Expression* restExprs(Expression *seq) { return cdr(seq); }

bool isCond(Expression *expr) { return isTaggedList(expr, cond_symbol); }
Expression* condClauses(Expression *expr) { return cdr(expr); }
Expression* condPredicate(Expression *clause) { return car(clause); }
Expression* condActions(Expression *clause) { return cdr(clause); }
bool isCondElseClause(Expression *clause) { return condPredicate(clause) == else_symbol; }
Expression* seqToExpr(Expression *seq) {
    if (isEmptyList(seq)) return seq;
    else if (isLastExpr(seq)) return firstExpr(seq);
    else return makeBegin(seq);
}
Expression* expandClauses(Expression *clauses) {
    Expression *first, *rest;
    if (isEmptyList(clauses)) return _false;
    else {
        first = car(clauses);
        rest = cdr(clauses);
        if (isCondElseClause(first)) {
            if (isEmptyList(rest)) return seqToExpr(condActions(first));
            else { fprintf(stderr, "else clause isn't last cond->if"); exit(1); }
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

bool isLet(Expression *expr) { return isTaggedList(expr, let_symbol); }
Expression* letBindings(Expression *expr) { return cadr(expr); }
Expression* letBody(Expression *expr) { return cddr(expr); }
Expression* bindingParam(Expression *binding) { return car(binding); }
Expression* bindingArg(Expression *binding) { return cadr(binding); }
Expression* bindingsParams(Expression *bindings) {
    return isEmptyList(bindings) ? empty_list : cons(bindingParam(car(bindings)), bindingsParams(cdr(bindings)));
}
Expression* bindingsArgs(Expression *bindings) {
    return isEmptyList(bindings) ? empty_list : cons(bindingArg(car(bindings)), bindingsArgs(cdr(bindings)));
}
Expression* letParams(Expression *expr) { return bindingsParams(letBindings(expr)); }
Expression* letArgs(Expression *expr) { return bindingsArgs(letBindings(expr)); }
Expression* letToApplication(Expression *expr) { return makeApplication(makeLambda(letParams(expr), letBody(expr)), letArgs(expr)); }

Expression* eval(Expression *expr, Expression *env);

Expression* listOfValues(Expression *expr, Expression *env) {
    return (noOperands(expr)) ? empty_list :
            cons(eval(firstOperand(expr), env), listOfValues(otherOperands(expr), env));
}

Expression* evalAssignment(Expression *expr, Expression *env) {
    setVarValue(assignmentVar(expr), eval(assignmentValue(expr), env), env);
    return ok_symbol;
}
Expression* evalDefinition(Expression *expr, Expression *env) {    
    defVar(definitionVar(expr), eval(definitionValue(expr), env), env);
    return ok_symbol;
}

Expression* eval(Expression *expr, Expression *env) {
    Expression *proc, *args;

tailcall:
    if (isSelfEval(expr)) return expr;
    else if (isVar(expr)) return lookupVarValue(expr, env);
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
    else if (isApplication(expr)) {
        proc = eval(operation(expr), env);
        args = listOfValues(operands(expr), env);
        if (isPrimProc(proc)) return (proc->atom.fn)(args);
        else if (isCompProc(proc)) {
            env = extendEnv(proc->atom.compound_proc.params, args, proc->atom.compound_proc.env);
            expr = makeBegin(proc->atom.compound_proc.body);
            goto tailcall;
        } else { fprintf(stderr, "unknown procedure type\n"); exit(1); }
    }
    else { fprintf(stderr, "cannot eval unknown expression type\n"); exit(1); }
    fprintf(stderr, "eval illegal state\n"); exit(1);
}

// *******************WRITE******************

void write(Expression *expr);

void writeList(Expression *list) {
    Expression *car_obj = car(list);
    Expression *cdr_obj = cdr(list);

    write(car_obj);

    if (cdr_obj->exprType_ == LIST && cdr_obj != empty_list) {
        printf(" ");
        writeList(cdr_obj);
    } else {
        if (cdr_obj == empty_list) { return; }
        printf(" . ");
        write(cdr_obj);
    }
}

void write(Expression *expr) {
    int i=0;
    char c;
    string str;
    if (isList(expr)) {
        printf("(");
        if (expr->list != nullptr) { writeList(expr); }
        printf(")");
    } else if (isAtom(expr)) {
        switch (expr->atom.atomType_) {
            case BOOL:
                cout << expr->atom.atomValue_;
                break;
            case SYMBOL:
                cout << expr->atom.atomValue_;
                break;
            case NUM:
                cout << expr->atom.atomValue_;
                break;
            case CHAR:
                c = expr->atom.atomValue_[0];
                printf("#\\");
                switch (c) {
                    case '\n':
                        printf("newline");
                        break;
                    case ' ':
                        printf("space");
                        break;
                    default:
                        cout << c;
                }
                break;
            case STR:
                str = expr->atom.atomValue_;
                cout << '"';
                while ((c = str[i++]) != '\0') {
                    switch (c) {
                        case '\n':
                            printf("\\n");
                            break;
                        case '\\':
                            printf("\\\\");
                            break;
                        case '"':
                            printf("\\\"");
                            break;
                        default:
                            cout << c;
                    }
                }
                cout << '"';
                break;
            case PRIM_PROC:
            case COMP_PROC:
                cout << expr->atom.atomValue_;
                break;
            default:
                fprintf(stderr, "cannot write unknown type\n");
                exit(1);
        }
    } else {
        fprintf(stderr, "expression Expression is empty\n");
        exit(1);
    }
}

// *******************LOOP*******************

string getInput() {
    string line = "", temp = "";
    int left = 0, right = 0, i = 2;
    while (true) {
        getline(cin, temp);
        for (int in=0; in<temp.size(); ++in) {
            if (temp[in] == '(') ++left;
            if (temp[in] == ')') ++right;
            if (temp[in] == 5) { line += temp; goto end; }
        }
        line += temp + '\n';
        cout << "  ";
        for (int j = 0; j < left-right; ++j) cout << "    ";
    }
    end:
    line.pop_back();
    return line;
}

int parenCount(string line) {
    int left = 0, right = 0;
    for (int i=0; i<line.size(); ++i) {
        if (line[i] == '(') ++left;
        if (line[i] == ')') ++right;
    }
    return left - right;
}

void fileInput(string file, bool showImportText) {
    ifstream f(file);
    string line, temp = "";
    char c;
    while (f.get(c) && isspace(c));
    while (getline(f,line)) {
        line = c + line;
        while (parenCount(line) > 0) { getline(f,temp); line += '\n' + temp; }
        i=0;
        Expression *evaluated = eval(readIn(line),global_env);
        if (showImportText) { cout << "> " << line << '\n'; write(evaluated); cout << '\n'; }
        while (f.get(c) && isspace(c));
    }
}

int main() {
    system("clear");
    cout << "=== Scheme in C++ === ^C to quit\n";
    string line;
    init();

    //fileInput("scm_files/a.scm", true);
    //fileInput("scm_files/testing_input.scm", false);

    while (1) {
        i = 0;
        cout << "> ";
        line = getInput();
        write(eval(readIn(line), global_env));
        cout << '\n';
        // write(global_env); cout << '\n';
    }

    // Test Cases
    // fileInput("scm_files/testing_input.txt", true);
}