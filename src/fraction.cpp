#include "fraction.h"
#include <cassert>

void Fraction::normalize() {
    assert(denominator_ != 0);
    assert(numerator_ >= -2147483647);
    assert(denominator_ >= -2147483647);

int gcd(int a, int b) {//ищем нод чисел
    if (a < 0) {
        a = -a;
    }

    while (b != 0) {
        int remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

Fraction::Fraction(int numerator, int denominator)
    : numerator_{numerator}, denominator_{denominator} {
    normalize();
}

void Fraction::normalize() {
    assert(denominator_ != 0);

    if (denominator_ < 0) {
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }

    int divisor = gcd(numerator_, denominator_);

    numerator_ /= divisor;
    denominator_ /= divisor;
}

int Fraction::numerator() const {
    return numerator_;
}

int Fraction::denominator() const {
    return denominator_;
}

bool Fraction::operator==(const Fraction& other) const {
    return numerator_ == other.numerator_
        && denominator_ == other.denominator_;
}

std::ostream& operator<<(std::ostream& out, const Fraction& fraction) {
    out << fraction.numerator() << '/' << fraction.denominator();
    return out;
}
