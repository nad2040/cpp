#include <iostream>
using namespace std;

bool notEqual(int, int, int, int, int, int, int, int, int);
bool notEqual2(int, int, int, int, int, int, int, int, int);

int main() {
	int a1,a2,a3,a4,a5,a6,a7,a8,a9;
	for (a1 = 1; a1<=9; a1++)
		for (a2 = 1; a2<=9; a2++)
			for (a3 = 1; a3<=9; a3++)
				for (a4 = 1; a4<=9; a4++)
					for (a5 = 1; a5<=9; a5++)
						for (a6 = 1; a6<=9; a6++)
							for (a7 = 1; a7<=9; a7++)
								for (a8 = 1; a8<=9; a8++)
									for (a9 = 1; a9<=9; a9++)
										if (notEqual2(a1,a2,a3,a4,a5,a6,a7,a8,a9)==true)
											if ((a1+a2+a3==15)&&(a4+a5+a6==15)&&(a7+a8+a9==15)&&(a1+a4+a7==15)&&(a2+a5+a8==15)&&(a3+a6+a9==15)&&(a1+a5+a9==15)&&(a3+a5+a7==15))
												cout<<a1<<" "<<a2<<" "<<a3<<"\n"<<a4<<" "<<a5<<" "<<a6<<"\n"<<a7<<" "<<a8<<" "<<a9<<" done"<<endl;
	return 0;
}

bool notEqual(int a, int b, int c, int d, int e, int f, int g, int h, int i) {
	if ((a!=b)&&(a!=c)&&(a!=d)&&(a!=e)&&(a!=f)&&(a!=g)&&(a!=h)&&(a!=i)&&(b!=c)&&(b!=d)&&(b!=e)&&(b!=f)&&(b!=g)&&(b!=h)&&(b!=i)&&(c!=d)&&(c!=e)&&(c!=f)&&(c!=g)&&(c!=h)&&(c!=i)&&(d!=e)&&(d!=f)&&(d!=g)&&(d!=h)&&(d!=i)&&(e!=f)&&(e!=g)&&(e!=h)&&(e!=i)&&(f!=g)&&(f!=h)&&(f!=i)&&(g!=h)&&(g!=i)&&(h!=i))
		return true;
	else
		return false;
}

bool notEqual2(int a, int b, int c, int d, int e, int f, int g, int h, int i) {
	int product = 9*8*7*6*5*4*3*2*1;
	int sum = 1+2+3+4+5+6+7+8+9;
	if (a*b*c*d*e*f*g*h*i != product || a+b+c+d+e+f+g+h+i != sum)
		return false;
	else return true;
}