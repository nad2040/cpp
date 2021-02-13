//p98
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int data[10] = {31,28,31,30,30,6,12,8,20,15};
	cout << "Element" << setw(13) << "Value" << endl;
	for (int i=0; i<10; i++)
		cout << setw(7) << i << setw(13) << data[i] << endl;
	return 0;
}
