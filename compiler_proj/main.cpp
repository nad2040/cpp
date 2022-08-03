#include <iostream>
#include <variant>
#include <string>
#include <queue>
#include <regex>

struct Token {
    std::string tok;
    enum TokenType { UNK, EF, IDENTIFIER, NUM, PLUS, MINUS, MULT, DIV, LEFT_PAREN, RIGHT_PAREN, WHITESPACE } token_type;

    bool isOp() { return token_type == PLUS || token_type == MINUS || token_type == MULT || token_type == DIV; }
    bool isNum() { return token_type == NUM; }
    bool isDelim() { return token_type == LEFT_PAREN || token_type == RIGHT_PAREN; }
    bool isWS() { return token_type == WHITESPACE; }

    int precedence() {
        switch (token_type) {
            case PLUS:
            case MINUS:
                return 1;
            case MULT:
            case DIV:
                return 2;
            default: return -1;
        }
    }

    Token() : tok(std::string()), token_type(UNK) {}
    Token(std::string str, TokenType type) : tok(str), token_type(type) {}
    Token(char c, TokenType type) : tok(std::string(c,1)), token_type(type) {}

    friend std::ostream & operator<<(std::ostream &out, Token token) {
        switch (token.token_type) {
            case UNK:
                out << "UNK";
                return out;
            case EF:
                out << "EOF";
                return out;
            case WHITESPACE:
                out << "WS";
                return out;
            case NUM:
                out << "IntLiteral: " << token.tok;
                return out;
            case PLUS:
                out << "Plus";
                return out;
            case MINUS:
                out << "Minus";
                return out;
            case MULT:
                out << "Mult";
                return out;
            case DIV:
                out << "Div";
                return out;
            case LEFT_PAREN:
                out << "LeftParen";
                return out;
            case RIGHT_PAREN:
                out << "RightParen";
                return out;
            default:
                return out;
        }
    }
};

struct Node {
    Node *left,*right;
    Token value;
    bool leaf;

    Node(Token t) : value(t), left(nullptr), right(nullptr), leaf(true) {}
    Node(Node *l, Node *r, Token t) : value(t), left(l), right(r), leaf(false) {}
    
    friend std::ostream & operator<<(std::ostream &out, Node* node) {
        static int depth = 0;
        if (node->leaf) {
            for (int i=0; i<depth; i++) out << "  ";
            out << node->value << '\n';
        } else {
            for (int i=0; i<depth; i++) out << "  ";
            out << node->value << '\n';
            depth++;
            out << node->left;
            out << node->right;
            depth--;
        }
        return out;
    }
};

Node *parse(std::queue<Token> &, int);
Node *parse_exp(std::queue<Token> &);
Node *parse_exp_l(std::queue<Token> &, Node *, int);

Node *parse(std::queue<Token>& tokens) {
    Token t=tokens.front();
    tokens.pop();
    return new Node(t);
}

Node *parse_exp(std::queue<Token>& tokens) {
    return parse_exp_l(tokens, parse(tokens), 0);
}

Node *parse_exp_l(std::queue<Token>& tokens, Node *l, int min_precedence) {
    if (!tokens.empty()) {
        Token lookahead = tokens.front();
        while (!tokens.empty() && lookahead.isOp() && lookahead.precedence() >= min_precedence) {
            Token op = lookahead;
            tokens.pop();
            Node *r = parse(tokens);
            if (!tokens.empty()) {
                lookahead = tokens.front();
                while (!tokens.empty() && lookahead.isOp() && lookahead.precedence() > op.precedence()) {
                    r = parse_exp_l(tokens, r, op.precedence() + (lookahead.precedence() > op.precedence() ? 1 : 0));
                    if (!tokens.empty()) lookahead = tokens.front();
                }
            }
            l = new Node(l, r, op);
        }
    }
    return l;
}

std::queue<Token> tokenize_string(std::string &);
Token nextToken(std::string &);

std::queue<Token> tokenize_string(std::string &str) {
    std::queue<Token> tokens;
    Token t;
    while (1) {
        t=nextToken(str);
        if (t.token_type == Token::WHITESPACE) continue;
        if (t.token_type == Token::EF) break;
        tokens.push(t);
    }
    return tokens;
}
Token nextToken(std::string &s) {
    std::smatch match;
    std::regex re;
    Token result;

    if (s.empty()) return Token("", Token::EF);

    re = std::regex(R"(^\s+)"); // match whitespace
    if (std::regex_search(s, match, re)) {
        result = Token(match.str(0), Token::WHITESPACE);
        s = s.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^[A-Za-z]+)"); // match identifier
    if (std::regex_search(s, match, re)) {
        result = Token(match.str(0), Token::IDENTIFIER);
        s = s.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^\d+)"); // match one or more digits
    if (std::regex_search(s, match, re)) {
        result = Token(match.str(0), Token::NUM);
        s = s.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^\+)"); // match plus
    if (std::regex_search(s, match, re)) {
        result = Token(match.str(0), Token::PLUS);
        s = s.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^\-)"); // match minus
    if (std::regex_search(s, match, re)) {
        result = Token(match.str(0), Token::MINUS);
        s = s.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^\*)"); // match mult
    if (std::regex_search(s, match, re)) {
        result = Token(match.str(0), Token::MULT);
        s = s.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^\/)"); // match div
    if (std::regex_search(s, match, re)) {
        result = Token(match.str(0), Token::DIV);
        s = s.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^\()"); // match (
    if (std::regex_search(s, match, re)) {
        result = Token(match.str(0), Token::LEFT_PAREN);
        s = s.substr(match.str(0).size());
        return result;
    }
    re = std::regex(R"(^\))"); // match )
    if (std::regex_search(s, match, re)) {
        result = Token(match.str(0), Token::RIGHT_PAREN);
        s = s.substr(match.str(0).size());
        return result;
    }

    char c = s[0];
    s = s.substr(1);
    return Token(c, Token::UNK);
}

void write(Token &t) {
    std::cout << t << std::endl;
}

// PRECEDENCE CLIMBING PARSER
int main() {
    std::string expr;
    std::ostringstream ss;
    Token t;
    
    for (int i=0;i<10;i++) {
        ss << std::cin.rdbuf();
        expr = ss.str();
        ss.str(std::string());
        clearerr(stdin);

        std::queue<Token> tokens = tokenize_string(expr);

        // for (int it=0; it<tokens.size(); it++) {
        //     std::cout << tokens.front() << '\n';
        //     tokens.push(tokens.front());
        //     tokens.pop();
        // }

        Node *tree = parse_exp(tokens);
        std::cout << tree << std::endl;

        expr.clear();
    }

    return 0;
}