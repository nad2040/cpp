#include<iostream>
using namespace std;

double G = 6.67e-11;

double d(double v0, double a, double t);
double Vf(double v0, double a, double t);
double Fg(double m1, double m2, double r);

int main() {
    double m1 = 5.98e+24;
    double m2 = 7.35e+22;
    double r = 3.84e+8;
    cout << "The force between Earth and moon is " << Fg(m1, m2, r) << endl;
    double v0 = 0;
    double a = 9.81;
    double t = 16;
    cout << "The final velocity in the fall is " << Vf(v0, a, t) << endl;
    cout << "The distance is " << d(v0, a, t) << endl;
}

double d(double v0, double a, double t) {
    return v0*t + a*t*t/2;
}

double Vf(double v0, double a, double t) {
    return v0 + a*t;
}

double Fg(double m1, double m2, double r) {
    return (G*m1*m2)/(r*r);
}