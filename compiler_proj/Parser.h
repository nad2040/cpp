#pragma once
#include "Tokenizer.h"
#include "AST.h"

class Parser {
public:
    std::queue<Token> tokens;

    Parser(std::queue<Token> t);

    AST *parse();
    AST *parse_expr();
    AST *parse_expr_l(AST *, int);

};