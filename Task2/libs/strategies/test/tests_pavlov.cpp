#include <gtest/gtest.h>
#include "pavlov.h"

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

TEST(test_pavlov,
     test_constructors)
{
    EXPECT_THROW
    (
        {
            PavlovStrategy strategy(
                "/home/acer/NSU_OOP_CXX/Task2/libs/strategies/tit_for_tat_with_forgiveness/test/");
        },
        boost::property_tree::json_parser_error
    );
}

class PavlovStrategyTest : public ::testing::TestWithParam<std::vector<ChoiceArgs>> {};
INSTANTIATE_TEST_SUITE_P
(
    test_pavlov,
    PavlovStrategyTest,
    ::testing::Values
        (
            // Tit for tat case
            std::vector<ChoiceArgs>{
                ChoiceArgs(C, C, C),
                ChoiceArgs(C, C, C),
                ChoiceArgs(C, C, C),
                ChoiceArgs(C, C, C),
                ChoiceArgs(C, C, C),
                ChoiceArgs(C, C, C),

                ChoiceArgs(C, D, C),
                ChoiceArgs(C, D, D),
                ChoiceArgs(C, C, D),
                ChoiceArgs(D, D, C),
                ChoiceArgs(C, D, D),
                ChoiceArgs(D, D, D)
            },

            // Suspicious tit for tat case
            std::vector<ChoiceArgs>{
                ChoiceArgs(D, C, C),
                ChoiceArgs(C, C, D),
                ChoiceArgs(D, C, C),
                ChoiceArgs(C, C, D),
                ChoiceArgs(D, C, C),
                ChoiceArgs(D, C, D),

                ChoiceArgs(C, C, C),
                ChoiceArgs(C, C, C),
                ChoiceArgs(C, D, C),
                ChoiceArgs(D, C, D),
                ChoiceArgs(C, C, D),
                ChoiceArgs(C, C, C)
            },

            // Always defect
            std::vector<ChoiceArgs>{
                ChoiceArgs(D, D, C),
                ChoiceArgs(C, D, D),
                ChoiceArgs(D, D, D),
                ChoiceArgs(C, C, D),
                ChoiceArgs(D, D, C),
                ChoiceArgs(C, D, D),

                ChoiceArgs(C, D, D),
                ChoiceArgs(D, D, D),
                ChoiceArgs(C, C, D),
                ChoiceArgs(D, D, D),
                ChoiceArgs(C, D, D),
                ChoiceArgs(D, D, D)
            },

            // Random
            std::vector<ChoiceArgs>{
                ChoiceArgs(C, C, C),
                ChoiceArgs(C, C, C),
                ChoiceArgs(C, C, C),
                ChoiceArgs(C, C, C),
                ChoiceArgs(D, C, C),
                ChoiceArgs(C, C, D),

                ChoiceArgs(C, D, D),
                ChoiceArgs(D, C, D),
                ChoiceArgs(D, D, D),
                ChoiceArgs(D, D, D),
                ChoiceArgs(C, D, D),
                ChoiceArgs(D, D, D)
            }
        )
);

TEST_P(PavlovStrategyTest, test_vote_update)
{
    PavlovStrategy strategy("/home/acer/NSU_OOP_CXX/Task2/config/");
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