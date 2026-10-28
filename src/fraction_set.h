#ifndef LAB03_FRACTION_SET_H
#define LAB03_FRACTION_SET_H

#include "fraction.h"
#include <iostream>
#include <cstddef>

class FractionSet
{
public:
    FractionSet();

    FractionSet(const FractionSet &other);
    FractionSet(FractionSet &&other) noexcept;

    FractionSet &operator=(const FractionSet &other);
    FractionSet &operator=(FractionSet &&other) noexcept;

    ~FractionSet();

    std::size_t size() const;
    bool empty() const;
    bool contains(const Fraction &value) const;
    bool add(const Fraction &value);
    bool remove(const Fraction &value);
    bool operator()(const Fraction &value) const;

    FractionSet &operator+=(const Fraction &value);
    FractionSet &operator-=(const Fraction &value);

    FractionSet operator|(const FractionSet &other) const;
    FractionSet operator&(const FractionSet &other) const;
    FractionSet operator-(const FractionSet &other) const;

    bool operator==(const FractionSet& other) const;
    bool operator!=(const FractionSet& other) const;
    friend std::ostream& operator<<(std::ostream& out,
                                const FractionSet& set);

    private:
    Fraction *data_;
    std::size_t size_;
    std::size_t capacity_;

    void swap(FractionSet &other) noexcept;
    void reserve(std::size_t new_capacity);
};

#endif