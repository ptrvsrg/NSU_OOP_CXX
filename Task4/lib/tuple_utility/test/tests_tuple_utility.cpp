#include <gtest/gtest.h>
#include <strstream>
#include <tuple>
#include "tuple_utility.h"

TEST(test_tuple_utility,
     check_print_tuple)
{
    auto tuple = std::make_tuple(1,
                                          "dog",
                                          3.14);

    std::stringstream tuple_out;
    std::stringstream check;

    tuple_out << tuple;
    check << std::get<0>(tuple) << ", "
          << std::get<1>(tuple) << ", "
          << std::get<2>(tuple);

    EXPECT_EQ(tuple_out.str(),
              check.str());
}

TEST(tests_tuple,
     check_make_tuple)
{
    auto tuple = MakeTuple<int,
                                    std::string,
                                    double>({"1",
                                             "dog",
                                             "3.14"});
    auto check = std::make_tuple(1,
                                          "dog",
                                          3.14);
    EXPECT_EQ(tuple,
              check);
}

int main(int argc,
         char ** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}