#include "read.h"

using namespace std;

extern Expression *empty_list;
extern Expression *_false;
extern Expression *_true;
extern Expression *quote_symbol;

bool isDelimiter(char c) {
    return isspace(c) || c == EOF ||
           c == '('   || c == ')' ||
           c == '"'   || c == ';' ||
           c == '\0';
}

void Reader::eatWhiteSpace() {
    char c;
    while ((c = line[i++]) != '\0') {
        if (isspace(c)) continue;
        else if (c == ';') {
            while ((c = line[i++]) != '\0' && c != '\n');
            continue;
        }
        --i;
        break;
    }
}
void Reader::eatString(string check) {
    int c=0;
    while (c<check.length()) {
        if (line[i++] != check[c++]) {
            fprintf(stderr, "unexpected character '%c'\n", line[i]);
            exit(1);
        }
    }
    ++i;
}
void Reader::peekDelimiter() {
    if (!isDelimiter(line[++i])) {
        fprintf(stderr, "character not followed by delimiter\n");
        exit(1);
    }
}
Expression* Reader::readCharacter() {
    char c;
    switch (c = line[++i]) {
        case '\0':
            fprintf(stderr, "incomplete character literal\n");
            exit(1);
        case 's':
            if (line[++i] == 'p') {
                eatString("pace");
                peekDelimiter();
                return new Expression(Atom(' '));
            } break;
        case 'n':
            if (line[++i] == 'e') {
                eatString("ewline");
                peekDelimiter();
                return new Expression(Atom('\n'));
            } break;
    }
    peekDelimiter();
    return new Expression(Atom(c));
}

Expression* Reader::readPair() {
    char c;
    Expression *car_obj;
    Expression *cdr_obj;
    Expression *expr;
    
    eatWhiteSpace();
    c = line[i];
    if (c == ')') { /* read the empty list */
        i++;
        return empty_list;
    }

    car_obj = readIn();

    eatWhiteSpace();
    c = line[i++];   
    if (c == '.') { /* read improper list */
        c = line[i++];
        if (!isDelimiter(c)) {
            fprintf(stderr, "dot not followed by delimiter\n"); exit(1);
        }
        cdr_obj = readIn();
        eatWhiteSpace();
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
        cdr_obj = readPair();
        expr = cons(car_obj, cdr_obj);
        return expr;
    }
}
Expression* Reader::readIn() {
    long n = 0;
    short sign = 1;
    char c;
    string str;

    eatWhiteSpace();

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
            return readCharacter();
        } else {
            fprintf(stderr, "unknown bool or char literal\n");
            exit(1);
        }
    }
    else if ((c == '-' && isdigit(line[i+1]) || isdigit(c))) { /* read number */
        if (c == '-') {
            sign = -1;
            i++;
        }
        while (isdigit(c = line[i++])) {
            n = n*10 + (c - '0');
        } --i;
        n *= sign;
        return new Expression(Atom(n));
    }
    else if (isInitial(c) || ((c == '+' || c == '-') && isDelimiter(line[i+1]))) { /* read symbol */
        while (isInitial(c) || isdigit(c) || c == '+' || c == '-') {
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
        return readPair();
    }
    else if (c == '\'') { /* read quoted expression */
        i++;
        return cons(quote_symbol, cons(readIn(), empty_list));
    }
    else { /* bad input */
        fprintf(stderr, "bad input. Unexpected '%c'\n", c);
        exit(1);
    }
    fprintf(stderr, "read illegal state\n");
    exit(1);
}