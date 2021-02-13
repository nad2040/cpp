#include <iostream>
using namespace std;
int main(){
	int i,sum;
	sum = 0;
	for (i=1; i<=21; i++) {
		if (i%5 == 0)
			sum += i;
	}
	cout<<"sum is "<<sum<<endl;
	return 0;
}
