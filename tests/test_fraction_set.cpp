#include "fraction_set.h"

#include <gtest/gtest.h>
#include <sstream>
#include <utility>

TEST(FractionTest, Normalization) {
    Fraction zero;
    EXPECT_EQ(zero.numerator(), 0);
    EXPECT_EQ(zero.denominator(), 1);

    Fraction value{6, -8};
    EXPECT_EQ(value.numerator(), -3);
    EXPECT_EQ(value.denominator(), 4);

    EXPECT_EQ((Fraction{-6, -8}), (Fraction{3, 4}));
    EXPECT_EQ((Fraction{0, -8}), Fraction{});
    EXPECT_EQ((Fraction{2, 4}), (Fraction{3, 6}));
    EXPECT_FALSE((Fraction{1, 2} == Fraction{3, 4}));
}

TEST(FractionTest, Output) {
    std::ostringstream out;
    out << Fraction{6, -8} << ' ' << Fraction{};

    EXPECT_EQ(out.str(), "-3/4 0/1");
}

TEST(FractionSetTest, EmptySet) {
    FractionSet set;

    EXPECT_EQ(set.size(), 0u);
    EXPECT_TRUE(set.empty());
    EXPECT_FALSE(set.contains(Fraction{1, 2}));
    EXPECT_FALSE(set(Fraction{1, 2}));
    EXPECT_FALSE(set.remove(Fraction{1, 2}));
}

TEST(FractionSetTest, AddRejectsDuplicates) {
    FractionSet set;

    EXPECT_TRUE(set.add(Fraction{1, 2}));
    EXPECT_FALSE(set.add(Fraction{2, 4}));
    EXPECT_FALSE(set.add(Fraction{-3, -6}));
    EXPECT_TRUE(set.add(Fraction{-1, 2}));

    EXPECT_EQ(set.size(), 2u);
    EXPECT_FALSE(set.empty());
}

TEST(FractionSetTest, RemoveAndReuse) {
    FractionSet set;
    set += Fraction{1, 2};
    set += Fraction{3, 4};
    set += Fraction{5, 6};

    EXPECT_FALSE(set.remove(Fraction{7, 8}));
    EXPECT_TRUE(set.remove(Fraction{2, 4}));
    EXPECT_FALSE(set(Fraction{1, 2}));
    EXPECT_EQ(set.size(), 2u);

    std::ostringstream out;
    out << set;
    EXPECT_EQ(out.str(), "{ 5/6, 3/4 }");

    EXPECT_TRUE(set.remove(Fraction{3, 4}));
    EXPECT_TRUE(set.remove(Fraction{5, 6}));
    EXPECT_TRUE(set.empty());
    EXPECT_FALSE(set.remove(Fraction{5, 6}));

    EXPECT_TRUE(set.add(Fraction{7, 8}));
    EXPECT_TRUE(set(Fraction{7, 8}));
    EXPECT_EQ(set.size(), 1u);
}

TEST(FractionSetTest, ContainsAndCallAgree) {
    FractionSet set;
    set += Fraction{1, 2};

    EXPECT_TRUE(set.contains(Fraction{3, 6}));
    EXPECT_TRUE(set(Fraction{3, 6}));

    EXPECT_FALSE(set.contains(Fraction{3, 4}));
    EXPECT_FALSE(set(Fraction{3, 4}));
}

TEST(FractionSetTest, CompoundOperators) {
    FractionSet set;

    EXPECT_EQ(&(set += Fraction{1, 2}), &set);
    (set += Fraction{3, 4}) += Fraction{5, 6};
    EXPECT_EQ(set.size(), 3u);

    EXPECT_EQ(&(set -= Fraction{3, 4}), &set);
    EXPECT_FALSE(set(Fraction{3, 4}));

    set -= Fraction{7, 8};
    EXPECT_EQ(set.size(), 2u);
}

TEST(FractionSetTest, CopyConstructor) {
    FractionSet original;
    original += Fraction{1, 2};
    original += Fraction{3, 4};

    FractionSet copy{original};
    EXPECT_EQ(copy, original);

    copy.remove(Fraction{1, 2});
    copy.add(Fraction{5, 6});

    EXPECT_TRUE(original(Fraction{1, 2}));
    EXPECT_FALSE(original(Fraction{5, 6}));
    EXPECT_TRUE(copy(Fraction{5, 6}));
    EXPECT_NE(copy, original);
}

TEST(FractionSetTest, CopyAssignment) {
    FractionSet original;
    original += Fraction{1, 2};

    FractionSet copy;
    copy += Fraction{7, 8};

    EXPECT_EQ(&(copy = original), &copy);
    EXPECT_EQ(copy, original);
    EXPECT_FALSE(copy(Fraction{7, 8}));

    copy.remove(Fraction{1, 2});

    EXPECT_TRUE(copy.empty());
    EXPECT_TRUE(original(Fraction{1, 2}));
}

TEST(FractionSetTest, SelfAssignment) {
    FractionSet set;
    set += Fraction{1, 2};

    FractionSet& alias = set;

    set = alias;
    EXPECT_EQ(set.size(), 1u);
    EXPECT_TRUE(set(Fraction{1, 2}));

    set = std::move(alias);
    EXPECT_EQ(set.size(), 1u);
    EXPECT_TRUE(set(Fraction{1, 2}));
}

TEST(FractionSetTest, MoveConstructor) {
    FractionSet source;
    source += Fraction{1, 2};
    source += Fraction{3, 4};

    FractionSet moved{std::move(source)};

    EXPECT_EQ(moved.size(), 2u);
    EXPECT_TRUE(moved(Fraction{1, 2}));
    EXPECT_TRUE(moved(Fraction{3, 4}));

    EXPECT_TRUE(source.empty());
    EXPECT_EQ(source.size(), 0u);

    EXPECT_TRUE(source.add(Fraction{5, 6}));
    EXPECT_FALSE(moved(Fraction{5, 6}));
}

TEST(FractionSetTest, MoveAssignment) {
    FractionSet source;
    source += Fraction{1, 2};

    FractionSet target;
    target += Fraction{7, 8};

    EXPECT_EQ(&(target = std::move(source)), &target);

    EXPECT_EQ(target.size(), 1u);
    EXPECT_TRUE(target(Fraction{1, 2}));
    EXPECT_FALSE(target(Fraction{7, 8}));

    EXPECT_TRUE(source.empty());
    EXPECT_EQ(source.size(), 0u);

    EXPECT_TRUE(source.add(Fraction{3, 4}));
    EXPECT_FALSE(target(Fraction{3, 4}));
}

TEST(FractionSetTest, EmptyCopiesAndMoves) {
    FractionSet empty;
    FractionSet copied{empty};
    FractionSet moved{std::move(empty)};

    EXPECT_TRUE(empty.empty());
    EXPECT_TRUE(copied.empty());
    EXPECT_TRUE(moved.empty());

    FractionSet target;
    target += Fraction{1, 2};
    target = copied;
    EXPECT_TRUE(target.empty());

    target += Fraction{3, 4};
    target = std::move(moved);
    EXPECT_TRUE(target.empty());
    EXPECT_TRUE(moved.empty());

    EXPECT_TRUE(target.add(Fraction{5, 6}));
}

TEST(FractionSetTest, SetOperations) {
    FractionSet left;
    left += Fraction{1, 2};
    left += Fraction{3, 4};

    FractionSet right;
    right += Fraction{6, 8};
    right += Fraction{5, 6};

    FractionSet left_before{left};
    FractionSet right_before{right};

    FractionSet expected_union{left};
    expected_union += Fraction{5, 6};

    FractionSet expected_intersection;
    expected_intersection += Fraction{3, 4};

    FractionSet expected_difference;
    expected_difference += Fraction{1, 2};

    EXPECT_EQ(left | right, expected_union);
    EXPECT_EQ(left & right, expected_intersection);
    EXPECT_EQ(left - right, expected_difference);

    EXPECT_EQ(right | left, expected_union);
    EXPECT_EQ(right & left, expected_intersection);
    EXPECT_NE(right - left, expected_difference);

    EXPECT_EQ(left, left_before);
    EXPECT_EQ(right, right_before);
}

TEST(FractionSetTest, OperationsWithEmptyAndSelf) {
    FractionSet empty;

    FractionSet set;
    set += Fraction{1, 2};

    EXPECT_EQ(set | empty, set);
    EXPECT_EQ(empty | set, set);

    EXPECT_TRUE((set & empty).empty());
    EXPECT_TRUE((empty & set).empty());

    EXPECT_EQ(set - empty, set);
    EXPECT_TRUE((empty - set).empty());

    EXPECT_EQ(set | set, set);
    EXPECT_EQ(set & set, set);
    EXPECT_TRUE((set - set).empty());
    EXPECT_TRUE((empty | empty).empty());
}

TEST(FractionSetTest, EqualityIgnoresOrder) {
    FractionSet left;
    left += Fraction{1, 2};
    left += Fraction{3, 4};

    FractionSet right;
    right += Fraction{3, 4};
    right += Fraction{2, 4};

    EXPECT_TRUE(left == right);
    EXPECT_FALSE(left != right);

    right -= Fraction{1, 2};
    right += Fraction{5, 6};

    EXPECT_FALSE(left == right);
    EXPECT_TRUE(left != right);

    right -= Fraction{5, 6};
    EXPECT_NE(left, right);
    EXPECT_EQ(FractionSet{}, FractionSet{});
}

TEST(FractionSetTest, OutputFormat) {
    FractionSet set;

    std::ostringstream empty_out;
    empty_out << set;
    EXPECT_EQ(empty_out.str(), "{}");

    set += Fraction{6, 8};
    set += Fraction{2, 4};

    std::ostringstream out;
    out << set << '!';

    EXPECT_EQ(out.str(), "{ 3/4, 1/2 }!");
}

TEST(FractionSetTest, ThousandElements) {
    FractionSet set;

    for (int i = 0; i < 1000; ++i) {
        ASSERT_TRUE(set.add(Fraction{i, 1}));
    }

    EXPECT_EQ(set.size(), 1000u);

    for (int i = 0; i < 1000; ++i) {
        EXPECT_TRUE(set.contains(Fraction{i, 1}));
        EXPECT_FALSE(set.add(Fraction{2 * i, 2}));
    }

    EXPECT_EQ(set.size(), 1000u);

    FractionSet copy{set};
    EXPECT_EQ(copy, set);

    for (int i = 0; i < 1000; ++i) {
        ASSERT_TRUE(copy.remove(Fraction{i, 1}));
    }

    EXPECT_TRUE(copy.empty());
    EXPECT_EQ(set.size(), 1000u);
    EXPECT_TRUE(copy.add(Fraction{1, 2}));
}