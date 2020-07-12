#include <iostream>
using namespace std;

int main() {
    int i = 5, j = 6;
    float f1 = 0.5, f2 = 3.14;
    double g1 = 0.5000001, g2 = 3.1415;
    int *iPtr = &i, *jPtr = &j;
    float *f1Ptr = &f1, *f2Ptr = &f2;
    double *g1Ptr = &g1, *g2Ptr = &g2;
    cout << "pointer to i " << iPtr << " value of this pointer is " << *iPtr << endl;
    cout << "pointer to j " << jPtr << " value of this pointer is " << *jPtr << endl;
    cout << "pointer to f1 " << f1Ptr << " value of this pointer is " << *f1Ptr << endl;
    cout << "pointer to f2 " << f2Ptr << " value of this pointer is " << *f2Ptr << endl;
    cout << "pointer to g1 " << g1Ptr << " value of this pointer is " << *g1Ptr << endl;
    cout << "pointer to g2 " << g2Ptr << " value of this pointer is " << *g2Ptr << endl;
    cout << sizeof(int) << endl;
    cout << sizeof(float) << endl;
    cout << sizeof(double) << endl;
    cout << sizeof(int*) << endl;
    cout << sizeof(float*) << endl;
    cout << sizeof(double*) << endl;
    cout << &iPtr << endl;
    cout << &jPtr << endl;
    cout << &f1Ptr << endl;
    cout << &f2Ptr << endl;
    cout << &g1Ptr << endl;
    cout << &g2Ptr << endl;
}