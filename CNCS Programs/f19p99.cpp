//p99
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int data[10] = {31,28,31,30,30,6,12,8,20,15};
	int total = 0;
	cout << "Element" << setw(13) << "Value" << endl;
	for (int j=0; j<10; j++) {
		total += data[j];
		cout << setw(7) << j << setw(13) << data[j] << endl;
	}
	cout << "The total is " << total << endl;
	return 0;
}
