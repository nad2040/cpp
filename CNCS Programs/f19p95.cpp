//p95 is p94 with 2 func
#include<iostream>
using namespace std;

const double pi = 3.141592653589793238462643383;

void area(double &area, double r){
	area = pi*r*r;
}
void circumference(double &circumference, double r){
	circumference = 2*pi*r;
}

int main(){
	double r1,a,c;
	cout << "Enter radius: ";
	cin >> r1;
	area(a,r1);
	circumference(c,r1);
	cout << "Area = " << a << ", Circumference = " << c << endl;
	return 0;
}
