#include<iostream>
using namespace std;
int main(){
	int w,num,count;
	w = 1;
	cout<<"enter the nums from the list: ";
	count = 0;
	while (w <= 5) {
		cin>>num;
		if (num == -7)
			count++;
		w++;
	}
	cout<<"there are "<<count<<" -7's"<<endl;
	return 0;
}
