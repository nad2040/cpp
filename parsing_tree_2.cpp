//tree using filesystem
#include<queue>
#include<stack>
#include<string>
#include<iostream>
#include<cmath>
#include<cstddef>
#include<filesystem>

class Token {
public:
    enum TokenType {UNKNOWN, NUM, FUNC, OP, LPAREN, RPAREN};
	bool isNumber() { return tokenType_ == NUM; }
	bool isFunction() { return tokenType_ == FUNC; }
	bool isOperator() { return tokenType_ == OP; }
    bool isLeftParenthesis() { return tokenType_ == LPAREN; }
    bool isRightParenthesis() { return tokenType_ == RPAREN; }

	bool isLeftAssociative() { return tokenValue_ != "^"; }
	int precedence() {
        if (tokenValue_ == "+" || tokenValue_ == "-") { return 2; }
        else if (tokenValue_ == "*" || tokenValue_ == "/") { return 3; }
        else if (tokenValue_ == "^") { return 4; }
        else if (tokenType_ == FUNC) { return 5; }
        return 0;
    }
    int arity() {
        if (tokenValue_ == "sin")
            return 1;
        return 2;
    }

    std::string getValue() {
        return tokenValue_;
    }

    Token() : tokenType_(UNKNOWN), tokenValue_() {}

    Token(int num) {
        tokenType_ = NUM;
        tokenValue_ = std::to_string(num);
    }

    Token(double num) {
        tokenType_ = NUM;
        tokenValue_ = std::to_string(num);
    }

    Token(const std::string& str) {
        if (str == "+" || str == "-" || str == "*" || str == "/" || str == "^") tokenType_ = OP;
        else if (str == "(") tokenType_ = LPAREN;
        else if (str == ")") tokenType_ = RPAREN;
        else tokenType_ = FUNC;
        tokenValue_ = str;
    }

private:
    TokenType tokenType_;
    std::string tokenValue_;
};

class Node {
public:
	Token token_;
	Node* left_;
	Node* right_;

    Node() : token_(), left_(), right_() {}

    Node(Token token) {
        token_ = token;
        left_ = nullptr;
        right_ = nullptr;
    }

    Node(Token token, Node* left, Node* right) {
        token_ = token;
        left_ = left;
        right_ = right;
    }

    std::string returnToken() {
        return token_.getValue();
    }

};

using OutputQueue = std::queue<Token>;
using InputQueue = std::queue<Token>;
using OperatorStack = std::stack<Token>;
using NodeStack = std::stack<Node*>;
namespace fs = std::filesystem;

void displayQueue(std::queue<Token> q) {
    while(!q.empty()) {
        std::cout << q.front().getValue() << " ";
        q.pop();
    }
    std::cout << std::endl;
}

void displayStack(std::stack<Token> s) {
    while(!s.empty()) {
        std::cout << s.top().getValue() << " ";
        s.pop();
    }
    std::cout << std::endl;
}

void displayTree(Node* tree) {
    if (tree != nullptr) {
        fs::create_directory(tree->returnToken());
        fs::current_path(tree->returnToken());
        auto currentp = fs::current_path();
        if (tree->left_ != nullptr) {
            Node* l = tree->left_;
            displayTree(l);
	        fs::current_path(currentp);
        }
        if (tree->right_ != nullptr) {
            Node* r = tree->right_;
            displayTree(r);
	        fs::current_path(currentp);
        }
    }
}

/* This implementation does not implement composite functions,functions with variable number of arguments, and unary operators. */
OutputQueue shuntingYard(InputQueue& inQ) {
	OutputQueue outQ;
	OperatorStack opStack;

	while(!inQ.empty())
    {
	    Token token = inQ.front(); inQ.pop();

        // std::cout << "token: " << token.getValue() << std::endl;
        // std::cout << "outQ: "; displayQueue(outQ);
        // std::cout << "opStack: "; displayStack(opStack);
        // std::cout << std::endl;

	    if (token.isNumber())
        {
		    outQ.push(token);
	    }
        else if (token.isFunction())
        {
		    opStack.push(token); 
	    }
        else if (token.isOperator())
        {
            while (
                !opStack.empty()
                && (opStack.top().precedence() > token.precedence()
                    || (opStack.top().precedence() == token.precedence() && token.isLeftAssociative()))
                && (!opStack.top().isLeftParenthesis()))
                {
                    outQ.push(opStack.top());
                    opStack.pop();
                }
            opStack.push(token);
	    }
	    else if (token.isLeftParenthesis())
        {
		    opStack.push(token);
        }
	    else if (token.isRightParenthesis())
        {
            while (!opStack.top().isLeftParenthesis())
            {
                outQ.push(opStack.top());
                opStack.pop();
            }
            /* If the stack runs out without finding a left parenthesis, then there are mismatched parentheses. */
            if (opStack.top().isLeftParenthesis())
            {
                opStack.pop();
            }
        }
    }
	/* After while loop, if operator stack not null, pop everything to output queue */
    while (!opStack.empty())
    {
        /* If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses. */
        outQ.push(opStack.top());
        opStack.pop();
    }
    
	return outQ;
}

Node* makeTree(OutputQueue& outQ) {
    NodeStack treeStack;

    Node* root = nullptr;

    while (!outQ.empty())
    {
        Token token = outQ.front(); outQ.pop();
        
        if (token.isNumber())
        {
            treeStack.push(new Node(token));
        }
        else if (token.isFunction() || token.isOperator())
        {
            //std::string oper = token.getValue();
            Node* nptr = new Node(token);
            root = nptr;

            if (token.arity() == 2) {
                //Node arg2 = (treeStack.top()); treeStack.pop();
                //Node arg1 = (treeStack.top()); treeStack.pop();
                Node* arg2 = treeStack.top(); treeStack.pop();
                Node* arg1 = treeStack.top(); treeStack.pop();
                //n.token_ = token;
                nptr->left_ = arg1;
                nptr->right_ = arg2;
                treeStack.push(nptr);
            }
        }
    }
    return root;
}

InputQueue tokenizer(std::string inputString) {
    InputQueue inQ;
    int ch = 0;
	while (ch < inputString.length())
	{
        std::string token = "";
		if (inputString[ch] == '+' || inputString[ch] == '-' || inputString[ch] == '*' || inputString[ch] == '/' || inputString[ch] == '^' || inputString[ch] == '(' || inputString[ch] == ')')
        {
            token += inputString[ch];
            //std::cout << "index: " << ch << " token: " << token << std::endl;
            ch++;
            inQ.push(Token(token));
            //displayQueue(inQ);
                      
        }
        else if ((inputString[ch] >= '0' && inputString[ch] <='9') || inputString[ch] == '.')
        {
            while ((inputString[ch] >= '0' && inputString[ch] <='9') || inputString[ch] == '.')
            {
                token += inputString[ch];
                //std::cout << "index: " << ch << " token: " << token << std::endl;
                ch++;
            }
            inQ.push(Token(std::stoi(token)));
            //displayQueue(inQ);
        }
        else if ((inputString[ch] >= 'A' && inputString[ch] <='Z') || (inputString[ch] >= 'a' && inputString[ch] <='z'))
        {
            while ((inputString[ch] >= 'A' && inputString[ch] <='Z') || (inputString[ch] >= 'a' && inputString[ch] <='z'))
            {
                token += inputString[ch];
                //std::cout << "index: " << ch << " token: " << token << std::endl;
                ch++;
            }
            inQ.push(Token(token));
            //displayQueue(inQ);
        }
        else {
            ch++;
        }
	}
	//if (token != "") inQ.push(Token(token));
	
	return inQ;    
}

int main() {

    fs::create_directory("temp");
    fs::current_path("temp");

    InputQueue inQ = tokenizer("3+4*5+3");
    OutputQueue outQ = shuntingYard(inQ);
    displayQueue(outQ);
    Node* root = makeTree(outQ);
    std::cout << root->returnToken() << " " << root->left_->returnToken() << " " << root->right_->returnToken() << std::endl;
    displayTree(root);

    return 0;
}
