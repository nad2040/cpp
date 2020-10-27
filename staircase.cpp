#include <iostream>
#include <vector>

using namespace std;

void displaySteps(vector<int> &v) {
    for (auto e : v) cout << e << " ";
    cout << endl;
}

void solve(int start, int end, vector<int> steps) {
    static int solutionCount = 0;
    steps.push_back(start);
    if (start > end) {
        steps.pop_back();
        return;
    } else if (start == end) {
        displaySteps(steps);
        cout << ++solutionCount << "\n\n";
        return;
    }
    for (int i=1; i<3; ++i) {
        solve(start+i,end,steps);
    }
}

long staircase(long n) {
    if (n == 1) return 1;
    if (n == 2) return 2;

    long cache[n+1];
    cache[1] = 1;
    cache[2] = 2;

    for (int i=3; i<=n; ++i) {
        cache[i] = cache[i-1] + cache[i-2];
    }

    return cache[n];
}


int main() {
    vector<int> steps;
    long n=5;

    solve(0,n,steps);
    cout << staircase(n) << endl;
}