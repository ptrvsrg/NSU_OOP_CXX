#include "gtest/gtest.h"
#include "tit_for_tat.h"

#include <array>

struct MoveArg
{
    Choice opponent;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}