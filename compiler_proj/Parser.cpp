#include "Parser.h"

Parser::Parser(std::queue<Token> t) : tokens(t) {}

AST *Parser::parse() {
    Token t=tokens.front();
    tokens.pop();
    return new AST(t);
}

AST *Parser::parse_expr() {
    return parse_expr_l(parse(), 0);
}

AST *Parser::parse_expr_l(AST *l, int min_precedence) {
    if (!tokens.empty()) {
        Token lookahead = tokens.front();
        while (!tokens.empty() && lookahead.is_operator() && lookahead.precedence() >= min_precedence) {
            Token op = lookahead;
            tokens.pop();
            AST *r = parse();
            if (!tokens.empty()) {
                lookahead = tokens.front();
                while (!tokens.empty() && lookahead.is_operator() && lookahead.precedence() > op.precedence()) {
                    r = parse_expr_l(r, op.precedence() + (lookahead.precedence() > op.precedence() ? 1 : 0));
                    if (!tokens.empty()) lookahead = tokens.front();
                }
            }
            l = new AST(op, l, r);
        }
    }
    return l;
}