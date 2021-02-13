#include <iostream>
using namespace std;
int main(){
	int s;
	cout<<"Input a score 0-100: ";
	cin>>s;
	if ((s<70) && (s>=60))
		cout<<"Grade: D";
	else if ((s<80) && (s>=70))
		cout<<"Grade: C";
	else if ((s<90) && (s>=80))
		cout<<"Grade: B";
	else if ((s<=100) && (s>=90))
		cout<<"Grade: A";
	else
		cout<<"Grade: F";
}
