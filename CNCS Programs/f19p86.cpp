#include<iostream>
using namespace std;
float sum(float,float);

int main(){
	cout<<"Hello Again.\n";
	float a,b;
	cout<<"Enter two numbers: \n";
	cin>>a>>b;
	cout<<"The sum of the two numbers is "<<sum(a,b)<<endl;
	return 0;
}
float sum(float a1, float b1){
	float c;
	c=a1+b1;
	return c;
}
