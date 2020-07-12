#include<iostream>
#include<cmath>
#include<vector>
#include<set>
#include<algorithm>
#include<sstream>

using namespace std;

vector<pair<int,int>> factorPair(int n) {
    vector<pair<int,int>> factorPairs;
    for (int i=1; i<=sqrt(n); i++){
        if (n%i == 0) {
            factorPairs.insert(factorPairs.end(),pair<int,int> (i,n/i));
        }
    }
    return factorPairs;
}

void displayPair(pair<int, int> p) {
    cout << p.first << '\t' << p.second << endl;
}

void displayPairs(const vector<pair<int,int>>& pairs) {
    for (int i=0; i<pairs.size(); i++){
        displayPair(pairs[i]);
    }
    // for (auto elem : pairs) {
    //     display(elem);
    // }
}

// int nDigit(int a, int n) {
//     return a/((int)pow(10,n))%10;
// }

// void returnDigits(int x, set<int>& digits) {
//     for (int i=0; i<(floor(log(x))); i++) {
//         digits.insert(nDigit(x,i));
//     }
// }    

set<int> getDigits(int n) {
    set<int> digits;
    while(n>0) {
        digits.insert(n%10);
        n /= 10;
    }
    return digits;
}

set<int> vectorToSet(const vector<int>& v) {
    set<int> s;
    for (auto i : v)
        s.insert(i);
    return s;
}

bool isGoodPair(const pair<int, int>& data1, const pair<int, int>& data2) {

    stringstream os;
    os << data1.first << data1.second << data2.first << data2.second;

    if (os.str().length() == 9) {
        uint32_t num;
        os >> num;
        auto dset = getDigits(num);
        return dset.size() == 9 && dset.find(0) == dset.end(); 
    }

    return false;
}

void findPairs(const vector<pair<int, int>>& pairs) {
    for (int i=0; i<pairs.size(); ++i) {
        for (int j=i+1; j<pairs.size(); ++j) {
            if (isGoodPair(pairs[i], pairs[j])) {
                cout << pairs[i].first << " " << pairs[i].second << " ";
                cout << pairs[j].first << " " << pairs[j].second << " ";
                cout << pairs[i].first*pairs[i].second << endl;
            }
        }
    }
}

int main() {
    int num = 1000;
    //for(auto i : getDigits(num)) cout << i << endl;
    //displayPairs(factorPair(num));
    // for(auto i : factorPair(num)) {
    //     cout << isGoodPair(i) << endl;
    // }
    //testFunc();
    
    for(num; num<10000; ++num) {
        findPairs(factorPair(num));
    }
}
/*
int main() {
    set<int> factorDigits{};
    int a,b;
    bool flag = false;
    while (flag == false) {
        for (int i=100000; i<1000000; i++) {
            factorPair(i);
            for (a=0; a<factorPairs.size(); a++) {
                for (b=a+1; b<factorPairs.size(); b++) {
                    returnDigits(factorPairs[a].first, factorDigits);
                    returnDigits(factorPairs[a].second, factorDigits);
                    returnDigits(factorPairs[b].first, factorDigits);
                    returnDigits(factorPairs[b].second, factorDigits);

                    if (factorDigits.contains()) {
                        flag = true;
                        cout << i << endl;
                        for (auto it=factorDigits.begin(); it != factorDigits.end(); ++it) {
                            cout << ' ' << *it;
                        }
                    }
                    factorPairs.clear();
                    factorDigits.clear();
                }
            }
        }
        if (flag == false) {break;}
    }


    return 0;
}
*/