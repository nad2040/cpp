#include<iostream>
#include<vector>
#include<algorithm>
#include<random>

using namespace std;

template<typename T>
void displayVector(const vector<T>& v) {
    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;
}

template<typename T>
void dmerge(vector<T>& v, int b1, int e1, int b2, int e2) {
    // cout << "merging v " << b1 << " " << e1 << " " << b2 << " " << e2 << endl;
    // displayVector(v);

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
void MergeSort(vector<T> &v, int low, int high) {
    // cout << "sorting v from " << low << " to " << high << endl;
    // displayVector(v);

    if (low >= high) {
        return;
    } else {
        int m = low + (high-low)/2;
        MergeSort(v,low,m);
        MergeSort(v,m+1,high);
        dmerge(v,low,m,m+1,high);
    }
}

int main() {
    vector<int> myList = {10,9,8,7,6,5,4,3,2,1};
    // displayVector(myList);
    // BubbleSort(myList);
    // displayVector(myList);
    // cout << comparison << " comparisons\n";

    // cout << "++++++++++++\n";
    // test = {1,2,30,5,7,8,9,10};
    // dmerge(test,0,2,3,7);

    // cout << "++++++++++++\n";
    vector<int> test = {1,0,4,3};
    //dmerge(test,0,6,7,12);
    displayVector(test);

    // cout << "++++++++++++\n";
    //vector<int> test = {1,3,2,3,7,5,8,5,2,9};

    vector<double> t(1000);
    
    generate(begin(t), end(t), [](){ return rand()%1000/3.14; } );

    MergeSort(t,0,t.size()-1);
    displayVector(t);

    // test = {1,6,7,2,6};
    // MergeSort(test,0,test.size()-1);

    
    // displayVector(t);


    return 0;
}
