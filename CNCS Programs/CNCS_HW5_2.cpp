#include<iostream>
using namespace std;

int gcd(int, int);
int totient(int);

int main() {
    cout << "gcd(15,39) = " << gcd(15,39) << endl;
    cout << "gcd(24,10) = " << gcd(24,10) << endl;
    cout << "gcd(5643,2564) = " << gcd(5643,2564) << endl;
    for (int i=1; i<=15; i++) {
        cout << i << " totient is: " << totient(i) << endl;
    }
}

int gcd(int a , int b) {
    if (a==b) return a;
    else if (a > b) {
        if (b==0) return a;
        return gcd(b,a%b);
    }
    else {
        if (a==0) return b;
        return gcd(a,b%a);
    }
}

int totient(int val) {
    int i,count;
    count = 0;
    for (i=1; i<=val; i++)
        if (gcd(i,val)==1)
            count+=1;
    return count;
}