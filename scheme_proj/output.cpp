#include "output.h"

#include <string>

extern Expression *empty_list;

void write(std::ostream& os, Expression *expr);
void writeList(std::ostream& os, Expression *list) {
    Expression *car_obj = car(list);
    Expression *cdr_obj = cdr(list);

    write(os, car_obj);

    if (cdr_obj->exprType_ == LIST && cdr_obj != empty_list) {
        os << " ";
        writeList(os, cdr_obj);
    } else {
        if (cdr_obj == empty_list) { return; }
        os << " . ";
        write(os, cdr_obj);
    }
}

void write(std::ostream& os, Expression *expr) {
    int i=0;
    char c;
    std::string str;
    switch (expr->exprType_) {
    case LIST:
        os << "(";
        if (expr->list != nullptr) { writeList(os, expr); }
        os << ")";
        break;
    case ATOM:
        switch (expr->atom.atomType_) {
        case BOOL:
        case SYMBOL:
        case NUM:
        case PRIM_PROC:
        case COMP_PROC:
        case EOF_OBJECT:
            os << expr->atom.atomValue_;
            break;
        case CHAR:
            c = expr->atom.atomValue_[0];
            os << "#\\";
            switch (c) {
                case '\n':
                    os << "newline";
                    break;
                case ' ':
                    os << "space";
                    break;
                default:
                    os << c;
            }
            break;
        case STR:
            str = expr->atom.atomValue_;
            os << '"';
            while ((c = str[i++]) != '\0') {
                switch (c) {
                    case '\n':
                        os << "\\n";
                        break;
                    case '\\':
                        os << "\\\\";
                        break;
                    case '"':
                        os << "\\\"";
                        break;
                    default:
                        os << c;
                }
            }
            os << '"';
            break;
        default:
            std::cerr << "cannot write unknown type\n"; exit(1);
        }
        break;
    default:
        std::cerr << "illegal expression\n"; exit(1);
    }
}

std::ostream& operator<<(std::ostream& os, Expression* expr) {
    write(os, expr);
    return os;
}

std::ostream& operator<<(std::ostream& os, const Expression& expr) {
    write(os, const_cast<Expression*>(&expr));
    return os;
}

