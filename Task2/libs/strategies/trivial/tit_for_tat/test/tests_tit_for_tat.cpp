#include "gtest/gtest.h"
#include "tit_for_tat.h"

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

TEST(test_tit_for_tat, test_vote_update)
{
    std::vector<ChoiceArgs> steps =
    {
        ChoiceArgs(D, C, C),
        ChoiceArgs(C, D, D),
        ChoiceArgs(D, D, D),
        ChoiceArgs(C, C, D),
        ChoiceArgs(C, C, C)
    };

    TitForTatStrategy strategy;

    for (ChoiceArgs step : steps)
    {
        EXPECT_EQ(strategy.vote(), step.strategy_choice_);
        strategy.update(step.opponent1_choice_, step.opponent2_choice_);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}