#include <gtest/gtest.h>
#include "grim_trigger.h"

#include <vector>

struct ChoiceArgs
{
    Choice opponent1_choice_;
    Choice opponent2_choice_;
    Choice strategy_choice_;

    ChoiceArgs(Choice opponent1_choice,
               Choice opponent2_choice,
               Choice strategy_choice)
    :   opponent1_choice_(opponent1_choice),
        opponent2_choice_(opponent2_choice),
        strategy_choice_(strategy_choice) {}
};

class GrimTriggerStrategyTest : public ::testing::TestWithParam<std::vector<ChoiceArgs>> {};
INSTANTIATE_TEST_SUITE_P
(
    test_grim_trigger_strategy,
    GrimTriggerStrategyTest,
    ::testing::Values
    (
        std::vector<ChoiceArgs>{
            ChoiceArgs(C, C, C),
            ChoiceArgs(C, C, C),
            ChoiceArgs(C, C, C),
            ChoiceArgs(C, C, C),
            ChoiceArgs(C, C, C),
            ChoiceArgs(D, D, C),
            ChoiceArgs(C, D, D),
            ChoiceArgs(C, C, D),
            ChoiceArgs(D, D, D),
            ChoiceArgs(C, D, D),
            ChoiceArgs(D, D, D)
        }
    )
);

TEST_P(GrimTriggerStrategyTest,
       test_vote_update)
{
    GrimTriggerStrategy strategy;
    std::vector<ChoiceArgs> params_vector = GetParam();

    for (ChoiceArgs params : params_vector)
    {
        EXPECT_EQ(strategy.vote(),
                  params.strategy_choice_);
        strategy.update(params.opponent1_choice_,
                        params.opponent2_choice_);
    }
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}