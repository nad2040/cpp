//p100
#include <iostream>

using namespace std;

int main() {
	int A[5][3] = {{5,2,6},{-9,-91,0},{0,0,38},{15,7,-8},{64,-1,37}};
	for (int i=0; i<5; i++) {
		for (int j=0; j<3; j++)
			cout << A[i][j] << "\t";
	cout << "\n";
	}
	return 0;	
}
