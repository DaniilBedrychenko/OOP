#include <iostream>
using namespace std;

class Fraction {
private:
    int numerator;
    int denominator;

    void reduce() {
        int a = numerator, b = denominator;
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        numerator /= a;
        denominator /= a;
        if (denominator < 0) {
            denominator = -denominator;
            numerator = -numerator;
        }
    }

public:
    Fraction(int n = 0, int d = 1) : numerator(n), denominator(d) {
        if (d == 0) throw invalid_argument("Denominator cannot be zero");
        reduce();
    }

    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

    Fraction operator+(const Fraction& other) const {
        return Fraction(numerator * other.denominator + other.numerator * denominator,
                        denominator * other.denominator);
    }

    Fraction operator-(const Fraction& other) const {
        return Fraction(numerator * other.denominator - other.numerator * denominator,
                        denominator * other.denominator);
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) throw invalid_argument("Division by zero");
        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }

    Fraction operator+(int value) const {
        return Fraction(numerator + value * denominator, denominator);
    }

    Fraction operator-(int value) const {
        return Fraction(numerator - value * denominator, denominator);
    }

    Fraction operator*(int value) const {
        return Fraction(numerator * value, denominator);
    }

    Fraction operator/(int value) const {
        if (value == 0) throw invalid_argument("Division by zero");
        return Fraction(numerator, denominator * value);
    }

    friend ostream& operator<<(ostream& os, const Fraction& f) {
        os << f.numerator;
        if (f.denominator != 1) os << "/" << f.denominator;
        return os;
    }
};

int main() {
    Fraction a(3, 4);
    Fraction b(2, 5);

    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "a / b = " << a / b << endl;

    cout << "a + 2 = " << a + 2 << endl;
    cout << "a - 1 = " << a - 1 << endl;
    cout << "a * 3 = " << a * 3 << endl;
    cout << "a / 2 = " << a / 2 << endl;

    return 0;
}
