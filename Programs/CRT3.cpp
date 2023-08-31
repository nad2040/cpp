#include <iostream>
#include <vector>

typedef struct {
    long remainder;
    long modulus;
    long N;
    long z;
} CRT;

std::vector<CRT> rsystem;

void dump(std::vector<CRT> &rsystem) {
    for(auto rm: rsystem) {
        std::cout << rm.remainder << ',' << rm.modulus << ',' << rm.N << ',' << rm.z << '\n';
    }
}

int calcBigN(std::vector<CRT> &rsystem) {
    long N = 1;
    for (auto rm: rsystem) N *= rm.modulus;
    return N;
}

void calcN(std::vector<CRT> &rsystem) {
    long bigN = calcBigN(rsystem);
    for (auto& rm: rsystem) {
        rm.N = bigN/rm.modulus;
    }
}

void inverse(std::vector<CRT> &rsystem) {
    for (auto& rm: rsystem) {
        for (long i=1; i<rm.modulus; ++i) {
            if (rm.N*i % rm.modulus == 1)
                rm.z = i;
        }
    }
}

void solve(std::vector<CRT> &rsystem) {
    calcN(rsystem);
    inverse(rsystem);
    long sum = 0;
    long bigN = calcBigN(rsystem);
    for (auto& rm: rsystem)
        sum += rm.remainder*rm.N*rm.z;
        sum %= bigN;
    std::cout << sum << '\n';
}

int main(){
    CRT rm;
    while(std::cin >> rm.remainder >> rm.modulus) {
        rsystem.push_back(rm);
    }
    solve(rsystem);
    return 0;
}
