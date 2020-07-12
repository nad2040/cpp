#include <iostream>
#include <cmath>

bool isPrime(int n) {
    for (int i=2; i<=n/2; i++)
        if (n%i == 0)
            return false;
    return true;
}

int gcd(int a, int b) {
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

int lcm(int a, int b) {
    if (a==b) return a;
    else return a*b/gcd(a,b);
}

int phi(int val) {
    int i,count;
    count = 0;
    for (i=1; i<=val; i++)
        if (gcd(i,val)==1)
            count+=1;
    return count;
}

int tau(int n) {
    int count = 0;
    for (int i=1; i<=n; i++)
        if (n%i == 0)
            count++;
    return count;
}

int sigma(int n) {
    int sum = 0;
    for (int i=1; i<=n; i++)
        if (n%i == 0) {
            sum += i;
        }
    return sum;
}

bool isPerfect(int n) {
    if (sigma(n) == 2*n)
        return true;
    else
        return false;
}

int primroot(int n) {
    return phi(phi(n));
}

int pow_mod_b(int a, int n, int b) {
    if (a>=b) {
        int x = a%b;
        return (int)pow(x,n) % b;
    }
    else {
        int y = pow(a,n);
        return y%b;
    }
}

int fib(int n) {
    if (n==0)
        return 0;
    else if (n==1)
        return 1;
    else
        return fib(n-2)+fib(n-1);
}