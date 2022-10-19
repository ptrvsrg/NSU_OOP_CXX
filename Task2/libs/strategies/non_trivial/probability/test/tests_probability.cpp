#include "gtest/gtest.h"
#include "probability.h"

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

class StrategyTest : public ::testing::TestWithParam<std::vector<ChoiceArgs>> {};
INSTANTIATE_TEST_SUITE_P
(
    test_parser,
    StrategyTest,
    ::testing::Values
    (
        std::vector<ChoiceArgs>{
            ChoiceArgs(C, C, D),
            ChoiceArgs(C, C, D),
            ChoiceArgs(D, C, D),
            ChoiceArgs(D, C, D),
            ChoiceArgs(C, C, D),
            ChoiceArgs(D, D, D),
            ChoiceArgs(C, D, D),
            ChoiceArgs(C, C, D),
            ChoiceArgs(D, D, D),
            ChoiceArgs(C, D, D),
            ChoiceArgs(D, D, D),
            ChoiceArgs(C, C, D),
            ChoiceArgs(D, C, D),
            ChoiceArgs(D, D, D),
            ChoiceArgs(C, D, D)
        }
    )
);

TEST_P(StrategyTest, test_vote_update)
{
    Matrix matrix;
    ProbabilityStrategy strategy(matrix);

    std::vector<ChoiceArgs> params_vector = GetParam();

    for (ChoiceArgs params : params_vector)
    {
        EXPECT_EQ(strategy.vote(), params.strategy_choice_);
        strategy.update(params.opponent1_choice_, params.opponent2_choice_);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}