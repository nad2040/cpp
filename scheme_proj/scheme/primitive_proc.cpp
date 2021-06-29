#include "primitive_proc.h"
#include "env.h"
#include "read.h"
#include "write.h"
#include "eval.h"

extern std::ifstream _ifs_2;
extern std::ofstream _ofs_2;

Expression* isNullProc(Expression *args) { return isEmptyList(car(args)) ? Expression::_true() : Expression::_false(); }
Expression* isBoolProc(Expression *args) { return isBool(car(args)) ? Expression::_true() : Expression::_false(); }
Expression* isSymbolProc(Expression *args) { return isSymbol(car(args)) ? Expression::_true() : Expression::_false(); }
Expression* isIntegerProc(Expression *args) { return isNum(car(args)) ? Expression::_true() : Expression::_false(); }
Expression* isCharProc(Expression *args) { return isChar(car(args)) ? Expression::_true() : Expression::_false(); }
Expression* isStringProc(Expression *args) { return isString(car(args)) ? Expression::_true() : Expression::_false(); }
Expression* isPairProc(Expression *args) { return isList(car(args)) ? Expression::_true() : Expression::_false(); }
Expression* isProcedureProc(Expression *args) { Expression* a = car(args); return (isPrimProc(a) || isCompProc(a)) ? Expression::_true() : Expression::_false(); }

Expression* charToIntProc(Expression *args) { return new Expression(Atom((long) car(args)->get<Atom>().get<char>())); }
Expression* intToCharProc(Expression *args) { return new Expression(Atom((char) car(args)->get<Atom>().get<long>())); }
Expression* numToStrProc(Expression *args) { return new Expression(Atom(std::to_string(car(args)->get<Atom>().get<long>()))); }
Expression* strToNumProc(Expression *args) { return new Expression(Atom(stol(car(args)->get<Atom>().get<std::string>()))); }
Expression* symbolToStrProc(Expression *args) { return new Expression(Atom(car(args)->get<Atom>().get<Symbol>().symbol)); }
Expression* strToSymbolProc(Expression *args) { return makeSymbol(car(args)->get<Atom>().get<std::string>()); }

Expression* addProc(Expression *args) {
    long result = 0;
    while (!isEmptyList(args)) {
        if (!isNum(car(args))) { std::cerr << "incorrect type in addition\n"; exit(1); }
        result += car(args)->get<Atom>().get<long>();
        args = cdr(args);
    }
    return new Expression(Atom(result));
}

Expression* subProc(Expression *args) {
    long result;
    result = car(args)->get<Atom>().get<long>();
    while (!isEmptyList(args = cdr(args))) {
        if (!isNum(car(args))) { std::cerr << "incorrect type in subtraction\n"; exit(1); }
        result -= car(args)->get<Atom>().get<long>();
    }
    return new Expression(Atom(result));
}

Expression* multProc(Expression *args) {
    long result = 1;
    while (!isEmptyList(args)) {
        result *= car(args)->get<Atom>().get<long>();
        args = cdr(args);
    }
    return new Expression(Atom(result));
}

Expression* quotientProc(Expression *args) {
    return new Expression(Atom( car(args)->get<Atom>().get<long>() / cadr(args)->get<Atom>().get<long>() ));
}

Expression* remainderProc(Expression *args) {
    return new Expression(Atom( car(args)->get<Atom>().get<long>() % cadr(args)->get<Atom>().get<long>() ));
}

Expression* isNumberEqualProc(Expression *args) {
    long value;
    value = car(args)->get<Atom>().get<long>();
    while (!isEmptyList(args = cdr(args))) {
        if (value != (car(args)->get<Atom>().get<long>())) return Expression::_false();
    }
    return Expression::_true();
}

Expression* isLessThanProc(Expression *args) {
    long previous;
    long next;
    previous = car(args)->get<Atom>().get<long>();
    while (!isEmptyList(args = cdr(args))) {
        next = car(args)->get<Atom>().get<long>();
        if (previous < next) previous = next;
        else return Expression::_false();
    }
    return Expression::_true();
}

Expression* isGreaterThanProc(Expression *args) {
    long previous;
    long next;
    previous = car(args)->get<Atom>().get<long>();
    while (!isEmptyList(args = cdr(args))) {
        next = car(args)->get<Atom>().get<long>();
        if (previous > next) previous = next;
        else return Expression::_false();
    }
    return Expression::_true();
}

Expression* consProc(Expression *args) { return cons(car(args), cadr(args)); }
Expression* carProc(Expression *args) { return caar(args); }
Expression* cdrProc(Expression *args) { return cdar(args); }
Expression* setcarProc(Expression *args) { setcar(car(args), cadr(args)); return Symbol::ok_symbol(); }
Expression* setcdrProc(Expression *args) { setcdr(car(args), cadr(args)); return Symbol::ok_symbol(); }
Expression* listProc(Expression *args) { return args; }

Expression* isEqProc(Expression *args) {
    Expression *expr1 = car(args), *expr2 = cadr(args);
    if (expr1->exprType_ != expr2->exprType_) return Expression::_false();
    if (expr1->exprType_ == ATOM) {
        if (expr1->get<Atom>().atomType_ != expr2->get<Atom>().atomType_) return Expression::_false();
        else return (expr1->get<Atom>() == expr2->get<Atom>()) ? Expression::_true() : Expression::_false();
    } else return (expr1 == expr2) ? Expression::_true() : Expression::_false();
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
    std::string filename = car(args)->get<Atom>().get<std::string>();
    std::ifstream ifs;
    Expression *expr;
    Expression *result;

    ifs.open(filename, std::ifstream::in);
    if (ifs.fail()) { std::cerr << "could not load file \"" << filename << "\""; exit(1); }
    Reader r = Reader(ifs);
    while (!r.in->eof()) {
        r.fillBuff();
        expr = r.readIn();
        result = eval(expr, theEnv::global_env());
        //r.emptyBuff();
    }
    ifs.close();
    return result;
}

Expression *openInputPortProc(Expression *args) {
    std::string filename = car(args)->get<Atom>().get<std::string>();
    _ifs_2.open(filename, std::ofstream::in);
    if (_ifs_2.fail()) { std::cerr << "could not load file \"" << filename << "\""; exit(1); }
    return new Expression(Atom(&_ifs_2));
}
Expression *closeInputPortProc(Expression *args) {
    car(args)->get<Atom>().get<std::ifstream*>()->close();
    if (car(args)->get<Atom>().get<std::ifstream*>()->fail()) { std::cerr << "could not close input port\n"; exit(1); }
    return Symbol::ok_symbol();
}
Expression *isInputPortProc(Expression *args) { return isInputPort(car(args)) ? Expression::_true() : Expression::_false(); }

Expression *readProc(Expression *args) {
    Expression *result;
    Reader r = isEmptyList(args) ? Reader() : Reader(*car(args)->get<Atom>().get<std::ifstream*>());
    r.fillBuff();
    result = r.readIn();
    //r.emptyBuff();
    return (result == nullptr) ? Expression::eof_object() : result;
}
Expression *readCharProc(Expression *args) {
    char c;
    Reader r = isEmptyList(args) ? Reader() : Reader(*car(args)->get<Atom>().get<std::ifstream*>());
    r.in->get(c);
    return (r.in->eof()) ? Expression::eof_object() : new Expression(Atom(c));
}
Expression *peekCharProc(Expression *args) {
    char c;
    Reader r = isEmptyList(args) ? Reader() : Reader(*car(args)->get<Atom>().get<std::ifstream*>());
    c = r.in->peek();
    return (c == EOF) ? Expression::eof_object() : new Expression(Atom(c));
}

Expression *isEOFObjProc(Expression *args) { return isEOFObject(car(args)) ? Expression::_true() : Expression::_false(); }

Expression *openOutputPortProc(Expression *args) {
    std::string filename = car(args)->get<Atom>().get<std::string>();
    _ofs_2.open(filename, std::ofstream::app);
    if (_ofs_2.fail()) { std::cerr << "could not open file \"" << filename << "\""; exit(1); }
    return new Expression(Atom(&_ofs_2));
}
Expression *closeOutputPortProc(Expression *args) {
    car(args)->get<Atom>().get<std::ofstream*>()->close();
    if (car(args)->get<Atom>().get<std::ofstream*>()->fail()) { std::cerr << "could not close output port\n"; exit(1); }
    return Symbol::ok_symbol();
}
Expression *isOutputPortProc(Expression *args) { return isOutputPort(car(args)) ? Expression::_true() : Expression::_false(); }

Expression *writeCharProc(Expression *args) {
    Expression *character = car(args);
    args = cdr(args);
    Writer w = isEmptyList(args) ? Writer() : Writer(*car(args)->get<Atom>().get<std::ofstream*>());
    w.out->put(character->get<Atom>().get<char>());
    w.out->flush();
    return Symbol::ok_symbol();
}
Expression *writeProc(Expression *args) {
    Expression *expr = car(args);
    args = cdr(args);
    Writer w = isEmptyList(args) ? Writer() : Writer(*car(args)->get<Atom>().get<std::ofstream*>());
    w.write(expr);
    w.out->flush();
    return Symbol::ok_symbol();
}

Expression *errorProc(Expression *args) {
    Writer w = Writer(std::cerr);
    while (!isEmptyList(args)) {
        w.write(car(args));
        std::cerr << " ";
        args = cdr(args);
    };
    std::cout << "\nexiting\n";
    exit(1);
}