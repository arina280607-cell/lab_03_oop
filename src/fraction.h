#ifndef LAB03_FRACTION_H
#define LAB03_FRACTION_H
#include <iostream>

class Fraction {
public:
    explicit Fraction(int numerator = 0, int denominator = 1);

    int numerator() const;
    int denominator() const;
    bool operator==(const Fraction& other) const;

    

private:
    int numerator_;
    int denominator_;

    void normalize();
};

std::ostream& operator<<(std::ostream& out, const Fraction& fraction);

#endif