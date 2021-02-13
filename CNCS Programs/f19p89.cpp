//p89 is p17 with functions
#include<iostream>
#include<cmath>
using namespace std;

void allsol();
void nosol();
double onesol(double, double);
double dupsol(double, double);
double twosol1(double, double, double);
double twosol2(double, double, double);

int main(){
	double a,b,c,D;
	cout << "enter 3 coefficients: \n";
	cin>>a>>b>>c;
	if (a==0)
		if (b==0)
			if (c==0)
				allsol();
			else
				nosol();
		else
			cout << onesol(b,c);
	else{
		D = b*b - 4*a*c;
		if (D<0)
			nosol();
		else if (D>0){
				cout << "2 solutions\n";
				cout << twosol1(a,b,D) << "\n" << twosol2(a,b,D) << endl;
					}
			else{
				cout << dupsol(a,b);
				}
		}
	return 0;
}
void allsol(){
	cout<<"All solutions\n";
}
void nosol(){
	cout<<"No solutions\n";
}
double onesol(double b, double c){
	cout << "Linear\nx = ";
	return -c/b;
}
double dupsol(double a, double b){
	cout << "Duplicate solution\nx = ";
	return -b/(2*a);
}
double twosol1(double a, double b, double D){
	cout << "x1 = ";
	return (-b+sqrt(D))/(2*a);
}
double twosol2(double a, double b, double D){
	cout << "x2 = ";
	return (-b-sqrt(D))/(2*a);
}
