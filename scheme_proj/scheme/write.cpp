#include "write.h"

using namespace std;

void Writer::writeList(Expression *list) {
    Expression *car_obj = car(list);
    Expression *cdr_obj = cdr(list);

    write(car_obj);

    if (cdr_obj->exprType_ == LIST && cdr_obj != Expression::empty_list()) {
        if (car_obj) *out << " ";
        writeList(cdr_obj);
    } else {
        if (cdr_obj == Expression::empty_list()) { return; }
        *out << " . ";
        write(cdr_obj);
    }
}

void Writer::write(Expression *expr) {
    if (!expr) return;
    int i=0;
    char c;
    string str;
    switch (expr->exprType_) {
        case LIST:
            *out << "(";
            if (!isEmptyList(expr)) { writeList(expr); }
            *out << ")";
            break;
        case ATOM:
            switch (expr->get<Atom>().atomType_) {
                case BOOL:
                    *out << (isFalse(expr) ? "#f" : "#t"); break;
                case NUM:
                    *out << expr->get<Atom>().get<long>(); break;
                case CHAR:
                    c = expr->get<Atom>().get<char>();
                    *out << "#\\";
                    switch (c) {
                        case '\n':
                            *out << "newline"; break;
                        case ' ':
                            *out << "space"; break;
                        default:
                            *out << c; break;
                    } break;
                case STR:
                    str = expr->get<Atom>().get<string>();
                    *out << '"';
                    while ((c = str[i++]) != '\0') {
                        switch (c) {
                            case '\n':
                                *out << "\\n"; break;
                            case '\\':
                                *out << "\\\\"; break;
                            case '"':
                                *out << "\\\""; break;
                            default:
                                *out << c; break;
                        }
                    }
                    *out << '"';
                    break;
                case SYMBOL:
                    *out << expr->get<Atom>().get<Symbol>().symbol; break;
                case PRIM_PROC:
                    *out << "#<prim-proc>"; break;
                case COMP_PROC:
                    *out << "#<comp-proc>"; break;
                case EOF_OBJECT:
                    *out << "#<eof>"; break;
            default:
                cerr << "cannot write unknown type\n"; exit(1);
            }
            break;
        default:
            cerr << "illegal expression\n"; exit(1);
    }
    out->flush();
}