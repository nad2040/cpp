#include<iostream>
using namespace std;
int main(){
    int a,b;
    cin >> a >> b;
    if (a == b)
        cout << "distinct numbers only\n";
    else {
        if (a>b)
            cout << a <<" is greater\n" << endl;
        else {
            cout << b <<" is greater\n" << endl;
        }
    }

    return 0;
    }
