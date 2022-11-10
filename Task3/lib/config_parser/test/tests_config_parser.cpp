#include <gtest/gtest.h>
#include "config_parser.h"
#include "config_parser_errors.h"

std::string test_dir = "/home/acer/NSU_OOP_CXX/Task3/lib/config_parser/test/files/";

TEST(test_config_parser, check_constructor)
{
    EXPECT_THROW
    (
        {
            ConfigParser config_parser(test_dir + "non_existent.txt");
        },
        OpeningException
    );
}

struct ConfigParserArgs
{
    std::string file_;
    ConverterCommand cvt_cmd_;
    bool status_;

    ConfigParserArgs(std::string file,
                     ConverterCommand cvt_cmd,
                     bool status)
    :   file_(std::move(file)),
        status_(status),
        cvt_cmd_(std::move(cvt_cmd))
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
                             ConverterCommand("mute", { "23", "54" }),
                             true),
            ConfigParserArgs(test_dir + "correct_with_comment.txt",
                             ConverterCommand("mute", { "23", "84" }),
                             true),
            ConfigParserArgs(test_dir + "only_comment.txt",
                             ConverterCommand(),
                             false)
        )
);

TEST_P(ConfigParserTest, check_get_converter_command)
{
    ConfigParserArgs params = GetParam();
    ConfigParser config_parser(params.file_);
    ConverterCommand cvt_cmd;
    bool status = config_parser.GetConverterCommand(cvt_cmd);

    EXPECT_EQ(status,
              params.status_);
    EXPECT_EQ(params.cvt_cmd_.converter_,
              cvt_cmd.converter_);
    EXPECT_EQ(params.cvt_cmd_.params_,
              cvt_cmd.params_);
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}