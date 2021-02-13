#include <iostream>

using namespace std;

class Shape {
public:
    virtual string name() = 0;
    virtual double area() = 0;
    virtual double circumference() = 0;
};

class Rectangle : public Shape {
public:
    Rectangle(double width, double height) : width_(width), height_(height) {

    }

    virtual string name() override {
        return "Rectangle";
    }

    virtual double area() override {
        return width_ * height_;
    }

    virtual double circumference() override {
        return 2 * (width_ + height_);
    }

private:
    double width_;
    double height_;
};

class Circle : public Shape {
public:
    Circle(double radius) : radius_(radius) {

    }

    virtual string name() override {
        return "Circle";
    }

    virtual double area() override {
        return 3.14 * radius_ * radius_;
    }

    virtual double circumference() override {
        return 3.14 * 2 * radius_;
    }

private:
    double radius_;
};

int main() {
    Rectangle Rect1(3, 4);
    Rectangle Rect2(2, 3);
    Circle Circle1(1);
    Circle Circle2(3);
    cout << Rect1.area() << endl;
    cout << Rect1.circumference() << endl;
    cout << Rect2.area() << endl;
    cout << Rect2.circumference() << endl;
    cout << Circle1.area() << endl;
    cout << Circle1.circumference() << endl;
    cout << Circle2.area() << endl;
    cout << Circle2.circumference() << endl;

    Shape* shapes[4];
    shapes[0] = &Rect1;
    shapes[1] = &Circle1;
    shapes[2] = &Rect2;
    shapes[3] = &Circle2;

    for(int i=0; i<4; ++i) {
        cout << shapes[i]->name() << ": " << shapes[i]->area() << endl;
        cout << shapes[i]->name() << ": " << shapes[i]->circumference() << endl;
    }
}