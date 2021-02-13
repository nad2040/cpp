#include <iostream>
#include <cmath>
#include <sstream>
#include <string>

using namespace std;

struct point {
    int x;
    int y;
    int z;
};

void setPoints(point &a, point &b) {
    cout << "Enter the coordinates of the first point (x,y,z): " << endl;
    cin >> a.x >> a.y >> a.z;
    cout << "Enter the coordinates of the second point (x,y,z): " << endl;
    cin >> b.x >> b.y >> b.z;
}

void distance(point &a, point &b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double dz = b.z - a.z;
    cout << "The distance is " << sqrt(dx*dx + dy*dy + dz*dz) << endl;
}

int main() {
    point a,b;
    setPoints(a, b);
    distance(a, b);
    return 0;
}
