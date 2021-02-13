#include<iostream>
using namespace std;
int main(){
	int w,num,sum;
	w = 1;
	sum = 0;
	cout<<"enter the nums from the list: ";
	while (w <= 5) {
		cin>>num;
		sum = sum + num;
		w++;
	}
	cout<<sum<<endl;
	return 0;
}
