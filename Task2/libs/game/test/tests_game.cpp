#include "gtest/gtest.h"
#include "game.h"

struct Options
{
    std::vector<std::string> strategy_name_;
    std::string mode_;
    int steps_ = -1;
    std::string lib_dir_;
    std::string config_dir_;
    std::string matrix_file_;
    std::string error_message_;

    Options(std::vector<std::string> strategy_name,
            std::string mode,
            int steps,
            std::string lib_dir,
            std::string config_dir,
            std::string matrix_file,
            std::string error_message)
       : strategy_name_(strategy_name),
        mode_(mode),
        steps_(steps),
        lib_dir_(lib_dir),
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
                    "",
                    "Not enough strategies"),
            Options({"strategy1", "strategy2", "strategy3"},
                    "career",
                    20,
                    "",
                    "",
                    "",
                    "Wrong modes"),
            Options({"strategy1", "strategy2", "strategy3"},
                    "detailed",
                    20,
                    "/home/",
                    "/home/",
                    "/home/acer/NSU_OOP_CXX/Task2/tests/wrong_matrix0.txt",
                    "/home/acer/NSU_OOP_CXX/Task2/tests/wrong_matrix0.txt : File opening error"),
            Options({"strategy1", "strategy2", "strategy3"},
                    "detailed",
                    20,
                    "/home/",
                    "/home/",
                    "/home/acer/NSU_OOP_CXX/Task2/tests/wrong_matrix1.txt",
                    "/home/acer/NSU_OOP_CXX/Task2/tests/wrong_matrix1.txt : Wrong matrix"),
            Options({"strategy1", "strategy2", "strategy3"},
                    "detailed",
                    20,
                    "/home/",
                    "/home/",
                    "/home/acer/NSU_OOP_CXX/Task2/tests/wrong_matrix2.txt",
                    "/home/acer/NSU_OOP_CXX/Task2/tests/wrong_matrix2.txt : Wrong matrix")
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
                    params.lib_dir_,
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