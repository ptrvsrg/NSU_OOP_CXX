#include <gtest/gtest.h>
#include "cl_parser.h"

struct ParserArgs
{
    int argc_;
    char ** argv_;
    std::vector<std::string> strategy_name_;
    std::string mode_;
    int steps_ = -1;
    std::string config_dir_;
    std::string matrix_file_;
    bool exception_;

    ParserArgs(std::initializer_list<std::string> args,
               std::vector<std::string> strategy_name,
               std::string mode,
               int steps,
               std::string config_dir,
               std::string matrix_file,
               bool exception)
    :   argc_(static_cast<int>(args.size())),
        strategy_name_(std::move(strategy_name)),
        mode_(mode),
        steps_(steps),
        config_dir_(std::move(config_dir)),
        matrix_file_(std::move(matrix_file)),
        exception_(exception)
    {
        argv_ = new char * [argc_];
        for (int i = 0; i < argc_; ++i)
        {
            argv_[i] = new char [(args.begin() + i)->size()];
            strcpy(argv_[i], (args.begin() + i)->data());
        }
    }
};

class ParserTest : public ::testing::TestWithParam<ParserArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_parser,
    ParserTest,
    ::testing::Values
        (
            ParserArgs({"./main", "--names", "player1", "player2", "player3"},
                       std::vector<std::string>({"player1", "player2", "player3"}),
                       std::string("detailed"),
                       -1,
                       std::string(""),
                       std::string(""),
                       false),
            ParserArgs({"./main", "-n", "player1", "player2", "player3"},
                       std::vector<std::string>({"player1", "player2", "player3"}),
                       std::string("detailed"),
                       -1,
                       std::string(""),
                       std::string(""),
                       false),
            ParserArgs({"./main", "--modes=fast"},
                       std::vector<std::string>(),
                       std::string("fast"),
                       -1,
                       std::string(""),
                       std::string(""),
                       false),
            ParserArgs({"./main", "-mfast"},
                       std::vector<std::string>(),
                       std::string("fast"),
                       -1,
                       std::string(""),
                       std::string(""),
                       false),
            ParserArgs({"./main", "--steps=15"},
                       std::vector<std::string>(),
                       std::string("detailed"),
                       15,
                       std::string(""),
                       std::string(""),
                       false),
            ParserArgs({"./main", "--steps=-15"},
                       std::vector<std::string>(),
                       std::string("detailed"),
                       -15,
                       std::string(""),
                       std::string(""),
                       false),
            ParserArgs({"./main", "-s15"},
                       std::vector<std::string>(),
                       std::string("detailed"),
                       15,
                       std::string(""),
                       std::string(""),
                       false),
            ParserArgs({"./main", "--configs=/home/"},
                       std::vector<std::string>(),
                       std::string("detailed"),
                       -1,
                       std::string("/home/"),
                       std::string(""),
                       false),
            ParserArgs({"./main", "-c/home/"},
                       std::vector<std::string>(),
                       std::string("detailed"),
                       -1,
                       std::string("/home/"),
                       std::string(""),
                       false),
            ParserArgs({"./main", "--matrix=/home/matrix.txt"},
                       std::vector<std::string>(),
                       std::string("detailed"),
                       -1,
                       std::string(""),
                       std::string("/home/matrix.txt"),
                       false),
            ParserArgs({"./main", "-M/home/matrix.txt"},
                       std::vector<std::string>(),
                       std::string("detailed"),
                       -1,
                       std::string(""),
                       std::string("/home/matrix.txt"),
                       false),
            ParserArgs({"./main", "--help"},
                       std::vector<std::string>(),
                       std::string("detailed"),
                       -1,
                       std::string(""),
                       std::string(""),
                       false),
            ParserArgs({"./main", "-h"},
                       std::vector<std::string>(),
                       std::string("detailed"),
                       -1,
                       std::string(""),
                       std::string(""),
                       false),
            ParserArgs({"./main", "-r"},
                       std::vector<std::string>(),
                       std::string("detailed"),
                       -1,
                       std::string(""),
                       std::string(""),
                       true),
            ParserArgs({"./main", "--auto"},
                       std::vector<std::string>(),
                       std::string("detailed"),
                       -1,
                       std::string(""),
                       std::string(""),
                       true),
            ParserArgs({"./main", "--theme=dark"},
                       std::vector<std::string>(),
                       std::string("detailed"),
                       -1,
                       std::string(""),
                       std::string(""),
                       true)
        )
);

TEST_P(ParserTest, check_options)
{
    ParserArgs params = GetParam();
    OptionArgs opts;

    if (params.exception_)
    {
        EXPECT_THROW(
            {
                GetOptions(params.argc_,
                           params.argv_,
                           opts);
            },
            std::exception
        );
        return;
    }

    GetOptions(params.argc_,
               params.argv_,
               opts);

    EXPECT_EQ(opts.strategy_name_,
              params.strategy_name_);
    EXPECT_EQ(opts.mode_,
              params.mode_);
    EXPECT_EQ(opts.steps_,
              params.steps_);
    EXPECT_EQ(opts.config_dir_,
              params.config_dir_);
    EXPECT_EQ(opts.matrix_file_,
              params.matrix_file_);
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}