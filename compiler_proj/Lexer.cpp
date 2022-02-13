#include "Token.h"

#include <iostream>
#include <queue>

using OutputQueue = std::queue<Token>;
using InputQueue = std::queue<Token>;

InputQueue lexer(std::string inputString) {
    InputQueue inQ;
    int ch = 0;
	while (ch < inputString.length())
	{
        std::string token = "";
		if (inputString[ch] == '+' || inputString[ch] == '-' || inputString[ch] == '*' || inputString[ch] == '/' || inputString[ch] == '^' || inputString[ch] == '(' || inputString[ch] == ')')
        {
            token += inputString[ch];
            ch++;
            inQ.push(Token(token));
                      
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