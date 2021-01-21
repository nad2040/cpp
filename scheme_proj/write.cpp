#include <iostream>
#include <string>
#include "write.h"

extern Expression *empty_list;

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
    std::string str;
    if (isList(expr)) {
        printf("(");
        if (expr->list != nullptr) { writeList(expr); }
        printf(")");
    } else if (isAtom(expr)) {
        switch (expr->atom.atomType_) {
            case BOOL:
                std::cout << expr->atom.atomValue_;
                break;
            case SYMBOL:
                std::cout << expr->atom.atomValue_;
                break;
            case NUM:
                std::cout << expr->atom.atomValue_;
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
                        std::cout << c;
                }
                break;
            case STR:
                str = expr->atom.atomValue_;
                std::cout << '"';
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
                            std::cout << c;
                    }
                }
                std::cout << '"';
                break;
            case PRIM_PROC:
            case COMP_PROC:
                std::cout << expr->atom.atomValue_;
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