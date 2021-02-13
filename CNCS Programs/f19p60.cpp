#include<iostream>
using namespace std;
int main(){
	int i,num,count;
	cout<<"enter the nums from the list: ";
	count = 0;
	for (i=1; i<=5; i++) {
		cin>>num;
		if (num == -7)
			count++;
	}
	if (count != 0)
        cout<<"there are "<<count<<" -7's"<<endl;
	else
		cout<<"-7 doesn't exist\n";
	return 0;
}