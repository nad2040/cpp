#include "Parser.h"

int main() {
    std::string expr;
    std::ostringstream ss;
    Token t;
    
    for (;;) {
        ss << std::cin.rdbuf();
        expr = ss.str();
        ss.str(std::string());
        clearerr(stdin);

        std::queue<Token> tokens = Tokenizer(expr).tokenize();

        // for (int it=0; it<tokens.size(); it++) {
        //     std::cout << tokens.front() << '\n';
        //     tokens.push(tokens.front());
        //     tokens.pop();
        // }

        if (tokens.empty()) break;

        AST *tree = Parser(tokens).parse_expr();
        std::cout << tree << '\n';

        expr.clear();
    }

    return 0;
}