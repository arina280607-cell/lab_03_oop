#include "fraction_set.h"
#include <utility>

FractionSet::FractionSet()
    : data_{nullptr}, size_{0}, capacity_{0} {
}


std::size_t FractionSet::size() const {
    return size_;
}

bool FractionSet::empty() const {
    return size_ == 0;
}

//правило 1/5 глубокое копирование(конструктор копирования)
FractionSet::FractionSet(const FractionSet& other)
    : data_{nullptr},
      size_{other.size_},
      capacity_{other.capacity_} {
    if (capacity_ != 0) {
        data_ = new Fraction[capacity_];

        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
}

//правило 2/5 оператор присваивания копированием + копи свап
FractionSet& FractionSet::operator=(const FractionSet& other) {
    if (this != &other) {
        FractionSet temporary{other};
        swap(temporary);
    }

    return *this;
}
//вспомогательная функция свап
void FractionSet::swap(FractionSet& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

//правило 3/5 конструктор перемещения
FractionSet::FractionSet(FractionSet&& other) noexcept
    : data_{other.data_},
      size_{other.size_},
      capacity_{other.capacity_} {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

//правило 4/5 оператор присваивания перемещением
FractionSet& FractionSet::operator=(FractionSet&& other) noexcept {
    if (this != &other) {
        delete[] data_;

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    return *this;
}

// правило 5/5 деструктор
FractionSet::~FractionSet() {
    delete[] data_;
}



bool FractionSet::contains(const Fraction& value) const {//поиск если жлемент уже существует
    for (std::size_t i = 0; i < size_; ++i) {
        if (data_[i] == value) {
            return true;
        }
    }

    return false;
}
void FractionSet::reserve(std::size_t new_capacity) {//выделение меса
    if (new_capacity <= capacity_) {
        return;
    }

    Fraction* new_data = new Fraction[new_capacity];

    for (std::size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }

    delete[] data_;

    data_ = new_data;
    capacity_ = new_capacity;
}
bool FractionSet::add(const Fraction& value) {//добавление
    if (contains(value)) {
        return false;
    }

    if (size_ == capacity_) {
        std::size_t new_capacity = 1;

        if (capacity_ != 0) {
            new_capacity = capacity_ * 2;
        }

        reserve(new_capacity);
    }

    data_[size_] = value;
    ++size_;

    return true;
}

//удаление дроби
bool FractionSet::remove(const Fraction& value) {
    for (std::size_t i = 0; i < size_; ++i) {
        if (data_[i] == value) {
            data_[i] = data_[size_ - 1];
            --size_;
            return true;
        }
    }

    return false;
}

//операторы (), +=, -=

bool FractionSet::operator()(const Fraction& value) const {
    return contains(value);
}

FractionSet& FractionSet::operator+=(const Fraction& value) {
    add(value);
    return *this;
}

FractionSet& FractionSet::operator-=(const Fraction& value) {
    remove(value);
    return *this;
}

//объединение
FractionSet FractionSet::operator|(const FractionSet& other) const {
    FractionSet result;

    for (std::size_t i = 0; i < size_; ++i) {
        result.add(data_[i]);
    }

    for (std::size_t i = 0; i < other.size_; ++i) {
        result.add(other.data_[i]);
    }

    return result;
}

//пересение
FractionSet FractionSet::operator&(const FractionSet& other) const {
    FractionSet result;

    for (std::size_t i = 0; i < size_; ++i) {
        if (other.contains(data_[i])) {
            result.add(data_[i]);
        }
    }

    return result;
}

//разность
FractionSet FractionSet::operator-(const FractionSet& other) const {
    FractionSet result;

    for (std::size_t i = 0; i < size_; ++i) {
        if (!other.contains(data_[i])) {
            result.add(data_[i]);
        }
    }

    return result;
}

bool FractionSet::operator==(const FractionSet& other) const {
    if (size_ != other.size_) {
        return false;
    }

    for (std::size_t i = 0; i < size_; ++i) {
        if (!other.contains(data_[i])) {
            return false;
        }
    }

    return true;
}

bool FractionSet::operator!=(const FractionSet& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const FractionSet& set) {
    out << '{';

    if (!set.empty()) {
        out << ' ';

        for (std::size_t i = 0; i < set.size_; ++i) {
            if (i != 0) {
                out << ", ";
            }

            out << set.data_[i];
        }

        out << ' ';
    }

    out << '}';
    return out;
}