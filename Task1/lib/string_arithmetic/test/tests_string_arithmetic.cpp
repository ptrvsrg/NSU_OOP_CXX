#include <iostream>
#include "gtest/gtest.h"
#include "string_arithmetic.h"

TEST(test_constructors, string_constructor)
{
    std::string num1 = "41736571836";
    String strNum1(num1);
    EXPECT_STREQ("41736571836", strNum1.to_string().data());
    EXPECT_STREQ(num1.c_str(), "41736571836");

    // many begin zeros
    String strNum2("000000041736571836");
    EXPECT_STREQ("41736571836", strNum2.to_string().data());

    // many zeros
    String strNum3("0000000");
    EXPECT_STREQ("0", strNum3.to_string().data());

    // negative number
    try
    {
        String strNum4("-41736571836");
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "Wrong string number");
    }

    // not number
    try
    {
        String strNum5("365sd718=36");
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "Wrong string number");
    }
}

TEST(test_constructors, copy_constructor)
{
    std::string num = "41736571836";

    String src(num);
    String dest(src);

    EXPECT_STREQ("41736571836", num.data());
    EXPECT_STREQ("41736571836", src.to_string().data());
    EXPECT_STREQ("41736571836", dest.to_string().data());
    EXPECT_NE(&src, &dest);
}

TEST(test_constructors, move_constructor)
{
    String src("41736571836");
    String dest(std::move(src));

    EXPECT_TRUE(src.to_string().empty());
    EXPECT_STREQ("41736571836", dest.to_string().data());
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

TEST(test_assignment_operators, move_assignment)
{
    String src("41736571836");
    String dest = std::move(src);
    EXPECT_TRUE(src.to_string().empty());
    EXPECT_STREQ("41736571836", dest.to_string().data());
}

TEST(test_assignment_operators, addition_assignment)
{
    String addendStr1("123123123123");
    String addendStr2("654654654654");

    String* pAddendStr1 = &addendStr1;
    String* pAddendStr2 = &addendStr2;

    addendStr2 += addendStr1;

    EXPECT_STREQ("123123123123", addendStr1.to_string().data());
    EXPECT_STREQ(addendStr2.to_string().data(), "777777777777");

    EXPECT_EQ(pAddendStr1, &addendStr1);
    EXPECT_EQ(pAddendStr2, &addendStr2);
}

TEST(test_assignment_operators, multiplication_assignment)
{
    String multiplierStr1("646314");
    String multiplierStr2("103705");

    String* pMultiplierStr1 = &multiplierStr1;
    String* pMultiplierStr2 = &multiplierStr2;

    multiplierStr2 *= multiplierStr1;

    EXPECT_STREQ("646314", multiplierStr1.to_string().data());
    EXPECT_STREQ(multiplierStr2.to_string().data(), "67025993370");

    EXPECT_EQ(pMultiplierStr1, &multiplierStr1);
    EXPECT_EQ(pMultiplierStr2, &multiplierStr2);
}

TEST(test_assignment_operators, subtraction_assignment)
{
    String minuendStr("646314");
    String subtrahendStr("103705");

    String* pMinuendStr = &minuendStr;
    String* pSubtrahendStr = &subtrahendStr;

    minuendStr -= subtrahendStr;

    EXPECT_STREQ("103705", subtrahendStr.to_string().data());
    EXPECT_STREQ(minuendStr.to_string().data(),"542609");

    EXPECT_EQ(pMinuendStr, &minuendStr);
    EXPECT_EQ(pSubtrahendStr, &subtrahendStr);
}

TEST(test_assignment_operators, division_assignment)
{
    String dividendStr("67025993370");
    String divisorStr("103705");

    String* pDividendStr = &dividendStr;
    String* pDivisorStr = &divisorStr;

    dividendStr /= divisorStr;

    EXPECT_STREQ(dividendStr.to_string().data(), "646314");
    EXPECT_STREQ("103705", divisorStr.to_string().data());

    EXPECT_EQ(pDividendStr, &dividendStr);
    EXPECT_EQ(pDivisorStr, &divisorStr);
}

TEST(test_assignment_operators, remainder_assignment)
{
    std::string dividend = "67025993370";
    std::string divisor = "1037015";

    String dividendStr("67025993370");
    String divisorStr("1037015");

    String* pDividendStr = &dividendStr;
    String* pDivisorStr = &divisorStr;

    dividendStr %= divisorStr;

    EXPECT_STREQ(dividendStr.to_string().data(), "602875");
    EXPECT_STREQ("1037015", divisorStr.to_string().data());

    EXPECT_EQ(pDividendStr, &dividendStr);
    EXPECT_EQ(pDivisorStr, &divisorStr);
}



TEST(test_arithmetic_operators, addition)
{
    String addendStr1("123123123123");
    String addendStr2("654654654654");
    String addendStr3("890890890890");

    String* pAddendStr1 = &addendStr1;
    String* pAddendStr2 = &addendStr2;
    String* pAddendStr3 = &addendStr3;

    // without carry
    String sum1 = addendStr1 + addendStr2;
    // with carry
    String sum2 = addendStr1 + addendStr3;

    EXPECT_STREQ("123123123123", addendStr1.to_string().data());
    EXPECT_STREQ("654654654654", addendStr2.to_string().data());
    EXPECT_STREQ("890890890890", addendStr3.to_string().data());

    EXPECT_EQ(pAddendStr1, &addendStr1);
    EXPECT_EQ(pAddendStr2, &addendStr2);
    EXPECT_EQ(pAddendStr3, &addendStr3);

    EXPECT_STREQ(sum1.to_string().data(), "777777777777");
    EXPECT_STREQ(sum2.to_string().data(), "1014014014013");
}

TEST(test_arithmetic_operators, multiplication)
{
    String multiplierStr1("103705");
    String multiplierStr2("3");
    String multiplierStr3("646314");
    String multiplierStr4("0");

    String* pMultiplierStr1 = &multiplierStr1;
    String* pMultiplierStr2 = &multiplierStr2;
    String* pMultiplierStr3 = &multiplierStr3;
    String* pMultiplierStr4 = &multiplierStr4;

    // without carry
    String product1 = multiplierStr1 * multiplierStr2;
    // with carry
    String product2 = multiplierStr1 * multiplierStr3;
    // multiplication by zero
    String product3 = multiplierStr1 * multiplierStr4;


    EXPECT_STREQ("103705", multiplierStr1.to_string().data());
    EXPECT_STREQ("3", multiplierStr2.to_string().data());
    EXPECT_STREQ("646314", multiplierStr3.to_string().data());
    EXPECT_STREQ("0", multiplierStr4.to_string().data());

    EXPECT_EQ(pMultiplierStr1, &multiplierStr1);
    EXPECT_EQ(pMultiplierStr2, &multiplierStr2);
    EXPECT_EQ(pMultiplierStr3, &multiplierStr3);
    EXPECT_EQ(pMultiplierStr4, &multiplierStr4);

    EXPECT_STREQ(product1.to_string().data(), "311115");
    EXPECT_STREQ(product2.to_string().data(), "67025993370");
    EXPECT_STREQ(product3.to_string().data(), "0");
}

TEST(test_arithmetic_operators, subtraction)
{
    String minuendStr("646314");
    String subtrahendStr("103705");

    String* pMinuendStr = &minuendStr;
    String* pSubtrahendStr = &subtrahendStr;

    String difference = minuendStr - subtrahendStr;

    EXPECT_STREQ("646314", minuendStr.to_string().data());
    EXPECT_STREQ("103705", subtrahendStr.to_string().data());

    EXPECT_EQ(pMinuendStr, &minuendStr);
    EXPECT_EQ(pSubtrahendStr, &subtrahendStr);

    EXPECT_STREQ(difference.to_string().data(), "542609");

    // negative difference
    try
    {
        String product = subtrahendStr - minuendStr;
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "String minuend must be greater than string subtrahend");
    }
}

TEST(test_arithmetic_operators, division)
{
    String dividendStr1("67025993370");
    String dividendStr2("0");
    String divisorStr1("103705");
    String divisorStr2("1037015");

    String* pDividendStr1 = &dividendStr1;
    String* pDividendStr2 = &dividendStr2;
    String* pDivisorStr1 = &divisorStr1;
    String* pDivisorStr2 = &divisorStr2;

    // without remainder
    String quotient1 = dividendStr1 / divisorStr1;
    // with remainder
    String quotient2 = dividendStr1 / divisorStr2;
    // zero division
    String quotient3 = dividendStr2 / divisorStr1;

    EXPECT_STREQ("67025993370", dividendStr1.to_string().data());
    EXPECT_STREQ("103705", divisorStr1.to_string().data());
    EXPECT_STREQ("1037015", divisorStr2.to_string().data());

    EXPECT_EQ(pDividendStr1, &dividendStr1);
    EXPECT_EQ(pDivisorStr1, &divisorStr1);
    EXPECT_EQ(pDivisorStr2, &divisorStr2);

    EXPECT_STREQ(quotient1.to_string().data(), "646314");
    EXPECT_STREQ(quotient2.to_string().data(), "64633");
    EXPECT_STREQ(quotient2.to_string().data(), "0");

    // divide by zero
    try
    {
        String quotient4 = dividendStr1 / String("0");
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "Division by zero");
    }

    try
    {
        String quotient5 = dividendStr2 / String("0");
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "Division by zero");
    }
}

TEST(test_arithmetic_operators, remainder)
{
    String dividendStr("67025993370");
    String divisorStr1("1037015");

    String* pDividendStr = &dividendStr;
    String* pDivisorStr1 = &divisorStr1;

    String remainder1 = dividendStr % divisorStr1;

    EXPECT_STREQ("67025993370", dividendStr.to_string().data());
    EXPECT_STREQ("1037015", divisorStr1.to_string().data());

    EXPECT_EQ(pDividendStr, &dividendStr);
    EXPECT_EQ(pDivisorStr1, &divisorStr1);

    EXPECT_STREQ(remainder1.to_string().data(), "602875");

    // divide by zero
    try
    {
        String quotient2 = dividendStr % String("0");
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "Division by zero");
    }
}



TEST(test_comparison_operators, equal)
{
    EXPECT_TRUE(String("873156") == String("873156"));
    EXPECT_FALSE(String("873156") == String("670068"));
}

TEST(test_comparison_operators, less)
{
    EXPECT_FALSE(String("873156") < String("873156"));
    EXPECT_FALSE(String("873156") < String("670068"));
    EXPECT_TRUE(String("670068") < String("873156"));
}

TEST(test_comparison_operators, greater_or_equal)
{
    EXPECT_TRUE(String("873156") >= String("873156"));
    EXPECT_TRUE(String("873156") >= String("670068"));
    EXPECT_FALSE(String("670068") >= String("873156"));
}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}