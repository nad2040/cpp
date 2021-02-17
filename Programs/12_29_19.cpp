#include <iostream>
#include <cmath>
using namespace std;

long long mypow(int x, int y) {
    long long result=1;
    for(; y>0; --y) {
        result *= x;
    }
    return result;
}

int main() {
    int a,b;
    for (b=2; b<20; ++b)
        for (a=2; a<b+3; ++a)
            if ((mypow(a,b)+1)%(mypow(b,a)+1) == 0)
                cout << a << ", " << b << endl;
}