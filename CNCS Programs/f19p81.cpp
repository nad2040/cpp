#include<iostream>
#include<cmath>
#include<cctype>
#include<cstdlib>
using namespace std;

int main() {
	//sqrt func
	double num,answer;
	cout<<"Pre-defined Function: sqrt(x)\nEnter a number\n";
	cin>>num;
	answer=sqrt(num);
	cout<<"The square root of "<<num<<" is "<<answer<<endl;
	
	//power func
	double base,exp;
	cout<<"Pre-defined Function: pow(x,y)\nEnter a base and exp\n";
	cin>>base>>exp;
	answer=pow(base,exp);
	cout<<base<<" to the power of "<<exp<<" is "<<answer<<endl;
	
	//abs func
	int x,y;
	cout<<"Pre-defined Function: abs(x)\nEnter an integer\n";
	cin>>x;
	y=abs(x);
	cout<<"The absolute value of "<<x<<" is "<<y<<endl;
	
	//lowercase func
	char L,l;
	cout<<"Pre-defined Function: tolower(x)\nEnter an uppercase letter\n";
	cin>>L;
	l=tolower(L);
	cout<<"The lowercase version of "<<L<<" is "<<l<<endl;
	
	//Uppercase func
	cout<<"Pre-defined Function: toupper(x)\nEnter an lowercase letter\n";
	cin>>l;
	L=toupper(l);
	cout<<"The uppercase version of "<<l<<" is "<<L<<endl;
	
	return 0;
}
