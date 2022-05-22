#include <iostream>
#include <variant>
#include <string>
#include <vector>

struct Token {
    std::variant<int, std::string> val;
    enum { NUM, OP } token_type;
    
    std::string get_op() { return std::get<std::string>(val); }
    int get_num() { return std::get<int>(val); }

    bool isOp() { return token_type == OP; }
    bool isNum() { return token_type == NUM; }

    int precedence() {
        if (std::get<std::string>(val)[0] == '+' || std::get<std::string>(val)[0] == '-') return 1;
        else return 2;
    }

    Token(std::string str) : token_type(OP) { val = str; }
    Token(int num) : token_type(NUM) { val = num; }

    friend std::ostream & operator<<(std::ostream &out, Token token) {
        if (token.isOp()) out << token.get_op();
        else if (token.isNum()) out << token.get_num();
        return out;
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

bool isOp(char c) { return c == '*' || c == '/' || c == '+' || c == '-'; }
bool isNum(char c) { return (c ^ '0') < 10; }

std::vector<Token> read_string(std::string& str) {
    std::vector<Token> tokens;
    for (int i=0; i<str.length(); i++) {
        if (isNum(str[i])) {
            int pos = i;
            while (isNum(str[++i]));
            tokens.push_back(Token(stoi(str.substr(pos,i))));
            --i;
        }
        else if (isOp(str[i])) {
            tokens.push_back(Token(std::string(1,str.at(i))));
        }
    }
    return tokens;
}

Node *parse(std::vector<Token>&, int);
Node *parse_exp(std::vector<Token>&);
Node *parse_exp_l(std::vector<Token>&, Node *, int);

int ind=0;

Node *parse(std::vector<Token>& tokens, int pos) {
    return new Node(tokens[pos]);
}

Node *parse_exp(std::vector<Token>& tokens) {
    return parse_exp_l(tokens, parse(tokens, ind), 0);
}

Node *parse_exp_l(std::vector<Token>& tokens, Node *l, int min_precedence) {
    Token lookahead = tokens[ind+1];
    while (ind < tokens.size() && lookahead.isOp() && lookahead.precedence() >= min_precedence) {
        Token op = lookahead;
        ind+=2;
        Node *r = parse(tokens, ind);
        lookahead = tokens[ind+1];
        while (ind < tokens.size() && lookahead.isOp() && lookahead.precedence() > op.precedence()) {
            r = parse_exp_l(tokens, r, op.precedence() + (lookahead.precedence() > op.precedence() ? 1 : 0));
            lookahead = tokens[ind+1];
        }
        l = new Node(l, r, op);
    }
    return l;
}

// PRECEDENCE CLIMBING PARSER
int main() {
    std::string expr;
    while (1) {
        std::getline (std::cin, expr);
        if (expr.empty()) break;
        std::vector<Token> tokens = read_string(expr);

        // for (Token &t: tokens) std::cout << t << ' ';
        // std::cout << std::endl;

        Node *tree = parse_exp(tokens);
        std::cout << tree << std::endl;
    }

    return 0;
}