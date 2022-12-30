#include <gtest/gtest.h>
#include "tit_for_tat_with_forgiveness.h"

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

TEST(test_tit_for_tat_with_forgiveness,
     test_constructors)
{
    EXPECT_THROW(
        {
            TitForTatWithForgivenessStrategy strategy("./");
        },
        boost::property_tree::json_parser_error
    );

    try
    {
        TitForTatWithForgivenessStrategy strategy("incorrect_config1/");
    }
    catch(const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(),
                     "Wrong forgiveness percentage");
    }

    try
    {
        TitForTatWithForgivenessStrategy strategy("incorrect_config2/");
    }
    catch(const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(),
                     "Wrong forgiveness percentage");
    }
}

class TitForTatWithForgivenessStrategyTest : public ::testing::TestWithParam<std::vector<ChoiceArgs>> {};
INSTANTIATE_TEST_SUITE_P
(
    test_tit_for_tat_with_forgiveness,
    TitForTatWithForgivenessStrategyTest,
    ::testing::Values
        (
            std::vector<ChoiceArgs>{
                ChoiceArgs(D, C, C),
                ChoiceArgs(C, D, D),
                ChoiceArgs(D, D, D),
                ChoiceArgs(C, C, C), // forgiveness
                ChoiceArgs(C, C, C),
                ChoiceArgs(C, D, C),
                ChoiceArgs(D, D, D),
                ChoiceArgs(C, C, D),
                ChoiceArgs(C, C, C),
                ChoiceArgs(C, D, C),
                ChoiceArgs(C, C, C)  // forgiveness
            }
        )
);

TEST_P(TitForTatWithForgivenessStrategyTest,
       test_vote_update)
{
    TitForTatWithForgivenessStrategy strategy("correct_config/");
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