#include <iostream>
#include <climits>
#include <sstream>
#include "gtest/gtest.h"
#include "big_int.h"

TEST(test_constructors, constructor_wthout_args)
{
    BigInt num1;
    EXPECT_EQ(int(num1), 0);
}

TEST(test_constructors, int_constructor)
{
    BigInt num1(10);
    EXPECT_EQ(int(num1), 10);

    BigInt num2(INT_MAX);
    EXPECT_EQ(int(num2), INT_MAX);

    BigInt num3(-34);
    EXPECT_EQ(int(num3), -34);

    BigInt num4(INT_MIN);
    EXPECT_EQ(int(num4), INT_MIN);
}

TEST(test_constructors, string_constructor)
{
    EXPECT_EQ(int(BigInt("-64228")), -64228);

    // 100000000 000000000 000000000 000000000
    EXPECT_STREQ(std::string(BigInt("4294967296")).data(), "4294967296");

    // empty string
    EXPECT_EQ(int(BigInt("")), 0);

    // many begin zeros
    EXPECT_EQ(int(BigInt("000000000654")), 654);

    // many zeros
    EXPECT_EQ(int(BigInt("000000000")), 0);

    // minus and many begin zeros
    EXPECT_EQ(int(BigInt("-00045")), -45);

    // minus and many begin zeros
    EXPECT_EQ(int(BigInt("-000")), 0);

    // minus
    try
    {
        BigInt num1("-");
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "Wrong number");
    }

    // not number
    try
    {
        BigInt num2("98dccS6E55");
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "Wrong number");
    }
}

TEST(test_constructors, copy_constructor)
{
    BigInt src(-65412);
    BigInt dest(src);

    EXPECT_EQ(int(src), int(dest));
    EXPECT_NE(&src, &dest);
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

TEST(test_assignment_operators, addition_assignment)
{
    BigInt sum;

    // adding zero
    sum = BigInt(0);
    sum += BigInt(534);
    EXPECT_EQ(int(sum), 534);

    sum = BigInt(-534);
    sum += BigInt(0);
    EXPECT_EQ(int(sum), -534);

    sum = BigInt(0);
    sum += BigInt(-534);
    EXPECT_EQ(int(sum), -534);

    sum = BigInt(534);
    sum += BigInt(0);
    EXPECT_EQ(int(sum), 534);

    // identical signs
    sum = BigInt(62);
    sum += BigInt(534);
    EXPECT_EQ(int(sum), 62+534);

    sum = BigInt(534);
    sum += BigInt(62);
    EXPECT_EQ(int(sum), 62+534);

    sum = BigInt(-62);
    sum += BigInt(-534);
    EXPECT_EQ(int(sum), -62-534);

    sum = BigInt(-534);
    sum += BigInt(-62);
    EXPECT_EQ(int(sum), -62-534);

    // different signs
    sum = BigInt(62);
    sum += BigInt(-534);
    EXPECT_EQ(int(sum), 62-534);

    sum = BigInt(-534);
    sum += BigInt(62);
    EXPECT_EQ(int(sum), 62-534);

    sum = BigInt(-62);
    sum += BigInt(534);
    EXPECT_EQ(int(sum), -62+534);

    sum = BigInt(534);
    sum += BigInt(-62);
    EXPECT_EQ(int(sum), -62+534);
}

TEST(test_assignment_operators, multiplication_assignment)
{
    BigInt product;

    // multiplication by zero
    product = BigInt(0);
    product *= BigInt(534);
    EXPECT_EQ(int(product), 0);

    product = BigInt(534);
    product *= BigInt(0);
    EXPECT_EQ(int(product), 0);

    product = BigInt(0);
    product *= BigInt(-534);
    EXPECT_EQ(int(product), 0);

    product = BigInt(534);
    product *= BigInt(0);
    EXPECT_EQ(int(product), 0);

    // identical signs
    product = BigInt(62);
    product *= BigInt(534);
    EXPECT_EQ(int(product), 62*534);

    product = BigInt(534);
    product *= BigInt(62);
    EXPECT_EQ(int(product), 62*534);

    product = BigInt(-62);
    product *= BigInt(-534);
    EXPECT_EQ(int(product), 62*534);

    product = BigInt(-534);
    product *= BigInt(-62);
    EXPECT_EQ(int(product), 62*534);

    // different signs
    product = BigInt(62);
    product *= BigInt(-534);
    EXPECT_EQ(int(product), 62*(-534));

    product = BigInt(-534);
    product *= BigInt(62);
    EXPECT_EQ(int(product), (-534)*62);

    product = BigInt(-62);
    product *= BigInt(534);
    EXPECT_EQ(int(product), (-62)*534);

    product = BigInt(534);
    product *= BigInt(-62);
    EXPECT_EQ(int(product), 534*(-62));
}

TEST(test_assignment_operators, subtraction_assignment)
{
    BigInt difference;

    // zero subtracting
    difference = BigInt(534);
    difference -= BigInt(0);
    EXPECT_EQ(int(difference), 534);

    difference = BigInt(-534);
    difference -= BigInt(0);
    EXPECT_EQ(int(difference), -534);

    // subtracting from zero
    difference = BigInt(0);
    difference -= BigInt(534);
    EXPECT_EQ(int(difference), -534);

    difference = BigInt(0);
    difference -= BigInt(-534);
    EXPECT_EQ(int(difference), 534);

    // identical signs
    difference = BigInt(534);
    difference -= BigInt(62);
    EXPECT_EQ(int(difference), 534-62);

    difference = BigInt(62);
    difference -= BigInt(534);
    EXPECT_EQ(int(difference), 62-534);

    difference = BigInt(-62);
    difference -= BigInt(-534);
    EXPECT_EQ(int(difference), -62+534);

    difference = BigInt(-534);
    difference -= BigInt(-62);
    EXPECT_EQ(int(difference), -534+62);

    // different signs
    difference = BigInt(62);
    difference -= BigInt(-534);
    EXPECT_EQ(int(difference), 62+534);

    difference = BigInt(-534);
    difference -= BigInt(62);
    EXPECT_EQ(int(difference), -534-62);

    difference = BigInt(-62);
    difference -= BigInt(534);
    EXPECT_EQ(int(difference), -62-534);

    difference = BigInt(534);
    difference -= BigInt(-62);
    EXPECT_EQ(int(difference), 534+62);
}

TEST(test_assignment_operators, division_assignment)
{
    BigInt quotient;

    // zero division
    quotient = BigInt(0);
    quotient /= BigInt(1354);
    EXPECT_EQ(int(quotient), 0);

    // identical signs
    quotient = BigInt(1534);
    quotient /= BigInt(62);
    EXPECT_EQ(int(quotient), 1534/62);

    quotient = BigInt(62);
    quotient /= BigInt(1534);
    EXPECT_EQ(int(quotient), 62/1534);

    quotient = BigInt(-62);
    quotient /= BigInt(-534);
    EXPECT_EQ(int(quotient), (-62)/(-534));

    quotient = BigInt(-534);
    quotient /= BigInt(-62);
    EXPECT_EQ(int(quotient), (-534)/(-62));

    // different signs
    quotient = BigInt(62);
    quotient /= BigInt(-534);
    EXPECT_EQ(int(quotient), 62/(-534));

    quotient = BigInt(-534);
    quotient /= BigInt(62);
    EXPECT_EQ(int(quotient), (-534)/62);

    quotient = BigInt(-62);
    quotient /= BigInt(534);
    EXPECT_EQ(int(quotient), (-62)/534);

    quotient = BigInt(534);
    quotient /= BigInt(-62);
    EXPECT_EQ(int(quotient), 534/(-62));

    // division by zero
    try
    {
        quotient = BigInt(534);
        quotient /= BigInt(0);
    }
    catch(std::invalid_argument const & ex)
    {
        EXPECT_STREQ(ex.what(), "Division by zero");
    }

    // zero division by zero
    try
    {
        quotient = BigInt(0);
        quotient /= BigInt(0);
    }
    catch(std::invalid_argument const & ex)
    {
        EXPECT_STREQ(ex.what(), "Division by zero");
    }
}

TEST(test_assignment_operators, mudulo_assignment)
{
    BigInt remainder;

    // zero division
    remainder = BigInt(0);
    remainder %= BigInt(1354);
    EXPECT_EQ(int(remainder), 0);

    // identical signs
    remainder = BigInt(1534);
    remainder %= BigInt(62);
    EXPECT_EQ(int(remainder), 1534%62);

    remainder = BigInt(62);
    remainder %= BigInt(1534);
    EXPECT_EQ(int(remainder), 62%1534);

    remainder = BigInt(-62);
    remainder %= BigInt(-534);
    EXPECT_EQ(int(remainder), (-62)%(-534));

    remainder = BigInt(-534);
    remainder %= BigInt(-62);
    EXPECT_EQ(int(remainder), (-534)%(-62));

    // different signs
    remainder = BigInt(62);
    remainder %= BigInt(-534);
    EXPECT_EQ(int(remainder), 62%(-534));

    remainder = BigInt(-534);
    remainder %= BigInt(62);
    EXPECT_EQ(int(remainder), (-534)%62);

    remainder = BigInt(-62);
    remainder %= BigInt(534);
    EXPECT_EQ(int(remainder), (-62)%534);

    remainder = BigInt(534);
    remainder %= BigInt(-62);
    EXPECT_EQ(int(remainder), 534%(-62));

    // division by zero
    try
    {
        remainder = BigInt(534);
        remainder %= BigInt(0);
    }
    catch(std::invalid_argument const & ex)
    {
        EXPECT_STREQ(ex.what(), "Division by zero");
    }

    // zero division by zero
    try
    {
        remainder = BigInt(0);
        remainder %= BigInt(0);
    }
    catch(std::invalid_argument const & ex)
    {
        EXPECT_STREQ(ex.what(), "Division by zero");
    }
}


TEST(test_assignment_operators, bitwise_or_assignment)
{
    BigInt result;

    // identical size
    result = BigInt(85);            // 0 01010101
    result |= BigInt(170);          // 0 10101010
    EXPECT_EQ(int(result), 255);    // 0 11111111

    // different size
    result = BigInt(21845);         // 0 01010101 01010101
    result |= BigInt(170);          // 0          10101010
    EXPECT_EQ(int(result), 22015);  // 0 01010101 11111111
    EXPECT_EQ(result.size(), 2);

    // negative numbers
    result = BigInt(-21845);        // 1 01010101 01010101
    result |= BigInt(-170);         // 1          10101010
    EXPECT_EQ(int(result), -22015); // 1 01010101 11111111

    // different sign
    result = BigInt(21845);         // 0 01010101 01010101
    result |= BigInt(-170);         // 1          10101010
    EXPECT_EQ(int(result), -22015); // 1 01010101 11111111
}

TEST(test_assignment_operators, bitwise_and_assignment)
{
    BigInt result;

    // identical size
    result = BigInt(87);            // 0 01010111
    result &= BigInt(170);          // 0 10101010
    EXPECT_EQ(int(result), 2);      // 0 00000010

    // different size
    result = BigInt(21847);         // 0 01010101 01010111
    result &= BigInt(170);          // 0          10101010
    EXPECT_EQ(int(result), 2);      // 0          00000010
    EXPECT_EQ(result.size(), 1);

    // negative numbers
    result = BigInt(-21847);        // 1 01010101 01010111
    result &= BigInt(-170);         // 1          10101010
    EXPECT_EQ(int(result), -2);     // 1          00000010

    // different sign
    result = BigInt(21847);         // 0 01010101 01010111
    result &= BigInt(-170);         // 1          10101010
    EXPECT_EQ(int(result), 2);      // 0          00000010
}

TEST(test_assignment_operators, bitwise_xor_assignment)
{
    BigInt result;

    // identical sizes
    result = BigInt(87);            // 0 01010111
    result ^= BigInt(170);          // 0 10101010
    EXPECT_EQ(int(result), 253);    // 0 11111101

    // different arg sizes
    result = BigInt(21847);         // 0 01010101 01010111
    result ^= BigInt(170);          // 0          10101010
    EXPECT_EQ(int(result), 22013);  // 0 01010101 11111101
    EXPECT_EQ(result.size(), 2);

    // different arg size and return size
    result = BigInt(21847);         // 0 01010101 01010111
    result ^= BigInt(21930);        // 0 01010101 10101010
    EXPECT_EQ(int(result), 253);    // 0          11111101
    EXPECT_EQ(result.size(), 1);

    // negative numbers
    result = BigInt(-21847);        // 1 01010101 01010111
    result ^= BigInt(-170);         // 1          10101010
    EXPECT_EQ(int(result), 22013);  // 0 01010101 11111101

    // different sign
    result = BigInt(21847);         // 0 01010101 01010111
    result ^= BigInt(-170);         // 1          10101010
    EXPECT_EQ(int(result), -22013); // 1 01010101 11111101
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

TEST(test_arithmetic_operators, addition)
{
    BigInt addend1(6420);
    BigInt* ptrAddend1 = &addend1;

    BigInt addend2(167);
    BigInt* ptrAddend2 = &addend2;

    BigInt sum = addend1 + addend2;
    BigInt* ptrSum = &sum;

    EXPECT_EQ(int(addend1), 6420);
    EXPECT_EQ(int(addend2), 167);

    EXPECT_EQ(int(sum), 6420+167);
    EXPECT_NE(ptrAddend1, ptrSum);
    EXPECT_NE(ptrAddend2, ptrSum);
}

TEST(test_arithmetic_operators, subtraction)
{
    BigInt minuend(6420);
    BigInt* ptrMinuend = &minuend;

    BigInt subtrahend(167);
    BigInt* ptrSubtrahend = &subtrahend;

    BigInt difference = minuend - subtrahend;
    BigInt* ptrDifference = &difference;

    EXPECT_EQ(int(minuend), 6420);
    EXPECT_EQ(int(subtrahend), 167);

    EXPECT_EQ(int(difference), 6420-167);
    EXPECT_NE(ptrMinuend, ptrDifference);
    EXPECT_NE(ptrSubtrahend, ptrDifference);
}

TEST(test_arithmetic_operators, multiplication)
{
    BigInt multiplier1(6420);
    BigInt* ptrMultiplier1 = &multiplier1;

    BigInt multiplier2(167);
    BigInt* ptrMultiplier2 = &multiplier2;

    BigInt product = multiplier1 * multiplier2;
    BigInt* ptrProduct = &product;

    EXPECT_EQ(int(multiplier1), 6420);
    EXPECT_EQ(int(multiplier2), 167);

    EXPECT_EQ(int(product), 6420*167);
    EXPECT_NE(ptrMultiplier1, ptrProduct);
    EXPECT_NE(ptrMultiplier2, ptrProduct);
}

TEST(test_arithmetic_operators, division)
{
    BigInt dividend(6420);
    BigInt* ptrDividend = &dividend;

    BigInt divisor(167);
    BigInt* ptrDivisor = &divisor;

    BigInt quotient = dividend / divisor;
    BigInt* ptrQuotient = &quotient;

    EXPECT_EQ(int(dividend), 6420);
    EXPECT_EQ(int(divisor), 167);

    EXPECT_EQ(int(quotient), 6420/167);
    EXPECT_NE(ptrDividend, ptrQuotient);
    EXPECT_NE(ptrDivisor, ptrQuotient);
}

TEST(test_arithmetic_operators, modulo)
{
    BigInt dividend(6420);
    BigInt* ptrDividend = &dividend;

    BigInt divisor(167);
    BigInt* ptrDivisor = &divisor;

    BigInt remainder = dividend % divisor;
    BigInt* ptrRemainder = &remainder;

    EXPECT_EQ(int(dividend), 6420);
    EXPECT_EQ(int(divisor), 167);

    EXPECT_EQ(int(remainder), 6420%167);
    EXPECT_NE(ptrDividend, ptrRemainder);
    EXPECT_NE(ptrDivisor, ptrRemainder);
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



TEST(test_bitwise_operators, bitwise_not)
{
    BigInt src;

    // size is saved
    src = BigInt(654);              // 0 00000010 10001110
    EXPECT_EQ(int(~src), -64881);   // 1 11111101 01110001

    // size is not saved
    src = BigInt(65393);            // 0 11111111 01110001
    EXPECT_EQ(int(~src), -142);     // 1 00000000 10001110
    EXPECT_EQ((~src).size(), 1);
}

TEST(test_bitwise_operators, bitwise_or)
{
    BigInt arg1(21845);
    BigInt* ptrArg1 = &arg1;

    BigInt arg2(170);
    BigInt* ptrArg2 = &arg2;

    BigInt res = arg1 | arg2;
    BigInt* ptrSum = &res;

    EXPECT_EQ(int(arg1), 21845);    // 0 01010101 01010101
    EXPECT_EQ(int(arg2), 170);      // 0          10101010

    EXPECT_EQ(int(res), 21845|170); // 0 01010101 11111111
    EXPECT_NE(ptrArg1, ptrSum);
    EXPECT_NE(ptrArg2, ptrSum);
}

TEST(test_bitwise_operators, bitwise_and)
{
    BigInt arg1(21847);
    BigInt* ptrArg1 = &arg1;

    BigInt arg2(170);
    BigInt* ptrArg2 = &arg2;

    BigInt res = arg1 & arg2;
    BigInt* ptrSum = &res;

    EXPECT_EQ(int(arg1), 21847);    // 0 01010101 01010111
    EXPECT_EQ(int(arg2), 170);      // 0          10101010

    EXPECT_EQ(int(res), 21847&170); // 0          00000010
    EXPECT_NE(ptrArg1, ptrSum);
    EXPECT_NE(ptrArg2, ptrSum);
}

TEST(test_bitwise_operators, bitwise_xor)
{
    BigInt arg1(21847);
    BigInt* ptrArg1 = &arg1;

    BigInt arg2(170);
    BigInt* ptrArg2 = &arg2;

    BigInt res = arg1 ^ arg2;
    BigInt* ptrSum = &res;

    EXPECT_EQ(int(arg1), 21847);    // 0 01010101 01010111
    EXPECT_EQ(int(arg2), 170);      // 0          10101010

    EXPECT_EQ(int(res), 21847^170); // 0 01010101 11111101
    EXPECT_NE(ptrArg1, ptrSum);
    EXPECT_NE(ptrArg2, ptrSum);
}



TEST(test_comparison_operators, equal)
{
    EXPECT_TRUE(BigInt(6511) == BigInt(6511));
    EXPECT_TRUE(BigInt(-6511) == BigInt(-6511));
    EXPECT_FALSE(BigInt(6511) == BigInt(-6511));
    EXPECT_FALSE(BigInt(-6511) == BigInt(6511));
    EXPECT_FALSE(BigInt(6511) == BigInt(-2716));
}

TEST(test_comparison_operators, not_equal)
{
    EXPECT_FALSE(BigInt(6511) != BigInt(6511));
    EXPECT_FALSE(BigInt(-6511) != BigInt(-6511));
    EXPECT_TRUE(BigInt(6511) != BigInt(-6511));
    EXPECT_TRUE(BigInt(-6511) != BigInt(6511));
    EXPECT_TRUE(BigInt(6511) != BigInt(-2716));
}

TEST(test_comparison_operators, greater)
{
    EXPECT_FALSE(BigInt(6511) > BigInt(6511));
    EXPECT_FALSE(BigInt(-6511) > BigInt(-6511));
    EXPECT_TRUE(BigInt(6511) > BigInt(-6511));
    EXPECT_FALSE(BigInt(-6511) > BigInt(6511));
    EXPECT_TRUE(BigInt(6511) > BigInt(2716));
    EXPECT_FALSE(BigInt(-6511) > BigInt(-2716));
    EXPECT_TRUE(BigInt(6511) > BigInt(-2716));
    EXPECT_FALSE(BigInt(-6511) > BigInt(2716));
}

TEST(test_comparison_operators, less)
{
    EXPECT_FALSE(BigInt(6511) < BigInt(6511));
    EXPECT_FALSE(BigInt(-6511) < BigInt(-6511));
    EXPECT_FALSE(BigInt(6511) < BigInt(-6511));
    EXPECT_TRUE(BigInt(-6511) < BigInt(6511));
    EXPECT_FALSE(BigInt(6511) < BigInt(2716));
    EXPECT_TRUE(BigInt(-6511) < BigInt(-2716));
    EXPECT_FALSE(BigInt(6511) < BigInt(-2716));
    EXPECT_TRUE(BigInt(-6511) < BigInt(2716));
}

TEST(test_comparison_operators, greater_or_equal)
{
    EXPECT_TRUE(BigInt(6511) >= BigInt(6511));
    EXPECT_TRUE(BigInt(-6511) >= BigInt(-6511));
    EXPECT_TRUE(BigInt(6511) >= BigInt(-6511));
    EXPECT_FALSE(BigInt(-6511) >= BigInt(6511));
    EXPECT_TRUE(BigInt(6511) >= BigInt(2716));
    EXPECT_FALSE(BigInt(-6511) >= BigInt(-2716));
    EXPECT_TRUE(BigInt(6511) >= BigInt(-2716));
    EXPECT_FALSE(BigInt(-6511) >= BigInt(2716));
}

TEST(test_comparison_operators, less_or_equal)
{
    EXPECT_TRUE(BigInt(6511) <= BigInt(6511));
    EXPECT_TRUE(BigInt(-6511) <= BigInt(-6511));
    EXPECT_FALSE(BigInt(6511) <= BigInt(-6511));
    EXPECT_TRUE(BigInt(-6511) <= BigInt(6511));
    EXPECT_FALSE(BigInt(6511) <= BigInt(2716));
    EXPECT_TRUE(BigInt(-6511) <= BigInt(-2716));
    EXPECT_FALSE(BigInt(6511) <= BigInt(-2716));
    EXPECT_TRUE(BigInt(-6511) <= BigInt(2716));
}



TEST(test_type_conversion_operators, int_conversion)
{
    BigInt num;

    num = BigInt(654);
    EXPECT_EQ(int(num), 654);

    num = BigInt(-654);
    EXPECT_EQ(int(num), -654);

    try
    {
        num = BigInt("165165161654");
    }
    catch(std::invalid_argument const & ex)
    {
        EXPECT_STREQ(ex.what(), "Int overflow");
    }
}

TEST(test_type_conversion_operators, string_conversion)
{
    BigInt num;

    num = BigInt("654");
    EXPECT_STREQ(std::string(num).data(), "654");

    num = BigInt("-654");
    EXPECT_STREQ(std::string(num).data(), "-654");

    num = BigInt("-0");
    EXPECT_STREQ(std::string(num).data(), "0");
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