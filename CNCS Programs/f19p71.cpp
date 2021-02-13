#include<iostream>
using namespace std;
int main(){
	int w,num,sum;
	w = 1;
	sum = 0;
	cout<<"enter the nums from the list: ";
	do {
		cin>>num;
		sum = sum + num;
		w++;
	} while (w <= 5);
	cout<<sum<<endl;
	return 0;
}