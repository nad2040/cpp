#include<iostream>
#include<cmath>
using namespace std;
int main(){
	double a,b,c,x,x1,x2,D;
	cout<<"enter 3 coefficients: \n";
	cin>>a>>b>>c;
	if (a==0)
		if (b==0)
			if (c==0)
				cout<<"all solutions\n";
			else
				cout<<"no solutions\n";
		else{
			cout<<"linear\n";
			x=-c/b;
			cout<<"x = "<<x<<endl;
			}
	else {
		D=b*b-4*a*c;
		if (D==0){
			cout<<"duplicate solution\n";
			x=-b/(2*a);
			cout<<"x = "<<x<<endl;
			}
		else if (D<0)
				cout<<"no solution\n";
			else{
				cout<<"two solutions\n";
				x1=(-b+sqrt(D))/(2*a);
				x2=(-b-sqrt(D))/(2*a);
				cout<<"x1 = "<<x1<<"\n"<<"x2 = "<<x2<<endl;
			}
		}
	return 0;		
}
