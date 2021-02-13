//p94
#include<iostream>
using namespace std;

void computingCircle(double &area, double &circumference, double r){
	const double pi = 3.141592653589793238462643383;
	area = pi*r*r;
	circumference = 2*pi*r;
}

int main(){
	double r1,a,c;
	cout << "Enter radius: ";
	cin >> r1;
	computingCircle(a,c,r1);
	cout << "Area = " << a << ", Circumference = " << c << endl;
	return 0;
}
