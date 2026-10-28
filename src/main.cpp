#include "fraction.h"
#include "fraction_set.h"
#include <iostream>
#include <utility>
#include <utility>

int main()
{
    Fraction a{2, 4};
    Fraction b{3, 6};
    Fraction c{-3, 4};

    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';
    std::cout << "c = " << c << '\n';

    std::cout << std::boolalpha;
    std::cout << "a == b: " << (a == b) << '\n';
    std::cout << "a == c: " << (a == c) << '\n';

    FractionSet set;

    std::cout << "Set size: " << set.size() << '\n';
    std::cout << "Set is empty: " << set.empty() << '\n';
    FractionSet copy{set};

    std::cout << "Copy size: " << copy.size() << '\n';
    std::cout << "Copy is empty: " << copy.empty() << '\n';
    FractionSet assigned;
    assigned = set;

    std::cout << "Assigned size: " << assigned.size() << '\n';
    std::cout << "Assigned is empty: " << assigned.empty() << '\n';

    assigned = assigned;

    std::cout << "After self-assignment: " << assigned.size() << '\n';
    FractionSet moved{std::move(copy)};

    std::cout << "Moved size: " << moved.size() << '\n';
    std::cout << "Source is empty: " << copy.empty() << '\n';
    assigned = std::move(moved);

    std::cout << "After move assignment: " << assigned.size() << '\n';
    std::cout << "Moved source is empty: " << moved.empty() << '\n';

    assigned = std::move(assigned);

    std::cout << "After self-move: " << assigned.size() << '\n';
    FractionSet example;

    std::cout << "Add 2/4: "
              << example.add(Fraction{2, 4}) << '\n';

    std::cout << "Add 3/6: "
              << example.add(Fraction{3, 6}) << '\n';

    std::cout << "Add 3/4: "
              << example.add(Fraction{3, 4}) << '\n';

    std::cout << "Size: " << example.size() << '\n';

    std::cout << "Contains 1/2: "
              << example.contains(Fraction{1, 2}) << '\n';

    std::cout << "Contains 5/6: "
              << example.contains(Fraction{5, 6}) << '\n';
    example.add(Fraction{5, 6});

    std::cout << "Remove 1/2: "
              << example.remove(Fraction{1, 2}) << '\n';

    std::cout << "Contains 1/2 after removal: "
              << example.contains(Fraction{1, 2}) << '\n';

    std::cout << "Size after removal: "
              << example.size() << '\n';

    std::cout << "Remove 1/2 again: "
              << example.remove(Fraction{1, 2}) << '\n';
    FractionSet short_operations;

    short_operations += Fraction{1, 2};
    short_operations += Fraction{2, 4};

    std::cout << "After += size: "
              << short_operations.size() << '\n';

    std::cout << "Contains through (): "
              << short_operations(Fraction{3, 6}) << '\n';

    short_operations -= Fraction{1, 2};

    std::cout << "After -= empty: "
              << short_operations.empty() << '\n';
    FractionSet left;
    left += Fraction{1, 2};
    left += Fraction{3, 4};

    FractionSet right;
    right += Fraction{3, 4};
    right += Fraction{5, 6};

    FractionSet united = left | right;
    FractionSet common = left & right;
    FractionSet difference = left - right;

    std::cout << "Union size: " << united.size() << '\n';

    std::cout << "Intersection size: " << common.size() << '\n';
    std::cout << "Intersection contains 3/4: "
              << common(Fraction{3, 4}) << '\n';

    std::cout << "Difference size: " << difference.size() << '\n';
    std::cout << "Difference contains 1/2: "
              << difference(Fraction{1, 2}) << '\n';
    std::cout << "Left: " << left << '\n';
    std::cout << "Right: " << right << '\n';
    std::cout << "Union: " << united << '\n';
    std::cout << "Intersection: " << common << '\n';
    std::cout << "Difference: " << difference << '\n';

    FractionSet reordered;
    reordered += Fraction{3, 4};
    reordered += Fraction{1, 2};

    std::cout << "Equal despite order: " << (left == reordered) << '\n';
    std::cout << "Left differs from right: " << (left != right) << '\n';
    return 0;
}