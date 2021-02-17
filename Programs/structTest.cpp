#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct test {
    char c;
    int8_t i;
    double d;
    //char buffer[256];
} __attribute__ ((__packed__));


int main(){

    ofstream ofs("structMem", ofstream::out | ofstream::app);
    //string s = "aaaaaaaaaa";
    //char buffer[256];
    for(int i=0; i<5; ++i){
        //s += "a";
        test a;
        a.c = 'a'+i;
        a.i = i*-2;
        a.d = 2.0*i;
        //memcpy(a.buffer, s.c_str(), s.length());
        ofs.write((char*)&a, sizeof(a));
    }
    
    ofs.close();

    ifstream ifs("structMem", ifstream::in);
    test t;
    //ifs.read((char*)&t, sizeof(t));
    for (int i=0; i<5; ++i) {
        ifs.read((char*)&t, sizeof(t));
        cout << t.c << " " << t.i << " " << t.d << " " /* << t.buffer  */<< " size " << sizeof(t) << '\n';
    }
    ifs.close();

    // int n = 1;
    // // little endian if true
    // if (*(char *)&n == 1) {
    //     cout << "little" << '\n';
    // }

}