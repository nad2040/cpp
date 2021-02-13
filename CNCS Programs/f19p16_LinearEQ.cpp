#include<iostream>
using namespace std;
int main(){
	float a,b,x;
	cout<<"Enter 2 coefficients: \n";
	cin>>a>>b;
	if(a==0)
		if(b==0)
			cout<<"all solutions\n";
		else
			cout<<"no solutions\n";
	else {
		cout<<"one solution:\n";
		x=-b/a;
		cout<<"x = "<<x<<endl;
	}
	return 0;
}
