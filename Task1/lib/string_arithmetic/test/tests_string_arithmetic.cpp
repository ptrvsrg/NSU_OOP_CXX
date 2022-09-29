#include <iostream>
#include "gtest/gtest.h"
#include "string_arithmetic.h"

TEST(test_constructors, constructor)
{
    String num;
    EXPECT_STREQ(num.to_string().data(), "0");
}

TEST(test_constructors, string_constructor)
{
    String num;

    num = String("41736571836");
    EXPECT_STREQ(num.to_string().data(), "41736571836");

    // many begin zeros
    num = String("000000041736571836");
    EXPECT_STREQ(num.to_string().data(), "41736571836");

    // many zeros
    num = String("0000000");
    EXPECT_STREQ(num.to_string().data(), "0");

    // negative number
    try
    {
        num = String("-41736571836");
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "Number must be positive");
    }

    // not number
    try
    {
        num = String("365sd718=36");
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "Wrong string number");
    }

    // not number with minus
    try
    {
        num = String("-365sd718=36");
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "Wrong string number");
    }
}

TEST(test_constructors, copy_constructor)
{
    String src("41736571836");
    String dest(src);

    EXPECT_STREQ("41736571836", src.to_string().data());
    EXPECT_STREQ("41736571836", dest.to_string().data());
    EXPECT_NE(&src, &dest);
}



TEST(test_assignment_operators, assignment)
{
    String src("41736571836");
    String dest = src;
    EXPECT_STREQ("41736571836", src.to_string().data());
    EXPECT_STREQ("41736571836", dest.to_string().data());
    EXPECT_NE(&src, &dest);

    // self-assignment
    String* pSrc = &src;
    src = src;
    EXPECT_STREQ("41736571836", src.to_string().data());
    EXPECT_EQ(&src, pSrc);
}

TEST(test_assignment_operators, addition_assignment)
{
    String sum;

    sum = String("0");
    sum += String("0");
    EXPECT_STREQ(sum.to_string().data(), "0");

    sum = String("561056");
    sum += String("0");
    EXPECT_STREQ(sum.to_string().data(), "561056");

    sum = String("0");
    sum += String("561056");
    EXPECT_STREQ(sum.to_string().data(), "561056");

    sum = String("561056");
    sum += String("714");
    EXPECT_STREQ(sum.to_string().data(), std::to_string(561056+714).data());

    sum = String("714");
    sum += String("561056");
    EXPECT_STREQ(sum.to_string().data(), std::to_string(714+561056).data());
}

TEST(test_assignment_operators, subtraction_assignment)
{
    String difference;

    difference = String("0");
    difference -= String("0");
    EXPECT_STREQ(difference.to_string().data(), "0");

    difference = String("561056");
    difference -= String("0");
    EXPECT_STREQ(difference.to_string().data(), "561056");

    difference = String("561056");
    difference -= String("714");
    EXPECT_STREQ(difference.to_string().data(), std::to_string(561056 - 714).data());

    try
    {
        difference = String("0");
        difference -= String("561056");
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "String minuend must be greater than string subtrahend");
    }

    try
    {
        difference = String("714");
        difference -= String("561056");
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "String minuend must be greater than string subtrahend");
    }
}

TEST(test_assignment_operators, multiplication_assignment)
{
    String product;

    product = String("0");
    product *= String("0");
    EXPECT_STREQ(product.to_string().data(), "0");

    product = String("561056");
    product *= String("0");
    EXPECT_STREQ(product.to_string().data(), "0");

    product = String("0");
    product *= String("561056");
    EXPECT_STREQ(product.to_string().data(), "0");

    product = String("561056");
    product *= String("714");
    EXPECT_STREQ(product.to_string().data(), std::to_string(561056 * 714).data());

    product = String("714");
    product *= String("561056");
    EXPECT_STREQ(product.to_string().data(), std::to_string(714 * 561056).data());
}

TEST(test_assignment_operators, division_assignment)
{
    String remainder;

    remainder = String("0");
    remainder %= String("561056");
    EXPECT_STREQ(remainder.to_string().data(), "0");

    remainder = String("561056");
    remainder %= String("714");
    EXPECT_STREQ(remainder.to_string().data(), std::to_string(561056 % 714).data());

    remainder = String("714");
    remainder %= String("561056");
    EXPECT_STREQ(remainder.to_string().data(), std::to_string(714 % 561056).data());

    try
    {
        remainder = String("561056");
        remainder %= String("0");
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "Division by zero");
    }

    try
    {
        remainder = String("0");
        remainder %= String("0");
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "Division by zero");
    }
}

TEST(test_assignment_operators, modulo_assignment)
{
    String remainder;

    remainder = String("0");
    remainder %= String("561056");
    EXPECT_STREQ(remainder.to_string().data(), "0");

    remainder = String("561056");
    remainder %= String("714");
    EXPECT_STREQ(remainder.to_string().data(), std::to_string(561056 % 714).data());

    remainder = String("714");
    remainder %= String("561056");
    EXPECT_STREQ(remainder.to_string().data(), std::to_string(714 % 561056).data());

    try
    {
        remainder = String("561056");
        remainder %= String("0");
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "Division by zero");
    }

    try
    {
        remainder = String("0");
        remainder %= String("0");
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "Division by zero");
    }
}



TEST(test_arithmetic_operators, addition)
{
    String addend1("6420");
    String* ptrAddend1 = &addend1;

    String addend2("167");
    String* ptrAddend2 = &addend2;

    String sum = addend1 + addend2;
    String* ptrSum = &sum;

    EXPECT_STREQ(addend1.to_string().data(), "6420");
    EXPECT_STREQ(addend2.to_string().data(), "167");

    EXPECT_STREQ(sum.to_string().data(), std::to_string(6420 + 167).data());
    EXPECT_NE(ptrAddend1, ptrSum);
    EXPECT_NE(ptrAddend2, ptrSum);
}

TEST(test_arithmetic_operators, subtraction)
{
    String minuend("6420");
    String* ptrMinuend = &minuend;

    String subtrahend("167");
    String* ptrSubtrahend = &subtrahend;

    String difference = minuend - subtrahend;
    String* ptrDifference = &difference;

    EXPECT_STREQ(minuend.to_string().data(), "6420");
    EXPECT_STREQ(subtrahend.to_string().data(), "167");

    EXPECT_STREQ(difference.to_string().data(), std::to_string(6420 - 167).data());
    EXPECT_NE(ptrMinuend, ptrDifference);
    EXPECT_NE(ptrSubtrahend, ptrDifference);
}

TEST(test_arithmetic_operators, multiplication)
{
    String multiplier1("6420");
    String* ptrMultiplier1 = &multiplier1;

    String multiplier2("167");
    String* ptrMultiplier2 = &multiplier2;

    String product = multiplier1 * multiplier2;
    String* ptrProduct = &product;

    EXPECT_STREQ(multiplier1.to_string().data(), "6420");
    EXPECT_STREQ(multiplier2.to_string().data(), "167");

    EXPECT_STREQ(product.to_string().data(), std::to_string(6420 * 167).data());
    EXPECT_NE(ptrMultiplier1, ptrProduct);
    EXPECT_NE(ptrMultiplier2, ptrProduct);
}

TEST(test_arithmetic_operators, division)
{
    String dividend("6420");
    String* ptrDividend = &dividend;

    String divisor("167");
    String* ptrDivisor = &divisor;

    String quotient = dividend / divisor;
    String* ptrQuotient = &quotient;

    EXPECT_STREQ(dividend.to_string().data(), "6420");
    EXPECT_STREQ(divisor.to_string().data(), "167");

    EXPECT_STREQ(quotient.to_string().data(), std::to_string(6420 / 167).data());
    EXPECT_NE(ptrDividend, ptrQuotient);
    EXPECT_NE(ptrDivisor, ptrQuotient);
}

TEST(test_arithmetic_operators, modulo)
{
    String dividend("6420");
    String* ptrDividend = &dividend;

    String divisor("167");
    String* ptrDivisor = &divisor;

    String remainder = dividend % divisor;
    String* ptrRemainder = &remainder;

    EXPECT_STREQ(dividend.to_string().data(), "6420");
    EXPECT_STREQ(divisor.to_string().data(), "167");

    EXPECT_STREQ(remainder.to_string().data(), std::to_string(6420 % 167).data());
    EXPECT_NE(ptrDividend, ptrRemainder);
    EXPECT_NE(ptrDivisor, ptrRemainder);
}



TEST(test_comparison_operators, equal)
{
    EXPECT_FALSE(String("856") == String("670068"));
    EXPECT_FALSE(String("670068") == String("856"));

    EXPECT_FALSE(String("870068") == String("873156"));
    EXPECT_FALSE(String("873156") == String("870068"));

    EXPECT_TRUE(String("873156") == String("873156"));
}

TEST(test_comparison_operators, less)
{
    EXPECT_TRUE(String("856") < String("670068"));
    EXPECT_FALSE(String("670068") < String("856"));

    EXPECT_TRUE(String("870068") < String("873156"));
    EXPECT_FALSE(String("873156") < String("870068"));

    EXPECT_FALSE(String("873156") < String("873156"));
}

TEST(test_comparison_operators, greater_or_equal)
{
    EXPECT_FALSE(String("856") >= String("670068"));
    EXPECT_TRUE(String("670068") >= String("856"));

    EXPECT_FALSE(String("870068") >= String("873156"));
    EXPECT_TRUE(String("873156") >= String("870068"));

    EXPECT_TRUE(String("873156") >= String("873156"));
}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}