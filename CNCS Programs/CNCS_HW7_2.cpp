#include <iostream>
#include <cmath>

using namespace std;

struct point {
    double x;
    double y;
};

void setPoints(point &a, point &b) {
    cout << "Enter the coordinates of the first point (x,y): " << endl;
    cin >> a.x >> a.y;
    cout << "Enter the coordinates of the second point (x,y): " << endl;
    cin >> b.x >> b.y;
}
void distance(point &a, point &b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    cout << "The distance is " << sqrt(dx*dx + dy*dy) << endl;
}
void slope(point &a, point &b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    cout << "The slope is " << dy/dx << endl;
}
void midpoint(point &a, point &b) {
    point m;
    m.x = (a.x + b.x)/2;
    m.y = (a.y + b.y)/2;
    cout << "The midpoint is (" << m.x << ", " << m.y << ")" << endl;
}

int main() {
    point a,b;
    setPoints(a, b);
    distance(a, b);
    slope(a, b);
    midpoint(a, b);

    return 0;
}