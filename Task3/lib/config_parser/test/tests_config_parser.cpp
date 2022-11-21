#include <gtest/gtest.h>
#include "config_parser.h"

TEST(test_config_parser,
     check_constructor)
{
    EXPECT_THROW
    (
        {
            ConfigParser config_parser("files/non_existent.txt");
        },
        std::ios_base::failure
    );
}

struct ConfigParserArgs
{
    std::string file_;
    ConverterCommand cvt_cmd_;

    ConfigParserArgs(std::string file,
                     ConverterCommand cvt_cmd)
    : file_(std::move(file)),
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
            ConfigParserArgs("files/correct.txt",
                             {"mute", "23", "54" }),
            ConfigParserArgs("files/correct_with_comment.txt",
                             {"mute", "23", "84" }),
            ConfigParserArgs("files/only_comment.txt",
                             {})
        )
);

TEST_P(ConfigParserTest,
       check_get_converter_command)
{
    ConfigParserArgs params = GetParam();
    ConfigParser config_parser(params.file_);
    ConverterCommand cvt_cmd = config_parser.GetConverterCommand();

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