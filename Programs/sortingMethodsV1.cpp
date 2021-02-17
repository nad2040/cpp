#include<iostream>
#include<vector>
#include<algorithm>
#include<random>

using namespace std;

int comparison = 0;

/*
bool checkList(const vector<int>& v) {
    int i=0;
    while (i<v.size()) {
        if (v[i] <= v[i+1]) {++i;} else {break;}
    }
    return i == v.size()-1;
}
*/

void displayVector(const vector<int>& v) {
    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;
}

void dmerge(vector<int>& v, int b1, int e1, int b2, int e2) {
    cout << "merging v " << b1 << " " << e1 << " " << b2 << " " << e2 << endl;
    displayVector(v);

    vector<int> temp;

    if (v.size()>1) {
        temp.insert(temp.end(),v.begin(),v.end());
        v.clear();
        while (b1 <= e1 && b2 <= e2) {
            if (temp[b1] > temp[b2]) {
                v.push_back(temp[b2]);
                b2++;
            } else {
                v.push_back(temp[b1]);
                b1++;
            }
        }
        while (b1 <= e1) {
            v.push_back(temp[b1]);
            b1++;
        }
        while (b2 <= e2) {
            v.push_back(temp[b2]);
            b2++;
        }
    }
    /*
    while (v.size() != temp.size()) {
        if (b1 == e1+1) {
            v.insert(v.end(),it+b2,it+e2+1);
        } else if (b2 == e2+1) {
            v.insert(v.end(),it+b1,it+e1+1);
        } else {
            if (v[b1] < v[b2]) {
                v.push_back(temp[b1]);
                b1++;
            } else if (v[b1] == v[b2]) {
                v.push_back(temp[b1]);
                v.push_back(temp[b2]);
                b1++;
                b2++;
            } else {
                v.push_back(temp[b2]);
                b2++;
            }
        }
    }
    */
}

void MergeSort(vector<int> &v, int low, int high) {
    cout << "sorting v from " << low << " to " << high << endl;
    displayVector(v);

    if (low >= high) {
        return;
    } else {
        int m = low + (high-low)/2;
        MergeSort(v,low,m);
        MergeSort(v,m+1,high);
        dmerge(v,low,m,m+1,high);
    }
}

void BubbleSort(vector<int>& v) {
    int n = v.size()-1;
    while (n > 0) {
        for (int j=0; j<n; ++j) {
            if (v[j] > v[j+1]) {
                swap(v[j],v[j+1]);
                comparison++;
            }
            //displayVector(v);
        }
        n--;
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
    vector<int> test = {1,3,8,10};
    //dmerge(test,0,6,7,12);
    displayVector(test);

    // cout << "++++++++++++\n";
    //vector<int> test = {1,3,2,3,7,5,8,5,2,9};

    
    MergeSort(test,0,test.size()-1);
    displayVector(test);

    // test = {1,6,7,2,6};
    // MergeSort(test,0,test.size()-1);

    return 0;
}