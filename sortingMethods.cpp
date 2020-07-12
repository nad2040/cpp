#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include<iterator>
#include "timing.h"

using namespace std;

template<typename T>
void dmerge(vector<T>& v, int b1, int e1, int b2, int e2) {
    int index = b1;
    vector<T> temp;

    if (v.size()>1) {
        while (b1 <= e1 && b2 <= e2) {
            if (v[b1] > v[b2]) {
                temp.push_back(v[b2]);
                b2++;
            } else {
                temp.push_back(v[b1]);
                b1++;
            }
        }
        while (b1 <= e1) {
            temp.push_back(v[b1]);
            b1++;
        }
        while (b2 <= e2) {
            temp.push_back(v[b2]);
            b2++;
        }
    }
    for(auto e : temp) {
        v[index++] = e;
    }
}

template<typename T>
void dMergeSort(vector<T> &v, int low, int high) {
    if (low >= high) {
        return;
    } else {
        int m = low + (high-low)/2;
        dMergeSort(v,low,m);
        dMergeSort(v,m+1,high);
        dmerge(v,low,m,m+1,high);
    }
}

template<typename T>
void bubbleSort(vector<T>& v) {
    int n = v.size()-1;
    while (n > 0) {
        for (int i=0; i<n; ++i) {
            if (v[i] > v[i+1]) {
                swap(v[i],v[i+1]);
            }
        }
        n--;
    }
}

int main() {
    using collection = vector<int>;
    collection t(10000);

	auto display = [](const collection& t) {
	    for (auto e : t) cout << e << ", "; cout << endl;
	};

    generate(begin(t), end(t), [](){ return rand()%1000; } );
    {
        Timer timing("dMergeSort");
        dMergeSort(t, 0, t.size()-1);
    }
    //display(t);

    generate(begin(t), end(t), [](){ return rand()%1000; } );
    {
        Timer timing("bubbleSort");
        bubbleSort(t);
    }
    //display(t);

    return 0;
}
