#include <iostream>
#include <cmath>
using namespace std;
const double PI = 3.14159265359;
struct IShape {
    virtual void Show() = 0;
    virtual double Perimeter() = 0;
    virtual void Save() = 0;
    virtual void Load() = 0;
    virtual ~IShape() {}
};

class Square : public IShape {
    double x, y, side;
public:
    Square() { Load(); }
    double Perimeter() override { return 4 * side; }
    void Show() override {
        cout << "Square: top-left(" << x << "," << y << "), side=" << side << "\nPerimeter=" << Perimeter() << endl;
    }
    void Save() override {
        cout << "Saving Square: " << x << " " << y << " " << side << endl;
    }
    void Load() override {
        x = 1; y = 2; side = (x + y) * 1.5;
    }
};

class Rectangle : public IShape {
    double x, y, w, h;
public:
    Rectangle() { Load(); }
    double Perimeter() override { return 2 * (w + h); }
    void Show() override {
        cout << "Rectangle: top-left(" << x << "," << y << "), w=" << w << " h=" << h << "\nPerimeter=" << Perimeter() << endl;
    }
    void Save() override {
        cout << "Saving Rectangle: " << x << " " << y << " " << w << " " << h << endl;
    }
    void Load() override {
        x = 1; y = 2; w = 4; h = 6;
    }
};

class Circle : public IShape {
    double x, y, r;
public:
    Circle() { Load(); }
    double Perimeter() override { return 2 * PI * r; }
    void Show() override {
        cout << "Circle: center(" << x << "," << y << "), r=" << r << "\nPerimeter=" << Perimeter() << endl;
    }
    void Save() override {
        cout << "Saving Circle: " << x << " " << y << " " << r << endl;
    }
    void Load() override {
        x = 5; y = 5; r = (x + y) / 4;
    }
};

class Ellipse : public IShape {
    double x, y, w, h;
public:
    Ellipse() { Load(); }
    double Perimeter() override {
        return PI * (3 * (w + h) - sqrt((3 * w + h) * (w + 3 * h)));
    }
    void Show() override {
        cout << "Ellipse: top-left(" << x << "," << y << "), w=" << w << " h=" << h << "\nApprox Perimeter=" << Perimeter() << endl;
    }
    void Save() override {
        cout << "Saving Ellipse: " << x << " " << y << " " << w << " " << h << endl;
    }
    void Load() override {
        x = 2; y = 3; w = 8; h = 4;
    }
};

int main() {
    IShape* shapes[4];
    shapes[0] = new Square();
    shapes[1] = new Rectangle();
    shapes[2] = new Circle();
    shapes[3] = new Ellipse();

    cout << "--- Initial shapes ---\n";
    for (int i = 0; i < 4; i++) shapes[i]->Show();

    cout << "\n--- Save shapes ---\n";
    for (int i = 0; i < 4; i++) shapes[i]->Save();

    cout << "\n--- Reload shapes (Load) ---\n";
    for (int i = 0; i < 4; i++) {
        shapes[i]->Load();
        shapes[i]->Show();
    }

    for (int i = 0; i < 4; i++) delete shapes[i];

    return 0;
}
