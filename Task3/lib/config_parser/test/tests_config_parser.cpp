#include <gtest/gtest.h>
#include "config_parser.h"
#include "config_parser_errors.h"

std::string test_dir = "/home/acer/NSU_OOP_CXX/Task3/lib/config_parser/test/files/";

TEST(test_config_parser,
     check_constructor)
{
    EXPECT_THROW
    (
        {
            ConfigParser config_parser(test_dir + "non_existent.txt");
        },
        std::ios_base::failure
    );
}

struct ConfigParserArgs
{
    std::string file_;
    std::vector<std::string> cvt_cmd_;
    bool exception_;

    ConfigParserArgs(std::string file,
                     std::vector<std::string> cvt_cmd,
                     bool exception)
    : file_(std::move(file)),
      cvt_cmd_(std::move(cvt_cmd)),
      exception_(exception)
    {}
};

class ConfigParserTest : public ::testing::TestWithParam<ConfigParserArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_config_parser,
    ConfigParserTest,
    ::testing::Values
        (
            ConfigParserArgs(test_dir + "correct.txt",
                             {"mute", "23", "54" },
                             false),
            ConfigParserArgs(test_dir + "correct_with_comment.txt",
                             {"mute", "23", "84" },
                             false),
            ConfigParserArgs(test_dir + "only_comment.txt",
                             {},
                             false),
            ConfigParserArgs(test_dir + "incorrect_link.txt",
                             {},
                             true),
            ConfigParserArgs(test_dir + "incorrect_params.txt",
                             {},
                             true)
        )
);

TEST_P(ConfigParserTest,
       check_get_converter_command)
{
    ConfigParserArgs params = GetParam();
    ConfigParser config_parser(params.file_);
    std::vector<std::string> cvt_cmd;

    if (params.exception_)
    {
        EXPECT_THROW
        (
            {
                cvt_cmd = config_parser.GetConverterCommand();
            },
            IncorrectParamsException
        );
        return;
    }

    EXPECT_NO_THROW
    (
        {
            cvt_cmd = config_parser.GetConverterCommand();
        }
    );
    EXPECT_EQ(params.cvt_cmd_,
              cvt_cmd);
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}