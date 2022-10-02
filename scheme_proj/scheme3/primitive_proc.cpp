#include "primitive_proc.h"
#include "env.h"
#include "read.h"
#include "write.h"
#include "eval.h"

Expression* isNullProc(Expression *args) { return isEmptyList(car(args)) ? Expression::_true() : Expression::_false(); }
Expression* isBoolProc(Expression *args) { return isBool(car(args)) ? Expression::_true() : Expression::_false(); }
Expression* isSymbolProc(Expression *args) { return isSymbol(car(args)) ? Expression::_true() : Expression::_false(); }
Expression* isIntegerProc(Expression *args) { return isNum(car(args)) ? Expression::_true() : Expression::_false(); }
Expression* isCharProc(Expression *args) { return isChar(car(args)) ? Expression::_true() : Expression::_false(); }
Expression* isStringProc(Expression *args) { return isString(car(args)) ? Expression::_true() : Expression::_false(); }
Expression* isPairProc(Expression *args) { return isList(car(args)) ? Expression::_true() : Expression::_false(); }
Expression* isProcedureProc(Expression *args) { Expression* a = car(args); return (isPrimProc(a) || isCompProc(a)) ? Expression::_true() : Expression::_false(); }

Expression* charToIntProc(Expression *args) { return new Expression((long) car(args)->data.character); }
Expression* intToCharProc(Expression *args) { return new Expression((char) car(args)->data.number); }
Expression* numToStrProc(Expression *args) { return new Expression(std::to_string(car(args)->data.number), false); }
Expression* strToNumProc(Expression *args) { return new Expression(stol(car(args)->data.string.val)); }
Expression* symbolToStrProc(Expression *args) { return new Expression(car(args)->data.symbol.val, false); }
Expression* strToSymbolProc(Expression *args) { return Expression::makeSymbol(car(args)->data.string.val); }

Expression* addProc(Expression *args) {
    long result = 0;
    while (!isEmptyList(args)) {
        if (!isNum(car(args))) { std::cerr << "incorrect type in addition\n"; exit(1); }
        result += car(args)->data.number;
        args = cdr(args);
    }
    return new Expression(result);
}

Expression* subProc(Expression *args) {
    long result;
    result = car(args)->data.number;
    while (!isEmptyList(args = cdr(args))) {
        if (!isNum(car(args))) { std::cerr << "incorrect type in subtraction\n"; exit(1); }
        result -= car(args)->data.number;
    }
    return new Expression(result);
}

Expression* multProc(Expression *args) {
    long result = 1;
    while (!isEmptyList(args)) {
        result *= car(args)->data.number;
        args = cdr(args);
    }
    return new Expression(result);
}

Expression* quotientProc(Expression *args) {
    return new Expression( car(args)->data.number / cadr(args)->data.number );
}

Expression* remainderProc(Expression *args) {
    return new Expression( car(args)->data.number % cadr(args)->data.number );
}

Expression* isNumberEqualProc(Expression *args) {
    long value;
    value = car(args)->data.number;
    while (!isEmptyList(args = cdr(args))) {
        if (value != (car(args)->data.number)) return Expression::_false();
    }
    return Expression::_true();
}

Expression* isLessThanProc(Expression *args) {
    long previous;
    long next;
    previous = car(args)->data.number;
    while (!isEmptyList(args = cdr(args))) {
        next = car(args)->data.number;
        if (previous < next) previous = next;
        else return Expression::_false();
    }
    return Expression::_true();
}

Expression* isGreaterThanProc(Expression *args) {
    long previous;
    long next;
    previous = car(args)->data.number;
    while (!isEmptyList(args = cdr(args))) {
        next = car(args)->data.number;
        if (previous > next) previous = next;
        else return Expression::_false();
    }
    return Expression::_true();
}

Expression* consProc(Expression *args) { return cons(car(args), cadr(args)); }
Expression* carProc(Expression *args) { return caar(args); }
Expression* cdrProc(Expression *args) { return cdar(args); }
Expression* setcarProc(Expression *args) { setcar(car(args), cadr(args)); return Expression::ok_symbol(); }
Expression* setcdrProc(Expression *args) { setcdr(car(args), cadr(args)); return Expression::ok_symbol(); }
Expression* listProc(Expression *args) { return args; }

Expression* isEqProc(Expression *args) {
    Expression *expr1 = car(args), *expr2 = cadr(args);
    return (*expr1 == *expr2) ? Expression::_true() : Expression::_false();
    // if (expr1->type != expr2->type) return Expression::_false();
    // else if (expr1->isAtom()) {
    //     if (expr1->type != expr2->type) return Expression::_false();
    //     else return (expr1->data == expr2->data) ? Expression::_true() : Expression::_false();
    // } else return (expr1 == expr2) ? Expression::_true() : Expression::_false();
}

Expression* applyProc(Expression *args) {
    std::cerr << "illegal state: The body of the apply primitive procedure should not execute.\n"; exit(1);
}

Expression* interactionEnvProc(Expression *args) { return theEnv::global_env(); }
Expression* nullEnvProc(Expression *args) { return theEnv::setupEnv(); }
Expression* envProc(Expression *args) { return theEnv::makeEnv(); }
Expression* evalProc(Expression *args) {
    std::cerr << "illegal state: The body of the eval primitive procedure should not execute.\n"; exit(1);
}

Expression* loadProc(Expression *args) {
    std::string filename = car(args)->data.string.val;
    std::ifstream* ifs = new std::ifstream();
    ifs->open(filename, std::ifstream::in);
    if (ifs->fail()) { std::cerr << "could not load file \"" << filename << "\""; exit(1); }
    
    Expression *expr;
    Expression *result;
    Reader r = Reader(ifs);
    while (!r.in->eof()) {
        r.fillBuff();
        expr = r.readIn();
        result = eval(expr, theEnv::global_env());
        r.emptyBuff();
    }
    ifs->close();
    return result;
}

Expression *openInputPortProc(Expression *args) {
    std::string filename = car(args)->data.string.val;
    std::ifstream* ifs = new std::ifstream();
    ifs->open(filename, std::ifstream::in);
    if (ifs->fail()) { std::cerr << "could not load file \"" << filename << "\""; exit(1); }
    return new Expression(ifs);
}
Expression *closeInputPortProc(Expression *args) {
    car(args)->data.input.stream->close();
    if (car(args)->data.input.stream->fail()) { std::cerr << "could not close input port\n"; exit(1); }
    return Expression::ok_symbol();
}
Expression *isInputPortProc(Expression *args) { return isInputPort(car(args)) ? Expression::_true() : Expression::_false(); }

Expression *readProc(Expression *args) {
    Expression *result;
    Reader r = isEmptyList(args) ? Reader() : Reader(car(args)->data.input.stream);
    r.fillBuff();
    result = r.readIn();
    return (result == nullptr) ? Expression::eof_object() : result;
}
Expression *readCharProc(Expression *args) {
    char c;
    Reader r = isEmptyList(args) ? Reader() : Reader(car(args)->data.input.stream);
    r.in->get(c);
    return (r.in->eof()) ? Expression::eof_object() : new Expression(c);
}
Expression *peekCharProc(Expression *args) {
    char c;
    Reader r = isEmptyList(args) ? Reader() : Reader(car(args)->data.input.stream);
    c = r.in->peek();
    return (c == EOF) ? Expression::eof_object() : new Expression(c);
}

Expression *isEOFObjProc(Expression *args) { return isEOFObject(car(args)) ? Expression::_true() : Expression::_false(); }

Expression *openOutputPortProc(Expression *args) {
    std::string filename = car(args)->data.string.val;
    std::ofstream* ofs = new std::ofstream();
    ofs->open(filename, std::ofstream::app);
    if (ofs->fail()) { std::cerr << "could not open file \"" << filename << "\""; exit(1); }
    return new Expression(ofs);
}
Expression *closeOutputPortProc(Expression *args) {
    car(args)->data.output.stream->close();
    if (car(args)->data.output.stream->fail()) { std::cerr << "could not close output port\n"; exit(1); }
    return Expression::ok_symbol();
}
Expression *isOutputPortProc(Expression *args) { return isOutputPort(car(args)) ? Expression::_true() : Expression::_false(); }

Expression *writeCharProc(Expression *args) {
    Expression *character = car(args);
    args = cdr(args);
    Writer w = isEmptyList(args) ? Writer() : Writer(car(args)->data.output.stream);
    w.out->put(character->data.character);
    w.out->flush();
    return Expression::ok_symbol();
}
Expression *writeProc(Expression *args) {
    Expression *expr = car(args);
    args = cdr(args);
    Writer w = isEmptyList(args) ? Writer() : Writer(car(args)->data.output.stream);
    w.write(expr);
    w.out->flush();
    return Expression::ok_symbol();
}

Expression *errorProc(Expression *args) {
    Writer w = Writer(&std::cerr);
    while (!isEmptyList(args)) {
        w.write(car(args));
        std::cerr << " ";
        args = cdr(args);
    };
    std::cout << "\nexiting\n";
    exit(1);
}