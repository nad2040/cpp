#include <iostream>
#include <string>
#include "Sxpressions.h"

using namespace std;

int i = 0;
string empty_list = "()";

bool isDigit(char c) {
    return (c <= '9' && c >= '0');
}

bool isDelimiter(char c) {
    return c == ' ' || c == EOF ||
           c == '(' || c == ')' ||
           c == '"' || c == ';' ||
           c == '\0' || c == '\n';
}

void eatWhiteSpace(string &line) {
    char c;
    while (!line.empty()) {
        c = line[i];
        if (c == ' ') {
            ++i;
            continue;
        }
        else if (c == ';') {
            while ((c = line[i++]) != EOF && c != '\n');
            continue;
        }
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

void eatAtom(string &line) {
    char c;
    while (!line.empty() && !isDelimiter(c = line[i++]));
}

void peekDelimiter(string &line) {
    if (!isDelimiter(line[i+1])) {
        fprintf(stderr, "character not followed by delimiter\n");
        exit(1);
    }
}

Expression* readCharacter(string &line) {
    char c;
    if (!line.empty()) {
        switch (c = line[++i]) {
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
    } else {
        fprintf(stderr, "incomplete character literal\n");
        exit(1);
    }
}

bool stringContains(string &line,char c) {
    for (int in=0; in<line.size(); ++in) {
        return line[in] == c;
    } return false;
}

string getInput() {
    string line = "", temp = "";
    bool flag = false;
    while (flag == false) {
        getline(cin, temp);
        for (int in=0; in<temp.size(); ++in) {
            if (temp[in] == 5) flag = true;
        }
        line += temp + '\n';
    }
    line.pop_back();line.pop_back();
    return line;
}

Expression* car(Expression* expr) {
    return expr->list->car;
}
void setcar(Expression *expr, Expression* value) {
    expr->list->car = value;
}
Expression* cdr(Expression* expr) {
    return expr->list->cdr;
}
void setcdr(Expression *expr, Expression* value) {
    expr->list->cdr = value;
}

Expression* cons(Expression *car, Expression *cdr) {
    Expression* expr = new Expression();
    expr->list->car = car;
    expr->list->cdr = cdr;
    return expr;
}

// READ

Expression* readIn(string& line);

Expression* readPair(string line) {
    char c;
    Expression *car_obj;
    Expression *cdr_obj;
    Expression *expr;
    
    eatWhiteSpace(line);
    
    c = line[++i];
    if (c == ')') { /* read the empty list */
        return new Expression(Atom(empty_list));
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
        return expr->cons(car_obj, cdr_obj);
    }
    else { /* read list */
        --i;
        cdr_obj = readPair(line);        
        return expr->cons(car_obj, cdr_obj);
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
    if (c == '#') {
        c = line[++i];
        if (c == 't') {
            eatAtom(line);
            return new Expression(Atom(true));
        } else if (c == 'f') {
            eatAtom(line);
            return new Expression(Atom(false));
        } else if (c == '\\') {
            return readCharacter(line);
        } else {
            fprintf(stderr, "unknown bool or char literal\n");
            exit(1);
        }
    }
    else if ((c == '-' && isDigit(line[i+1]) || isDigit(c))) {
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
    else if (c == '"') {
        i++;
        while (((c = line[i++]) != '"')) {
            if (c == '\\') {
                if ((c = line[i++]) == 'n') c = '\n';
            }
            str += c;
        }
        if (c == EOF) { fprintf(stderr, "non-terminated string literal\n"); exit(1); }
        return new Expression(Atom(str));
    }
    else if (c == '(') {
        return readPair(line);
    }
    else {
        fprintf(stderr, "bad input. Unexpected '%c'\n", c);
        exit(1);
    }
    fprintf(stderr, "read illegal state\n");
    exit(1);
}

// EVALUATE

Expression* eval(Expression *input) {
    return input;
}

// WRITE

void write(Expression *expr);

void writeList(Expression *list) {
    Expression *car_obj;
    Expression *cdr_obj;
    
    car_obj = car(list);
    cdr_obj = cdr(list);

    write(car_obj);
    if (cdr_obj != nullptr) {
        if (cdr(cdr_obj) == nullptr) {
            printf(" ");
            writeList(cdr_obj);
        }
        else if (cdr_obj->atom.atomType_ == EMPTY_LIST) { return; }
        else {
            printf(" . ");
            write(cdr_obj);
        }
    }
}

void write(Expression *expr) {
    int i=0;
    char c;
    string str;
    if (expr->list != nullptr) {
        printf("(");
        writeList(expr);
        printf(")");
    } else if (expr->atom.atomType_ != UNK) {
        switch (expr->atom.atomType_) {
            case EMPTY_LIST:
                cout << expr->atom.atomValue_;
                break;
            case BOOL:
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
            default:
                fprintf(stderr, "cannot write unknown type\n");
                exit(1);
        }
        delete expr;
    } else {
        delete expr;
        fprintf(stderr, "expression object is empty\n");
        exit(1);
    }
}

int main() {
    cout << "Scheme in C++\n";

    string line;

    while (1) {
        cout << "> ";
        line = getInput();
        write(eval(readIn(line)));
        cout << '\n';
        i=0;
    }
}