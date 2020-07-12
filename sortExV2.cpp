#include<iostream>
#include<vector>
#include<algorithm>
#include<random>

using namespace std;

template<typename T>
void displayVector(const vector<T>& v) {
	ostream_iterator<T> out_it (std::cout,", ");
	copy(begin(v), end(v), out_it);
	cout << endl;
}

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

int main() {

    vector<unsigned long> t(1000);

    //generate(begin(t), end(t), rand);

    auto lambda = []() { return rand()%1000; };
    generate(begin(t), end(t), lambda);

    dMergeSort(t, 0, t.size()-1);
    displayVector(t);

	int x = 100;
	int y = 1000;
	auto filter = [x, y](int z) { return z>x&&z<y ? true : false; };

	cout << filter(50) << endl;
	cout << filter(500) << endl;
	cout << filter(5000) << endl;
    return 0;
}
