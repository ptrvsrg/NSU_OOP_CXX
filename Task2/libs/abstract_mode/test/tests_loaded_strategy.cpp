#include "gtest/gtest.h"
#include "loaded_strategy.h"

struct Options
{
    std::string strategy_name_;
    std::string lib_dir_;
    std::string config_dir_;
    std::string error_message_;

    Options(std::string strategy_name,
            std::string lib_dir,
            std::string config_dir,
            std::string error_message)
       : strategy_name_(strategy_name),
        lib_dir_(lib_dir),
        config_dir_(config_dir),
        error_message_(error_message) {}
};

class GameTest : public ::testing::TestWithParam<Options> {};
INSTANTIATE_TEST_SUITE_P
(
    test_game,
    GameTest,
    ::testing::Values
        (
            Options("strategy1",
                    "",
                    "",
                    "strategy1.so: cannot open shared object file: No such file or directory"),
            Options("random",
                    "/home/acer/NSU_OOP_CXX/Task2/tests/",
                    "",
                    "/home/acer/NSU_OOP_CXX/Task2/tests/random.so: undefined symbol: CreateStrategy")
        )
);

TEST_P(GameTest, launch_exceptions)
{
    Options params = GetParam();
    Matrix matrix_;

    try
    {

        LoadedStrategy strategy(params.strategy_name_,
                                params.lib_dir_,
                                params.config_dir_,
                                matrix_);
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