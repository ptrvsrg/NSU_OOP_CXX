#include <iostream>
#include "gtest/gtest.h"
#include "big_int.h"

TEST(test_constructors, constructor_wthout_args)
{
    BigInt num1;
    EXPECT_EQ(int(num1), 0);
}

TEST(test_constructors, int_constructor)
{
    BigInt num2(-23745);
    EXPECT_EQ(int(num2), -23745);
}

TEST(test_constructors, string_constructor)
{
    std::string str1 = "-64228";
    BigInt num1(str1);
    EXPECT_EQ(int(num1), -64228);
    EXPECT_STREQ(std::string(num1).c_str(), str1.c_str());

    // empty string
    BigInt num2("");
    EXPECT_EQ(int(num2), 0);
    EXPECT_STREQ(std::string(num2).c_str(), "0");

    // many begin zeros
    BigInt num3("000000000654");
    EXPECT_EQ(int(num3), 654);

    // many zeros
    BigInt num4("000000000");
    EXPECT_EQ(int(num4), 0);

    // minus and many begin zeros
    BigInt num5("-00045");
    EXPECT_EQ(int(num5), -45);

    // minus and many begin zeros
    BigInt num6("-000");
    EXPECT_EQ(int(num6), 0);
    EXPECT_STREQ(std::string(num6).c_str(), "0");

    // minus
    try
    {
        BigInt num7("-");
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "Wrong string number");
    }

    // not number
    try
    {
        BigInt num8("98dccS6E55");
    }
    catch (std::invalid_argument const& ex)
    {
        EXPECT_STREQ(ex.what(), "Wrong string number");
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
    BigInt tmp(-65412);
    BigInt dest(std::move(tmp));

    EXPECT_EQ(int(dest), -65412);
    EXPECT_EQ(int(tmp), 0);
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
    BigInt src(-654087);
    BigInt dest = std::move(src);

    EXPECT_EQ(int(src), 0);
    EXPECT_EQ(int(dest), -654087);
}

TEST(test_assignment_operators, addition_assignment)
{
    BigInt addend1(5123);

    addend1 += BigInt(6540);
    EXPECT_EQ(int(addend1), 5123 + 6540);

    addend1 += BigInt(-120614);
    EXPECT_EQ(int(addend1), 5123 + 6540 - 120614);

    addend1 += BigInt(-3540);
    EXPECT_EQ(int(addend1), 5123 + 6540 - 120614 - 3540);

    addend1 += BigInt(8120614);
    EXPECT_EQ(int(addend1), 5123 + 6540 - 120614 - 3540 + 8120614);

    addend1 += BigInt(0);
    EXPECT_EQ(int(addend1), 5123 + 6540 - 120614 - 3540 + 8120614);
}

TEST(test_assignment_operators, multiplication_assignment)
{
    BigInt num(649);
    num *= BigInt(31);
    EXPECT_EQ(int(num), 649*31);

    num *= BigInt(-248);
    EXPECT_EQ(int(num), 649*31*(-248));

    num *= BigInt("48060");
    EXPECT_STREQ(std::string(num).c_str(), "-239795946720");

    num *= BigInt(0);
    EXPECT_EQ(int(num), 0);
}

TEST(test_assignment_operators, subtraction_assignment)
{
    BigInt num(314);
    num -= BigInt(497);
    EXPECT_EQ(int(num), 314-497);

    num -= BigInt(142);
    EXPECT_EQ(int(num), 314-497-142);

    num -= BigInt(-534);
    EXPECT_EQ(int(num), 314-497-142-(-534));

    num -= BigInt(-273);
    EXPECT_EQ(int(num), 314-497-142-(-534)-(-273));

    num -= BigInt(0);
    EXPECT_EQ(int(num), 314-497-142-(-534)-(-273));
}

TEST(test_assignment_operators, division_assignment)
{
    BigInt num1(0);
    num1 /= BigInt(1354);
    EXPECT_EQ(int(num1), 0);

    BigInt num2(11215182);
    num2 /= BigInt(1354);
    EXPECT_EQ(int(num2), 8283);

    num2 /= BigInt(54);
    EXPECT_EQ(int(num2), 153);

    try
    {
        num1 /= BigInt(0);
    }
    catch(std::invalid_argument const & ex)
    {
        EXPECT_STREQ(ex.what(), "Division by zero");
    }

    try
    {
        num2 /= BigInt(0);
    }
    catch(std::invalid_argument const & ex)
    {
        EXPECT_STREQ(ex.what(), "Division by zero");
    }
}

TEST(test_assignment_operators, remainder_assignment)
{
    BigInt num1(0);
    num1 %= BigInt(1354);
    EXPECT_EQ(int(num1), 0);

    BigInt num2(11215182);
    num2 %= BigInt(35348);
    EXPECT_EQ(int(num2), 9866);

    num2 %= BigInt(2);
    EXPECT_EQ(int(num2), 0);

    try
    {
        num1 %= BigInt(0);
    }
    catch(std::invalid_argument const & ex)
    {
        EXPECT_STREQ(ex.what(), "Division by zero");
    }

    try
    {
        BigInt num3(5482);
        num3 %= BigInt(0);
    }
    catch(std::invalid_argument const & ex)
    {
        EXPECT_STREQ(ex.what(), "Division by zero");
    }
}



TEST(test_arithmetic_operators, unary_plus)
{
    BigInt src("6165119841981");

    EXPECT_STREQ(std::string(src).c_str(), std::string(+src).c_str());
}

TEST(test_arithmetic_operators, unary_minus)
{
    BigInt src("6165119841981");

    EXPECT_STREQ(std::string(-src).c_str(), "-6165119841981");
}



TEST(test_bitwise_operators, bitwise_not)
{
    // size is saved
    BigInt src1(654);
    BigInt dest1 = ~src1;

    EXPECT_EQ(int(src1), 654);       // 00000010 10001110
    EXPECT_EQ(int(dest1), 64881);    // 11111101 01110001

    // size is not saved
    BigInt src2(65393);
    BigInt dest2 = ~src2;

    EXPECT_EQ(int(src2), 65393);    // 11111111 01110001
    EXPECT_EQ(int(dest2), 142);     // 00000000 10001110
    EXPECT_EQ(src2.size(), 2);
    EXPECT_EQ(dest2.size(), 1);
}



TEST(test_comparison_operators, equal)
{
    EXPECT_TRUE(BigInt("6511") == BigInt("6511"));
    EXPECT_TRUE(BigInt("-6511") == BigInt("-6511"));
    EXPECT_FALSE(BigInt("6511") == BigInt("-6511"));
    EXPECT_FALSE(BigInt("-6511") == BigInt("6511"));
    EXPECT_FALSE(BigInt("6511") == BigInt("-2716"));
}

TEST(test_comparison_operators, not_equal)
{
    EXPECT_FALSE(BigInt("6511") != BigInt("6511"));
    EXPECT_FALSE(BigInt("-6511") != BigInt("-6511"));
    EXPECT_TRUE(BigInt("6511") != BigInt("-6511"));
    EXPECT_TRUE(BigInt("-6511") != BigInt("6511"));
    EXPECT_TRUE(BigInt("6511") != BigInt("-2716"));
}

TEST(test_comparison_operators, greater)
{
    EXPECT_FALSE(BigInt("6511") > BigInt("6511"));
    EXPECT_FALSE(BigInt("-6511") > BigInt("-6511"));
    EXPECT_TRUE(BigInt("6511") > BigInt("-6511"));
    EXPECT_FALSE(BigInt("-6511") > BigInt("6511"));
    EXPECT_TRUE(BigInt("6511") > BigInt("2716"));
    EXPECT_FALSE(BigInt("-6511") > BigInt("-2716"));
    EXPECT_TRUE(BigInt("6511") > BigInt("-2716"));
    EXPECT_FALSE(BigInt("-6511") > BigInt("2716"));
}

TEST(test_comparison_operators, less)
{
    EXPECT_FALSE(BigInt("6511") < BigInt("6511"));
    EXPECT_FALSE(BigInt("-6511") < BigInt("-6511"));
    EXPECT_FALSE(BigInt("6511") < BigInt("-6511"));
    EXPECT_TRUE(BigInt("-6511") < BigInt("6511"));
    EXPECT_FALSE(BigInt("6511") < BigInt("2716"));
    EXPECT_TRUE(BigInt("-6511") < BigInt("-2716"));
    EXPECT_FALSE(BigInt("6511") < BigInt("-2716"));
    EXPECT_TRUE(BigInt("-6511") < BigInt("2716"));
}

TEST(test_comparison_operators, greater_or_equal)
{
    EXPECT_TRUE(BigInt("6511") >= BigInt("6511"));
    EXPECT_TRUE(BigInt("-6511") >= BigInt("-6511"));
    EXPECT_TRUE(BigInt("6511") >= BigInt("-6511"));
    EXPECT_FALSE(BigInt("-6511") >= BigInt("6511"));
    EXPECT_TRUE(BigInt("6511") >= BigInt("2716"));
    EXPECT_FALSE(BigInt("-6511") >= BigInt("-2716"));
    EXPECT_TRUE(BigInt("6511") >= BigInt("-2716"));
    EXPECT_FALSE(BigInt("-6511") >= BigInt("2716"));
}

TEST(test_comparison_operators, less_or_equal)
{
    EXPECT_TRUE(BigInt("6511") <= BigInt("6511"));
    EXPECT_TRUE(BigInt("-6511") <= BigInt("-6511"));
    EXPECT_FALSE(BigInt("6511") <= BigInt("-6511"));
    EXPECT_TRUE(BigInt("-6511") <= BigInt("6511"));
    EXPECT_FALSE(BigInt("6511") <= BigInt("2716"));
    EXPECT_TRUE(BigInt("-6511") <= BigInt("-2716"));
    EXPECT_FALSE(BigInt("6511") <= BigInt("-2716"));
    EXPECT_TRUE(BigInt("-6511") <= BigInt("2716"));
}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}