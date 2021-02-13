#include <iostream>
using namespace std;
int main(){
	int i,sum;
	sum = 0;
	for (i = 4; i <= 16; i++) {
		if (i%2 != 0)
			sum += i;
	}
	cout<<"the sum is "<<sum<<endl;
}
