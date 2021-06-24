#include "write.h"
#include <string>

using namespace std;

extern Expression *empty_list;

void Writer::writeList(Expression *list) {
    Expression *car_obj = car(list);
    Expression *cdr_obj = cdr(list);

    write(car_obj);

    if (cdr_obj->exprType_ == LIST && cdr_obj != empty_list) {
        if (car_obj) *out << " ";
        writeList(cdr_obj);
    } else {
        if (cdr_obj == empty_list) { return; }
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
        if (expr->list != nullptr) { writeList(expr); }
        *out << ")";
        break;
    case ATOM:
        switch (expr->atom.atomType_) {
        case BOOL:
        case SYMBOL:
        case NUM:
        case PRIM_PROC:
        case COMP_PROC:
        case EOF_OBJECT:
            *out << expr->atom.atomValue_;
            break;
        case CHAR:
            c = expr->atom.atomValue_[0];
            *out << "#\\";
            switch (c) {
                case '\n':
                    *out << "newline";
                    break;
                case ' ':
                    *out << "space";
                    break;
                default:
                    *out << c;
            }
            break;
        case STR:
            str = expr->atom.atomValue_;
            *out << '"';
            while ((c = str[i++]) != '\0') {
                switch (c) {
                    case '\n':
                        *out << "\\n";
                        break;
                    case '\\':
                        *out << "\\\\";
                        break;
                    case '"':
                        *out << "\\\"";
                        break;
                    default:
                        *out << c;
                }
            }
            *out << '"';
            break;
        default:
            cerr << "cannot write unknown type\n"; exit(1);
        }
        break;
    default:
        cerr << "illegal expression\n"; exit(1);
    }
    out->flush();
}