#include <iostream>

using namespace std;

int main() {
    int i[5] = {1, 2, 3, 4, 5};
    double d[5] = {1.0, 2.0, 3.0, 4.0, 5.0};

    cout << i[0] << " " << &i[0] << endl;
    cout << i[1] << " " << &i[1] << endl;
    cout << i[2] << " " << &i[2] << endl;
    cout << i[3] << " " << &i[3] << endl;
    cout << i[4] << " " << &i[4] << endl;
    cout << d[0] << " " << &d[0] << endl;
    cout << d[1] << " " << &d[1] << endl;
    cout << d[2] << " " << &d[2] << endl;
    cout << d[3] << " " << &d[3] << endl;
    cout << d[4] << " " << &d[4] << endl;

    int *iPtr = &i[0];
    cout << *iPtr << " " << *(iPtr + 1) << " " << *(iPtr + 2) << " " << *(iPtr + 3) << " " << *(iPtr + 4) << endl;
    double *dPtr = &d[0];
    cout << *dPtr << " " << *(dPtr + 1) << " " << *(dPtr + 2) << " " << *(dPtr + 3) << " " << *(dPtr + 4) << endl;
}