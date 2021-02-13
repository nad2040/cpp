//p87 is p85 with parameters
#include<iostream>
using namespace std;
double sum(double, double);
double product(double, double);
double difference(double, double);
int main(){
	double a,b;
	cout<<"Hello Again.\n";
	cout<<"Enter two numbers: \n";
	cin>>a>>b;
	cout<<"The sum is "<<sum(a,b)<<endl;
	cout<<"The product is "<<product(a,b)<<endl;
	cout<<"The difference is "<<difference(a,b)<<endl;
	return 0;
}

double sum(double a, double b){
	return a+b;
}

double product(double a, double b){
	return a*b;
}

double difference(double a, double b){
	return a-b;
}
