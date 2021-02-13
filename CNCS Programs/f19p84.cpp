#include<iostream>
using namespace std;
void sum();

int main(){
	cout<<"Hello Again.\n";
	sum();
	cout<<"bye\n";
	return 0;
}

void sum(){
	float a,b,c;
	cout<<"Enter two numbers: \n";
	cin>>a>>b;
	c=a+b;
	cout<<"The sum of the two numbers is "<<c<<endl;
}
