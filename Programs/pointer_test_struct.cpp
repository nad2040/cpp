#include <iostream>
using namespace std;

struct myStruct {
    int a;
    float b;
    double c;
};

int main() {
    myStruct hello;
    hello.a = 3, hello.b = 3.14, hello.c = 3.14159;
    cout << sizeof(hello) << endl;
    cout << &hello << " " << &hello.a << " " << &hello.b << " " << &hello.c << endl;
}