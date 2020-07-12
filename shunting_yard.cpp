#include<queue>
#include<stack>
#include<string>
#include<iostream>
#include<cmath>

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

using OutputQueue = std::queue<Token>;
using InputQueue = std::queue<Token>;
using OperatorStack = std::stack<Token>;

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

typedef double ResultType;
ResultType eval(OutputQueue& outQ) {
    OperatorStack calcStack;

    while (!outQ.empty())
    {
        Token token = outQ.front(); outQ.pop();

        if (token.isNumber())
        {
            calcStack.push(token);
        }
        else if (token.isFunction() || token.isOperator())
        {
            std::string oper = token.getValue();
            if (token.arity() == 2) {
                ResultType arg2 = std::stod(calcStack.top().getValue()); calcStack.pop();
                ResultType arg1 = std::stod(calcStack.top().getValue()); calcStack.pop();

                if (oper == "^") calcStack.push(pow(arg1,arg2));
                else if (oper == "*") calcStack.push(arg1 * arg2);
                else if (oper == "/") calcStack.push(arg1 / arg2);
                else if (oper == "+") calcStack.push(arg1 + arg2);
                else if (oper == "-") calcStack.push(arg1 - arg2);
                else if (oper == "max") calcStack.push(std::max(arg1,arg2));
            }
            else if (token.arity() == 1) {
                ResultType arg = std::stod(calcStack.top().getValue()); calcStack.pop();

                if (oper == "sin") calcStack.push(std::sin(arg));
                else if (oper == "cos") calcStack.push(std::cos(arg));
                else if (oper == "tan") calcStack.push(std::tan(arg));
            }
        }
    }
    
    ResultType result;
    if (calcStack.size() == 1)
    {
        result = std::stod(calcStack.top().getValue());
    }

    return result;
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
            inQ.push(Token(std::stod(token)));
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
    //InputQueue inQ = tokenizer("356 - 128.5 * 2  - 5");
    //InputQueue inQ = tokenizer("3+12.8*2/(1-3)^2^3");
    //InputQueue inQ = tokenizer("sin(max(2, 3) /   3 * 3.1415)");
    std::cout << "Enter an expression or `quit` to exit:\n";
    
    std::string inputString;
    while (true)
    {
        std::getline(std::cin, inputString);
        if (inputString == "quit") break;
        InputQueue inQ = tokenizer(inputString);
        OutputQueue outQ = shuntingYard(inQ);
        std::cout << eval(outQ) << "\n";
    }

    return 0;
}
