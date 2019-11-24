#include<iostream>
using namespace std;
int main(){
	int s;
	cout << "Enter a score 0-100: ";
	cin >> s;
	char grade = ' ';
	switch(s)
	{
		case 0 ... 59:
			grade = 'F';
			break;
		case 60 ... 69:
			grade = 'D';
			break;
		case 70 ... 79:
			grade = 'C';
			break;
		case 80 ... 89:
			grade = 'B';
			break;
		case 90 ... 100:
			grade = 'A';
			break;
	}
	if (grade == ' ') 
		cout << "invalid input: " << s << '\n';
	else
		cout << "grade is: " << grade << '\n';
	return 0;
}