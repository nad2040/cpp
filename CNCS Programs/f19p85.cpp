#include<iostream>
using namespace std;
void sum();
void product();
void difference();
int main(){
	cout<<"Hello Again.\n";
	sum();
	product();
	difference();
	return 0;
}

void sum(){
	float a,b,c;
	cout<<"Enter two numbers: \n";
	cin>>a>>b;
	c=a+b;
	cout<<"The sum of the two numbers is "<<c<<endl;
}

void product(){
	float a,b,c;
	cout<<"Enter two numbers: \n";
	cin>>a>>b;
	c=a*b;
	cout<<"The product of the two numbers is "<<c<<endl;
}

void difference(){
	float a,b,c;
	cout<<"Enter two numbers: \n";
	cin>>a>>b;
	c=a-b;
	cout<<"The difference between the two numbers is "<<c<<endl;
}
