#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

typedef struct {
    int remainder;
    int modulus;
    int y;
    int z;
} CRT;

vector<CRT> rsystem;

void dump(vector<CRT> &rsystem) {
    for(auto rm: rsystem) {
        cout << rm.remainder << ',' << rm.modulus << ',' << rm.y << ',' << rm.z << endl;
    }
}

int calcN(vector<CRT> &rsystem) {
    long N = 1;
    for (auto rm: rsystem)
        N *= rm.modulus;
    return N;
}

void calcY(vector<CRT> &rsystem) {
    long bigN = calcN(rsystem);
    for (auto& rm: rsystem) {
        rm.y = bigN/rm.modulus;
    }
}

void inverse(vector<CRT> &rsystem) {
    for (auto& rm: rsystem) {
        for (int i=1; i<=rm.modulus; ++i) {
            if (rm.y*i % rm.modulus == 1)
                rm.z = i;
        }
    }
}

void solver(vector<CRT> &rsystem) {
    calcY(rsystem);
    inverse(rsystem);
    long sum = 0;
    for (auto& rm: rsystem)
        sum += rm.remainder*rm.y*rm.z;
    sum %= calcN(rsystem);
    cout << sum << endl;
}

int main(){
    CRT rm;
    while(cin >> rm.remainder >> rm.modulus) {
        rsystem.push_back(rm);
    }
    solver(rsystem);
    return 0;
}