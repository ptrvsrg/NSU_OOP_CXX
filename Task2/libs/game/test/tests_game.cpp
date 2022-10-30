#include <gtest/gtest.h>
#include "game.h"

struct OptionArgs
{
    std::vector<std::string> strategy_name_;
    std::string mode_;
    int steps_ = -1;
    std::string config_dir_;
    std::string matrix_file_;
    std::string error_message_;

    OptionArgs(std::vector<std::string> strategy_name,
               std::string mode,
               int steps,
               std::string config_dir,
               std::string matrix_file,
               std::string error_message)
   :    strategy_name_(std::move(strategy_name)),
        mode_(std::move(mode)),
        steps_(steps),
        config_dir_(std::move(config_dir)),
        matrix_file_(std::move(matrix_file)),
        error_message_(std::move(error_message)) {}
};

class GameTest : public ::testing::TestWithParam<OptionArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_game,
    GameTest,
    ::testing::Values
        (
            OptionArgs({"strategy1", "strategy2"},
                       "detailed",
                       20,
                       "",
                       "",
                       "Not enough strategies")
        )
);

TEST_P(GameTest,
       test_launch)
{
    OptionArgs params = GetParam();
    Game game;

    EXPECT_THROW
    (
        {
            game.Launch(params.strategy_name_,
                        params.mode_,
                        params.steps_,
                        params.config_dir_,
                        params.matrix_file_);
        },
        StrategyCountException
    );
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}