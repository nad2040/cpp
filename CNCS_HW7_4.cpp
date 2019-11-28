#include <iostream>
#include <cmath>

using namespace std;

class PolynomialSolver {
public:
    PolynomialSolver(double aa, double bb, double cc) : a(aa), b(bb), c(cc)
    {
    }
    void solve() {
        cout << "Equation: " << a << "x^2 + " << b << "x + " << c << endl;
        if (a==0)
            if (b==0)
                if (c==0)
                    allsol();
                else
                    nosol();
            else
                onesol(b,c);
        else {
            double D = b*b - 4*a*c;
            if (D<0)
                nosol();
            else if (D>0) {
                    twosol(a,b,D);
                }
                else
                    dupsol(a,b);
        }
    }
private:
    void allsol(){
        cout << "All solutions\n";
    }
    void nosol(){
        cout << "No solutions\n";
    }
    void onesol(double b, double c){
        double x = -c/b;
        cout << "Linear\nx = " << x << endl;
    }
    void dupsol(double a, double b){
        double x = -b/(2*a);
        cout << "Duplicate solution\nx = " << x << endl;
    }
    void twosol(double a, double b, double D) {
        double x1,x2;
        cout << "2 solutions\n";
        x1 = (-b+sqrt(D))/(2*a);
        cout << "x1 = " << x1 << endl;
        x2 = (-b-sqrt(D))/(2*a);
        cout << "x2 = " << x2 << endl;
    }
    double a;
    double b;
    double c;
};

int main() {
    PolynomialSolver poly1(1, 1, 1);
    PolynomialSolver poly2(1, 4, 2);
    poly1.solve();
    poly2.solve();
    return 0;
}