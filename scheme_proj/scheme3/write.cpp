#include "write.h"

void Writer::writeList(Expression *list) {
    Expression *car_obj = car(list);
    Expression *cdr_obj = cdr(list);

    write(car_obj);

    if (cdr_obj->type == LIST && cdr_obj != Expression::empty_list()) {
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
    std::string str;
    switch (expr->type) {
        case LIST:
            *out << "(";
            if (!isEmptyList(expr)) { writeList(expr); }
            *out << ")";
            break;

        case BOOL:
            *out << (isFalse(expr) ? "#f" : "#t"); break;
        case NUM:
            *out << expr->data.number; break;
        case CHAR:
            c = expr->data.character;
            *out << "#\\";
            switch (c) {
                case '\n':
                    *out << "newline"; break;
                case ' ':
                    *out << "space"; break;
                default:
                    *out << c; break;
            } break;
        case STRING:
            str = expr->data.string.val;
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
            *out << expr->data.symbol.val; break;
        case PRIM_PROC:
            *out << "#<prim-proc>"; break;
        case COMP_PROC:
            *out << "#<comp-proc>"; break;
        case EOF_OBJECT:
            *out << "#<eof>"; break;
        case EMPTY_LIST:
            *out << "()"; break;
        default:
            std::cerr << "cannot write unknown expression\n"; exit(1);
    }
    out->flush();
}