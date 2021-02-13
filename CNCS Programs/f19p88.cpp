//p88 is p16 using functions
#include<iostream>
using namespace std;

void nosol();
void allsol();
double onesol(double,double);

int main(){
	double a,b;
	cout<<"Enter two numbers: \n";
	cin>>a>>b;
	if (a==0)
		if (b==0)
			allsol();
		else
			nosol();
	else
		cout<<"The solution is x = "<<onesol(a,b)<<endl;
}

void allsol(){
	cout<<"All solutions\n";
}

void nosol(){
	cout<<"No solution\n";
}

double onesol(double a, double b){
	return -b/a;
}
