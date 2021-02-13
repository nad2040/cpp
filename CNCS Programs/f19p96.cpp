//p95 with return val
#include<iostream>
using namespace std;

const double pi = 3.141592653589793238462643383;

double area(double area, double r){
	area = pi*r*r;
	return area;
}

double circumference(double circumference, double r){
	circumference = 2*pi*r;
	return circumference;
}

int main(){
	double r1,a,c;
	cout << "Enter radius: ";
	cin >> r1;
	cout << "Area = " << area(a,r1) << ", Circumference = " << circumference(c,r1) << endl;
	return 0;
}
