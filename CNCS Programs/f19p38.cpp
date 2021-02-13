#include<iostream>
using namespace std;
int main(){
	int w,num;
	w = 1;
	cout<<"enter the nums from list: ";
	while (w <= 5) {
		cin>>num;
		if (num%2 != 0)
			if ((num>=5)&&(num<=14))
				cout<<num<<" ";
		w++;
	}
	return 0;
}
