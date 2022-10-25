#include <gtest/gtest.h>
#include "strategy_creator.h"

struct NameArgs
{
    std::string name_;
    std::string config_dir_;
    bool exception_;

    NameArgs(std::string name,
             std::string config_dir,
             bool exception)
    :   name_(std::move(name)),
        config_dir_(std::move(config_dir)),
        exception_(exception)
    {}
};

class StrategyCreatorTest : public ::testing::TestWithParam<NameArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_startegy_creator,
    StrategyCreatorTest,
    ::testing::Values
    (
        NameArgs("always_cooperate",
                 "",
                 false),
        NameArgs("always_defect",
                 "",
                 false),
        NameArgs("grim_trigger",
                 "",
                 false),
        NameArgs("pavlov",
                 "/home/acer/NSU_OOP_CXX/Task2/config/",
                 false),
        NameArgs("random",
                 "",
                 false),
        NameArgs("tit_for_tat",
                 "",
                 false),
        NameArgs("tit_for_tat_with_forgiveness",
                 "/home/acer/NSU_OOP_CXX/Task2/config/",
                 false),
        NameArgs("my_strategy",
                 "",
                 true)
    )
);

TEST_P(StrategyCreatorTest, test_create)
{
    NameArgs params = GetParam();

    StrategyCreator creator;

    try
    {
        StrategyPtr strategy_ptr = creator.Create(params.name_, params.config_dir_);
        EXPECT_FALSE(params.exception_);
    }
    catch(const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(), "Wrong strategy name");
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}