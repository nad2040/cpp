#include<iostream>
using namespace std;
int main(){
	int s;
	cout<<"enter a number 0-100: ";
	cin>>s;
	if (s>=90)
		cout<<"your grade is A\n";
	else if ((80<=s)&&(s<90))
			cout<<"your grade is B\n";
		else if ((70<=s)&&(s<80))
				cout<<"your grade is C\n";
			else if ((60<=s)&&(s<70))
					cout<<"your grade is D\n";
				else
					cout<<"your grade is F\n";
	return 0;
}
