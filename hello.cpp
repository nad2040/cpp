#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>

int main() {
    using namespace std;
    cout << "Hello World!" << endl;
    
    vector<int> v{1,1,2,2,3,3,4,4,5,5,6,6};
    //for(auto i : v) cout << i << ' ';
    
    random_device rd;
    mt19937 g(rd());

    shuffle(v.begin(), v.end(), g);
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    cout << '\n';
    
    uniform_int_distribution<int> dist1(0,5);
    uniform_int_distribution<int> dist2(6,11);
    
    int count = 0;
    for(auto i=0; i<1000000; ++i) {
        shuffle(v.begin(), v.end(), g);
        int key1 = dist1(g);
        int key2 = dist2(g);
        //cout << key1 << ' ' << key2 << ' ' << v[key1] << ' ' << v[key2] << '\n';
        if (v[key1] + v[key2] == 7) ++count;
    }
    cout << count << '\n';
}
