#include <iostream>

struct Node {
    Node *left,*right;
    char value;
    bool leaf;

    Node(char c) : value(c), left(nullptr), right(nullptr), leaf(true) {}
    Node(Node *l, Node *r, char c) : value(c), left(l), right(r), leaf(false) {}
    bool isOp() {return value == '*' || value == '/' || value == '+' || value == '-';}
    bool isNum() {return (value ^ '0') < 10;}
    
    friend std::ostream & operator<<(std::ostream &out, Node* node) {
        static int depth = 0;
        if (node->leaf) {
            for (int i=0; i<depth; i++) std::cout << "  ";
            std::cout << node->value << '\n';
        } else {
            for (int i=0; i<depth; i++) std::cout << "  ";
            std::cout << node->value << '\n';
            depth++;
            std::cout << node->left;
            std::cout << node->right;
            depth--;
        }
        return out;
    }
};

bool isOp(char c) {return c == '*' || c == '/' || c == '+' || c == '-';}
bool isNum(char c) {return (c ^ '0') < 10;}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    else return 2;
}

Node *parse(int);
Node *parse_exp();
Node *parse_exp_l(Node *, int);

char str[] = "1+2*3-4+5/6";
int len = sizeof(str)-1;
int ind = 0;

Node *parse(int pos) {
    return new Node(str[ind]);
}

Node *parse_exp() {
    return parse_exp_l(parse(ind), 0);
}

Node *parse_exp_l(Node *l, int min_precedence) {
    char lookahead = str[ind+1];
    while (ind < len && isOp(lookahead) && precedence(lookahead) >= min_precedence) {
        char op = lookahead;
        ind+=2;
        Node *r = parse(ind);
        lookahead = str[ind+1];
        while (ind < len && isOp(lookahead) && precedence(lookahead) > precedence(op) ) {
            r = parse_exp_l(r, precedence(op) + (precedence(lookahead) > precedence(op) ? 1 : 0));
            lookahead = str[ind+1];
        }
        l = new Node(l, r, op);
    }
    return l;
}

// PRECEDENCE CLIMBING PARSER
int main() {
    Node *tree = parse_exp();
    std::cout << tree;
}