#include <iostream>
using namespace std;
int main(){
	int w,sum;
	w = 4;
	sum = 0;
	do {
		if (w%2 != 0)
			sum = sum + w;
		w = w + 1;
	} while (w<=16);
	cout<<"the sum is "<<sum<<endl;
	return 0;
}