#include<iostream>
#include<cmath>
#include<set>

using namespace std;

int nDigit(long a, long n) {
    return a/((int)pow(10,n-1))%10;
}

bool isGoodNum(long a) {
    set<int> dset = {1,2,3,4,5,6,7,8,9,0};
    for (int i=1; i<10; i++){
        int j = nDigit(a, i);
        dset.erase(j);
    }
    return dset.size() == 1;
}

long i = 100000000;
int main() {
    for (i; i<120000000; i++) {
        if (isGoodNum(i)) {
            if (i%11 == 0){
                cout << i << endl;
            }
        }
    }
    return 0;
}
