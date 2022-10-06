#include <iostream>
#include "gtest/gtest.h"
#include "string_arithmetic.h"

struct StringArgs
{
    std::string arg1_;
    std::string arg2_;
    std::string arg3_;

    StringArgs(std::string arg1, std::string arg2)
            :   arg1_(std::move(arg1)), arg2_(std::move(arg2)) {}
    StringArgs(std::string arg1, std::string arg2, std::string arg3)
            :   arg1_(std::move(arg1)), arg2_(std::move(arg2)), arg3_(std::move(arg3)) {}
};

TEST(test_constructors, constructor_without_args)
{
    String str;
    EXPECT_STREQ(((std::string)str).data(), "0");
}

class ConstructorTest : public ::testing::TestWithParam<StringArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_constructors,
    ConstructorTest,
    ::testing::Values
    (
        StringArgs("", "0"),
        StringArgs("41736571836", "41736571836"),
        StringArgs("000000041736571836", "41736571836"),        // many begin zeros
        StringArgs("0000000", "0"),                             // many zeros
        StringArgs("-41736571836", "Number must be positive"),  // negative number
        StringArgs("365sd718=36", "Wrong number"),              // not number
        StringArgs("-365sd718=36", "Wrong number")              // negative and not number
    )
);

TEST_P(ConstructorTest, constructor)
{
    StringArgs params = GetParam();
    try
    {
        String str(params.arg1_);
        EXPECT_EQ((std::string)str, params.arg2_);
    }
    catch (const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(), params.arg2_.data());
    }
}

TEST(test_constructors, copy_constructor)
{
    std::string str = "41736571836";
    String src(str);
    const String & dest(src);

    EXPECT_EQ(str, (std::string)src);
    EXPECT_EQ(str, (std::string)dest);
}

TEST(test_assignment_operators, assignment)
{
    std::string str = "41736571836";
    String src(str);
    String dest = src;

    EXPECT_EQ(str, (std::string)src);
    EXPECT_EQ(str, (std::string)dest);

    // self-assignment
    src = src;
    EXPECT_EQ(str, (std::string)src);
}

class ArithmeticOperatorTest : public ::testing::TestWithParam<StringArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_arithmetic_operators,
    ArithmeticOperatorTest,
    ::testing::Values
    (
        StringArgs("0", "0", "Division by zero"),
        StringArgs("0", "534", "String minuend must be greater than string subtrahend"),
        StringArgs("534", "0", "Division by zero"),
        StringArgs("62", "53194", "String minuend must be greater than string subtrahend"),
        StringArgs("51934", "62")
    )
);

TEST_P(ArithmeticOperatorTest, addition_operator)
{
    StringArgs params = GetParam();
    EXPECT_EQ
    (
        (std::string)(String(params.arg1_) + String(params.arg2_)),
        std::to_string(std::stoi(params.arg1_) + std::stoi(params.arg2_))
    );
}

TEST_P(ArithmeticOperatorTest, addition_assignment_operator)
{
    StringArgs params = GetParam();
    String result(params.arg1_);
    result += String(params.arg2_);
    EXPECT_EQ
    (
        (std::string)result,
        std::to_string(std::stoi(params.arg1_) + std::stoi(params.arg2_))
    );
}

TEST_P(ArithmeticOperatorTest, subtraction_operator)
{
    StringArgs params = GetParam();
    try
    {
        String result = String(params.arg1_) - String(params.arg2_);
        EXPECT_EQ
        (
            (std::string)result,
            std::to_string(std::stoi(params.arg1_) - std::stoi(params.arg2_))
        );
    }
    catch (const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(), params.arg3_.data());
    }
}

TEST_P(ArithmeticOperatorTest, subtraction_assignment_operator)
{
    StringArgs params = GetParam();
    try
    {
        String result(params.arg1_);
        result -= String(params.arg2_);
        EXPECT_EQ
        (
                (std::string)result,
                std::to_string(std::stoi(params.arg1_) - std::stoi(params.arg2_))
        );
    }
    catch (const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(), params.arg3_.data());
    }
}

TEST_P(ArithmeticOperatorTest, multiplication_operator)
{
    StringArgs params = GetParam();
    EXPECT_EQ
    (
        (std::string)(String(params.arg1_) * String(params.arg2_)),
        std::to_string(std::stoi(params.arg1_) * std::stoi(params.arg2_))
    );
}

TEST_P(ArithmeticOperatorTest, multiplication_assignment_operator)
{
    StringArgs params = GetParam();
    String result(params.arg1_);
    result *= String(params.arg2_);
    EXPECT_EQ
    (
        (std::string)result,
        std::to_string(std::stoi(params.arg1_) * std::stoi(params.arg2_))
    );
}

TEST_P(ArithmeticOperatorTest, division_operator)
{
    StringArgs params = GetParam();
    try
    {
        String result = String(params.arg1_) / String(params.arg2_);
        EXPECT_EQ
        (
                (std::string)(result),
                std::to_string(std::stoi(params.arg1_) / std::stoi(params.arg2_))
        );
    }
    catch (const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(), params.arg3_.data());
    }
}

TEST_P(ArithmeticOperatorTest, division_assignment_operator)
{
    StringArgs params = GetParam();
    try
    {
        String result(params.arg1_);
        result /= String(params.arg2_);
        EXPECT_EQ
        (
            (std::string)(result),
            std::to_string(std::stoi(params.arg1_) / std::stoi(params.arg2_))
        );
    }
    catch (const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(), params.arg3_.data());
    }
}

TEST_P(ArithmeticOperatorTest, modulo_operator)
{
    StringArgs params = GetParam();
    try
    {
        String result = String(params.arg1_) % String(params.arg2_);
        EXPECT_EQ
        (
            (std::string)(result),
            std::to_string(std::stoi(params.arg1_) % std::stoi(params.arg2_))
        );
    }
    catch (const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(), params.arg3_.data());
    }
}

TEST_P(ArithmeticOperatorTest, modulo_assignment_operator)
{
    StringArgs params = GetParam();
    try
    {
        String result(params.arg1_);
        result %= String(params.arg2_);
        EXPECT_EQ
        (
            (std::string)(result),
            std::to_string(std::stoi(params.arg1_) % std::stoi(params.arg2_))
        );
    }
    catch (const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(), params.arg3_.data());
    }
}

class ComparisonOperatorTest : public ::testing::TestWithParam<StringArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_comparison_operators,
    ComparisonOperatorTest,
    ::testing::Values
    (
        StringArgs("856", "670068"),
        StringArgs("670068", "856"),
        StringArgs("870068", "873156"),
        StringArgs("873156", "870068"),
        StringArgs("873156", "873156")
    )
);

TEST_P(ComparisonOperatorTest, equal)
{
    StringArgs params = GetParam();
    EXPECT_EQ
    (
        String(params.arg1_) == String(params.arg2_),
        std::stoi(params.arg1_) == std::stoi(params.arg2_)
    );
}

TEST_P(ComparisonOperatorTest, less)
{
    StringArgs params = GetParam();
    EXPECT_EQ
    (
        String(params.arg1_) < String(params.arg2_),
        std::stoi(params.arg1_) < std::stoi(params.arg2_)
    );
}

TEST_P(ComparisonOperatorTest, less_or_equal)
{
    StringArgs params = GetParam();
    EXPECT_EQ
    (
        String(params.arg1_) <= String(params.arg2_),
        std::stoi(params.arg1_) <= std::stoi(params.arg2_)
    );
}

TEST_P(ComparisonOperatorTest, greater_or_equal)
{
    StringArgs params = GetParam();
    EXPECT_EQ
    (
        String(params.arg1_) >= String(params.arg2_),
        std::stoi(params.arg1_) >= std::stoi(params.arg2_)
    );
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}