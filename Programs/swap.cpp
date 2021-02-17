//add a comment
#include<iostream>
using namespace std;

template<typename T>
void mySwap(T& a, T& b){
    T x = a;
    a = b;
    b = x;
}

template<typename U, typename V>
void dump(U& u, V& v) {
    std::cout << u << " " << v << endl;
}

int main(){
    float a = 30.5;
    float b = 60.7;
    mySwap(a,b);
    cout << a << " " << b << endl;
    int m = 3;
    int n = 67;
    mySwap(m,n);
    cout << m << " " << n << endl;

    dump(a, m);
    dump(n, b);
    return 0;
}
