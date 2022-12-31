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
                 "files/",
                 false),
        NameArgs("random",
                 "",
                 false),
        NameArgs("tit_for_tat",
                 "",
                 false),
        NameArgs("tit_for_tat_with_forgiveness",
                 "files/",
                 false),
        NameArgs("my_strategy",
                 "",
                 true)
    )
);

TEST_P(StrategyCreatorTest,
       test_create)
{
    NameArgs params = GetParam();

    StrategyCreator creator;

    if (params.exception_)
    {
        EXPECT_THROW
        (
            {
                StrategyPtr strategy_ptr = creator.Create(params.name_,
                                                          params.config_dir_);
            },
            StrategyNameException
        );
    }
    else
    {
        EXPECT_NO_THROW
        (
            StrategyPtr strategy_ptr = creator.Create(params.name_,
                                                      params.config_dir_);
        );
    }
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}