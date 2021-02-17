#include<iostream>
#include<cmath>
#include<vector>
#include<set>
#include<algorithm>

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

vector<int> getDigits(int n) {
    vector<int> digits;
    while(n>0) {
        digits.push_back(n%10);
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

void testFunc() {
    auto data1 = make_pair(4, 2379);
    auto data2 = make_pair(6, 1586);
    auto dset1 = getDigits(data1.first);
    auto dset2 = getDigits(data1.second);
    auto dset3 = getDigits(data2.first);
    auto dset4 = getDigits(data2.second);

    vector<int> dset_union{};
    vector<int> dset_union2{};

    merge(dset1.begin(), dset1.end(), dset2.begin(), dset2.end(), back_inserter(dset_union));
    for (auto elem : dset_union) { cout << elem << " "; } cout << " dset_union step1 " << endl;
    merge(dset3.begin(), dset3.end(), dset4.begin(), dset4.end(), back_inserter(dset_union));
    for (auto elem : dset_union) { cout << elem << " "; } cout << " dset_union step2 " << endl;


    auto totalDset = vectorToSet(dset_union);


    displayPair(data1);
    displayPair(data2);
    for (auto d: dset1) { cout << d << " "; } cout << " dset1 " << endl;
    for (auto d: dset2) { cout << d << " "; } cout << " dset2 " << endl;
    for (auto d: dset3) { cout << d << " "; } cout << " dset3 " << endl;
    for (auto d: dset4) { cout << d << " "; } cout << " dset4 " << endl;

    for (auto elem : totalDset) { cout << elem << " "; } cout << " totalDset " << endl;
    for (auto elem : dset_union) { cout << elem << " "; } cout << " dset_union " << endl;
    cout << "-----" << endl;

}

bool isGoodPair(const pair<int, int>& data1, const pair<int, int>& data2) {
    auto dset1 = getDigits(data1.first);
    auto dset2 = getDigits(data1.second);
    auto dset3 = getDigits(data2.first);
    auto dset4 = getDigits(data2.second);

    //vector<int> dset_inter{};
    vector<int> dset_union{};
    merge(dset1.begin(), dset1.end(), dset2.begin(), dset2.end(), back_inserter(dset_union)); 
    merge(dset3.begin(), dset3.end(), dset4.begin(), dset4.end(), back_inserter(dset_union));
 

    //set_intersection(dset1.begin(), dset1.end(), dset2.begin(), dset2.end(), back_inserter(dset_inter));
    //cout << "union size:" << dset_union.size() << " set1: " << dset1.size() << " set2: " << dset2.size() << endl;
    //for (auto i : vectorToSet(dset_union)) cout << i << ' ';
    //cout << endl;

    auto totalDset = vectorToSet(dset_union);
    return dset_union.size() == totalDset.size()
            && totalDset.size() == 9
            && totalDset.find(0) == totalDset.end();
    //return false;
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