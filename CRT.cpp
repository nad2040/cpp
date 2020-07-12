#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

typedef struct {
    int remainder;
    int modulus;
} rmpair;

vector<rmpair> rsystem;

void solver(vector<rmpair> &rsystem) {
    for (int i=0;;++i) {
        bool bad = false;
        for(auto rm: rsystem) {
            if (i % rm.modulus != rm.remainder)
                bad = true;
        }
        if (!bad) {
            cout << i << endl;
            break;
        }
    }
}

int main(){
    rmpair rm;
    while(cin >> rm.remainder >> rm.modulus) {
        rsystem.push_back(rm);
    }
    solver(rsystem);

    return 0;
}