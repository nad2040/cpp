#include <iostream>
using namespace std;
int main(){
	int w,sum;
	w = 1;
	sum = 0;
	while (w <= 21){
		if (w%5 == 0)
			sum = sum + w;
		w = w + 1;
	}
	cout<<"sum is "<<sum<<endl;
	return 0;
}
