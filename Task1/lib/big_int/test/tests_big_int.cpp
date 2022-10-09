#include <iostream>
#include <climits>
#include <sstream>
#include <utility>
#include "gtest/gtest.h"
#include "big_int.h"

struct IntArgs
{
    int arg1_;
    int arg2_;
    int arg3_;
    std::string exception_;

    IntArgs(int arg1, int arg2)
        : arg1_(arg1), arg2_(arg2), arg3_(0) {}
    IntArgs(int arg1, int arg2, std::string exception)
        : arg1_(arg1), arg2_(arg2), arg3_(0), exception_(std::move(exception)) {}
    IntArgs(int arg1, int arg2, int arg3)
        : arg1_(arg1), arg2_(arg2), arg3_(arg3) {}
};

struct StringArgs
{
    std::string arg1_;
    std::string arg2_;

    StringArgs(std::string arg1, std::string arg2)
            : arg1_(std::move(arg1)), arg2_(std::move(arg2)) {}
};

TEST(test_constructors, constructor_wthout_args)
{
    EXPECT_EQ((int)BigInt(), 0);
}

class IntConstructorTest : public ::testing::TestWithParam<IntArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_constructors,
    IntConstructorTest,
    ::testing::Values
    (
        IntArgs(10, 10),
        IntArgs(INT_MAX, INT_MAX),
        IntArgs(-34, -34),
        IntArgs(INT_MIN, INT_MIN)
    )
);

TEST_P(IntConstructorTest, int_constructor)
{
    IntArgs params = GetParam();
    EXPECT_EQ((int) BigInt(params.arg1_), params.arg2_);
}

class StringConstructorTest : public ::testing::TestWithParam<StringArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_constructors,
    StringConstructorTest,
    ::testing::Values
    (
        StringArgs("-64228", "-64228"),
        StringArgs("4294967296", "4294967296"),  // 100000000 000000000 000000000 000000000
        StringArgs("", "0"),                     // empty string
        StringArgs("000000000654", "654"),       // many begin zeros
        StringArgs("000000000", "0"),            // many zeros
        StringArgs("-00045", "-45"),             // minus and many begin zeros
        StringArgs("-000000000", "0"),           // minus and many zeros
        StringArgs("-", "Wrong number"),
        StringArgs("98dccS6E55", "Wrong number")
    )
);

TEST_P(StringConstructorTest, string_constructor)
{
    StringArgs params = GetParam();
    try
    {
        BigInt result = BigInt(params.arg1_);
        EXPECT_EQ(std::string(result), params.arg2_);
    }
    catch (const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(), params.arg2_.data());
    }
}

TEST(test_constructors, copy_constructor)
{
    BigInt src(-65412);
    BigInt dest(src);

    EXPECT_EQ(int(src), int(dest));
    EXPECT_NE(&src, &dest);
}

TEST(test_constructors, move_constructor)
{
    BigInt tmp(3146);
    BigInt src(std::move(tmp));

    EXPECT_EQ((int)src, 3146);
    EXPECT_EQ((int)tmp, 0);
    EXPECT_EQ((std::string)tmp, std::string("0"));
}

TEST(test_assignment_operators, assignment)
{
    BigInt src(-654087);
    BigInt dest = src;

    EXPECT_EQ(int(src), -654087);
    EXPECT_EQ(int(dest), -654087);

    // self-assigment
    src = src;
    EXPECT_EQ(int(src), -654087);
}

TEST(test_assignment_operators, move_assignment)
{
    BigInt tmp(3146);
    BigInt src = std::move(tmp);

    EXPECT_EQ((int)src, 3146);
    EXPECT_EQ((int)tmp, 0);
    EXPECT_EQ((std::string)tmp, std::string("0"));
}

class ArithmeticOperatorTest : public ::testing::TestWithParam<IntArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_arithmetic_operators,
    ArithmeticOperatorTest,
    ::testing::Values
    (
        IntArgs(0, 0, "Division by zero"),     // adding zero
        IntArgs(0, 534),
        IntArgs(0, -534),
        IntArgs(534, 0, "Division by zero"),
        IntArgs(-534, 0, "Division by zero"),
        IntArgs(62, 534),                           // identical signs
        IntArgs(-62, -534),
        IntArgs(534, 62),
        IntArgs(-534, -62),
        IntArgs(-62, 534),                          // different signs
        IntArgs(62, -534),
        IntArgs(534, -62),
        IntArgs(-534, 62)
    )
);

TEST_P(ArithmeticOperatorTest, addition_operator)
{
    IntArgs params = GetParam();
    EXPECT_EQ((int)(BigInt(params.arg1_) + BigInt(params.arg2_)), params.arg1_ + params.arg2_);
}

TEST_P(ArithmeticOperatorTest, addition_assignment_operator)
{
    IntArgs params = GetParam();
    BigInt result(params.arg1_);
    result += BigInt(params.arg2_);
    EXPECT_EQ((int)(result), params.arg1_ + params.arg2_);
}

TEST_P(ArithmeticOperatorTest, subtraction_operator)
{
    IntArgs params = GetParam();
    EXPECT_EQ((int)(BigInt(params.arg1_) - BigInt(params.arg2_)), params.arg1_ - params.arg2_);
}

TEST_P(ArithmeticOperatorTest, subtraction_assignment_operator)
{
    IntArgs params = GetParam();
    BigInt result(params.arg1_);
    result -= BigInt(params.arg2_);
    EXPECT_EQ((int)(result), params.arg1_ - params.arg2_);
}

TEST_P(ArithmeticOperatorTest, multiplication_operator)
{
    IntArgs params = GetParam();
    EXPECT_EQ((int)(BigInt(params.arg1_) * BigInt(params.arg2_)), params.arg1_ * params.arg2_);
}

TEST_P(ArithmeticOperatorTest, multiplication_assignment_operator)
{
    IntArgs params = GetParam();
    BigInt result(params.arg1_);
    result *= BigInt(params.arg2_);
    EXPECT_EQ((int)(result), params.arg1_ * params.arg2_);
}

TEST_P(ArithmeticOperatorTest, division_operator)
{
    IntArgs params = GetParam();
    try
    {
        BigInt result = BigInt(params.arg1_) / BigInt(params.arg2_);
        EXPECT_EQ((int)(result), params.arg1_ / params.arg2_);
    }
    catch (const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(), params.exception_.data());
    }
}

TEST_P(ArithmeticOperatorTest, division_assignment_operator)
{
    IntArgs params = GetParam();
    try
    {
        BigInt result(params.arg1_);
        result /=  BigInt(params.arg2_);
        EXPECT_EQ((int)(result), params.arg1_ / params.arg2_);
    }
    catch (const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(), params.exception_.data());
    }
}

TEST_P(ArithmeticOperatorTest, modulo_operator)
{
    IntArgs params = GetParam();
    try
    {
        BigInt result = BigInt(params.arg1_) % BigInt(params.arg2_);
        EXPECT_EQ((int)(result), params.arg1_ % params.arg2_);
    }
    catch (const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(), params.exception_.data());
    }
}

TEST_P(ArithmeticOperatorTest, modulo_assignment_operator)
{
    IntArgs params = GetParam();
    try
    {
        BigInt result(params.arg1_);
        result %=  BigInt(params.arg2_);
        EXPECT_EQ((int)(result), params.arg1_ % params.arg2_);
    }
    catch (const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(), params.exception_.data());
    }
}

TEST(test_arithmetic_operators, unary_plus)
{
    BigInt src(65408);
    EXPECT_EQ(int(src), 65408);
}

TEST(test_arithmetic_operators, unary_minus)
{
    BigInt src(65408);
    EXPECT_EQ(int(-src), -65408);

    src = BigInt(-65408);
    EXPECT_EQ(int(-src), 65408);
}

TEST(test_arithmetic_operators, prefix_increment)
{
    BigInt src(654);
    EXPECT_EQ(int(++src), 655);
    EXPECT_EQ(int(src), 655);
}

TEST(test_arithmetic_operators, postfix_increment)
{
    BigInt src(654);
    EXPECT_EQ(int(src++), 654);
    EXPECT_EQ(int(src), 655);
}

TEST(test_arithmetic_operators, prefix_decrement)
{
    BigInt src(654);
    EXPECT_EQ(int(--src), 653);
    EXPECT_EQ(int(src), 653);
}

TEST(test_arithmetic_operators, postfix_decrement)
{
    BigInt src(654);
    EXPECT_EQ(int(src--), 654);
    EXPECT_EQ(int(src), 653);
}

class OrOperatorTest : public ::testing::TestWithParam<IntArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_bitwise_operators,
    OrOperatorTest,
    ::testing::Values
    (
        // identical size
        // 0 01010111
        // 0 10101010
        // 0 11111111
        IntArgs(87, 170, 255),

        // different size
        // 0 01010101 01010111
        // 0          10101010
        // 0 01010101 11111111
        IntArgs(21847, 170, 22015),

        // negative numbers
        // 1 01010101 01010111
        // 1          10101010
        // 1 01010101 11111111
        IntArgs(-21847, -170, -22015),

        // different sign
        // 0 01010101 01010111
        // 1          10101010
        // 1 01010101 11111111
        IntArgs(21847, -170, -22015)
    )
);

TEST_P(OrOperatorTest, or)
{
    IntArgs params = GetParam();
    EXPECT_EQ((int)(BigInt(params.arg1_) | BigInt(params.arg2_)), params.arg3_);
}

TEST_P(OrOperatorTest, or_assignment)
{
    IntArgs params = GetParam();
    BigInt result = BigInt(params.arg1_);
    result |= BigInt(params.arg2_);
    EXPECT_EQ((int)result, params.arg3_);
}

class AndOperatorTest : public ::testing::TestWithParam<IntArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_bitwise_operators,
    AndOperatorTest,
    ::testing::Values
    (
        // identical size
        // 0 01010111
        // 0 10101010
        // 0 00000010
        IntArgs(87, 170, 2),

        // different size
        // 0 01010101 01010111
        // 0          10101010
        // 0          00000010
        IntArgs(21847, 170, 2),

        // negative numbers
        // 1 01010101 01010111
        // 1          10101010
        // 1          00000010
        IntArgs(-21847, -170, -2),

        // different sign
        // 0 01010101 01010111
        // 1          10101010
        // 0          00000010
        IntArgs(21847, -170, 2)
    )
);

TEST_P(AndOperatorTest, and)
{
    IntArgs params = GetParam();
    EXPECT_EQ((int)(BigInt(params.arg1_) & BigInt(params.arg2_)), params.arg3_);
}

TEST_P(AndOperatorTest, and_assignment)
{
    IntArgs params = GetParam();
    BigInt result = BigInt(params.arg1_);
    result &= BigInt(params.arg2_);
    EXPECT_EQ((int)result, params.arg3_);
}

class XorOperatorTest : public ::testing::TestWithParam<IntArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_bitwise_operators,
    XorOperatorTest,
    ::testing::Values
    (
        // identical size
        // 0 01010111
        // 0 10101010
        // 0 11111101
        IntArgs(87, 170, 253),

        // different size
        // 0 01010101 01010111
        // 0          10101010
        // 0 01010101 11111101
        IntArgs(21847, 170, 22013),

        // different arg size and return size
        // 0 01010101 01010111
        // 0 01010101 10101010
        // 0          11111101
        IntArgs(21847, 21930, 253),

        // negative numbers
        // 1 01010101 01010111
        // 1          10101010
        // 0 01010101 11111101
        IntArgs(-21847, -170, 22013),

        // different sign
        // 0 01010101 01010111
        // 1          10101010
        // 1 01010101 11111101
        IntArgs(21847, -170, -22013)
    )
);

TEST_P(XorOperatorTest, xor)
{
    IntArgs params = GetParam();
    EXPECT_EQ((int)(BigInt(params.arg1_) ^ BigInt(params.arg2_)), params.arg3_);
}

TEST_P(XorOperatorTest, xor_assignment)
{
    IntArgs params = GetParam();
    BigInt result = BigInt(params.arg1_);
    result ^= BigInt(params.arg2_);
    EXPECT_EQ((int)result, params.arg3_);
}

class NotOperatorTest : public ::testing::TestWithParam<IntArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_bitwise_operators,
    NotOperatorTest,
    ::testing::Values
    (
        // size is saved
        // 0 00000010 10001110
        // 1 11111101 01110001
        IntArgs(654, -64881),

        // size is not saved
        // 0 11111111 01110001
        // 1 00000000 10001110
        IntArgs(65393, -142)
    )
);

TEST_P(NotOperatorTest, not)
{
    IntArgs params = GetParam();
    BigInt result = BigInt(params.arg1_);
    EXPECT_EQ((int)(~result), params.arg2_);
}

class ComparisonOperatorTest : public ::testing::TestWithParam<IntArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_comparison_operators,
    ComparisonOperatorTest,
    ::testing::Values
        (
            IntArgs(6511, 6511),
            IntArgs(-6511, 6511),
            IntArgs(6511, -6511),
            IntArgs(-6511, -6511),
            IntArgs(6511, 2716),
            IntArgs(6511, -2716),
            IntArgs(-6511, 2716),
            IntArgs(-6511, -2716)
        )
);

TEST_P(ComparisonOperatorTest, equal)
{
    IntArgs params = GetParam();
    EXPECT_EQ(BigInt(params.arg1_) == BigInt(params.arg2_), params.arg1_ == params.arg2_);
}

TEST_P(ComparisonOperatorTest, not_equal)
{
    IntArgs params = GetParam();
    EXPECT_EQ(BigInt(params.arg1_) != BigInt(params.arg2_), params.arg1_ != params.arg2_);
}

TEST_P(ComparisonOperatorTest, greater)
{
    IntArgs params = GetParam();
    EXPECT_EQ(BigInt(params.arg1_) > BigInt(params.arg2_), params.arg1_ > params.arg2_);
}

TEST_P(ComparisonOperatorTest, less)
{
    IntArgs params = GetParam();
    EXPECT_EQ(BigInt(params.arg1_) < BigInt(params.arg2_), params.arg1_ < params.arg2_);
}

TEST_P(ComparisonOperatorTest, greater_or_equal)
{
    IntArgs params = GetParam();
    EXPECT_EQ(BigInt(params.arg1_) >= BigInt(params.arg2_), params.arg1_ >= params.arg2_);
}

TEST_P(ComparisonOperatorTest, less_or_equal)
{
    IntArgs params = GetParam();
    EXPECT_EQ(BigInt(params.arg1_) <= BigInt(params.arg2_), params.arg1_ <= params.arg2_);
}

TEST(test_type_conversion_operators, int_conversion)
{
    try
    {
        BigInt num = BigInt("165165161654");
    }
    catch(const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(), "Int overflow");
    }
}

TEST(test_input_output_operators, input)
{
    std::stringstream in;
    in << "-18906937482";

    BigInt num;
    in >> num;
    EXPECT_STREQ(std::string(num).data(), "-18906937482");
}

TEST(test_input_output_operators, output)
{
    std::ostringstream out;
    out << BigInt("-18906937482");
    EXPECT_STREQ(out.str().data(), "-18906937482");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}