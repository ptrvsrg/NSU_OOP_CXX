#include "gtest/gtest.h"
#include "game.h"

struct Options
{
    std::vector<std::string> strategy_name_;
    std::string mode_;
    int steps_ = -1;
    std::string config_dir_;
    std::string matrix_file_;
    std::string error_message_;

    Options(std::vector<std::string> strategy_name,
            std::string mode,
            int steps,
            std::string config_dir,
            std::string matrix_file,
            std::string error_message)
       : strategy_name_(strategy_name),
        mode_(mode),
        steps_(steps),
        config_dir_(config_dir),
        matrix_file_(matrix_file),
        error_message_(error_message) {}
};

class GameTest : public ::testing::TestWithParam<Options> {};
INSTANTIATE_TEST_SUITE_P
(
    test_game,
    GameTest,
    ::testing::Values
        (
            Options({"strategy1", "strategy2"},
                    "detailed",
                    20,
                    "",
                    "",
                    "Not enough strategies")
        )
);

TEST_P(GameTest, launch_exceptions)
{
    Options params = GetParam();
    Game game;

    try
    {
        game.Launch(params.strategy_name_,
                    params.mode_,
                    params.steps_,
                    params.config_dir_,
                    params.matrix_file_);
    }
    catch (const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(), params.error_message_.c_str());
        return;
    }

    FAIL();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}