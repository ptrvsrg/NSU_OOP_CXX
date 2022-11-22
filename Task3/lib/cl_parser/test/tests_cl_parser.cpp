#include <gtest/gtest.h>
#include "cl_parser.h"
#include "cl_parser_errors.h"

struct CommandLineParserArgs
{
    int argc_;
    char ** argv_;
    std::string config_file_;
    std::string output_file_;
    std::vector<std::string> input_files_;
    bool return_value_;
    enum class ExceptionType
    {
        NO_EXCEPTION,
        NO_CONFIG_FILE,
        NO_OUTPUT_FILE,
        NO_INPUT_FILES
    } exception_type_;

    CommandLineParserArgs(std::initializer_list<std::string> args,
               std::string config_file,
               std::string output_file,
               std::vector<std::string> input_files,
               bool return_value,
               ExceptionType exception_type)
    :   argc_(static_cast<int>(args.size())),
        config_file_(std::move(config_file)),
        output_file_(std::move(output_file)),
        input_files_(std::move(input_files)),
        return_value_(return_value),
        exception_type_(exception_type)
    {
        argv_ = new char * [argc_];
        for (int i = 0; i < argc_; ++i)
        {
            argv_[i] = new char [(args.begin() + i)->size()];
            strcpy(argv_[i],
                   (args.begin() + i)->data());
        }
    }
};

class CommandLineParserTest : public ::testing::TestWithParam<CommandLineParserArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_command_line_parser,
    CommandLineParserTest,
    ::testing::Values
        (
            CommandLineParserArgs({"./main", "-c", "/home/", "-O", "/bin/", "-I", "/lib/", "/dev/"},
                                  "/home/",
                                  "/bin/",
                                  { "/lib/", "/dev/" },
                                  true,
                                  CommandLineParserArgs::ExceptionType::NO_EXCEPTION),
            CommandLineParserArgs({"./main", "-c/home/", "-O/bin/", "-I/lib/", "/dev/"},
                                  "/home/",
                                  "/bin/",
                                  { "/lib/", "/dev/" },
                                  true,
                                  CommandLineParserArgs::ExceptionType::NO_EXCEPTION),
            CommandLineParserArgs({"./main", "--config", "/home/", "--output", "/bin/", "--input", "/lib/", "/dev/"},
                                  "/home/",
                                  "/bin/",
                                  { "/lib/", "/dev/" },
                                  true,
                                  CommandLineParserArgs::ExceptionType::NO_EXCEPTION),
            CommandLineParserArgs({"./main", "--config=/home/", "--output=/bin/", "--input=/lib/", "/dev/"},
                                  "/home/",
                                  "/bin/",
                                  { "/lib/", "/dev/" },
                                  true,
                                  CommandLineParserArgs::ExceptionType::NO_EXCEPTION),
            CommandLineParserArgs({"./main", "-h"},
                                  "",
                                  "",
                                  {},
                                  false,
                                  CommandLineParserArgs::ExceptionType::NO_EXCEPTION),
            CommandLineParserArgs({"./main", "--help"},
                                  "",
                                  "",
                                  {},
                                  false,
                                  CommandLineParserArgs::ExceptionType::NO_EXCEPTION),

            CommandLineParserArgs({"./main", "-c/home/", "-O/bin/"},
                                  "/home/",
                                  "/bin/",
                                  {},
                                  false,
                                  CommandLineParserArgs::ExceptionType::NO_INPUT_FILES),

            CommandLineParserArgs({"./main", "-c/home/", "-I/bin/"},
                                  "/home/",
                                  "",
                                  { "/bin/" },
                                  false,
                                  CommandLineParserArgs::ExceptionType::NO_OUTPUT_FILE),

            CommandLineParserArgs({"./main", "-O/home/", "-I/bin/"},
                                  "",
                                  "/home/",
                                  { "/bin/" },
                                  false,
                                  CommandLineParserArgs::ExceptionType::NO_CONFIG_FILE),

            CommandLineParserArgs({"./main", "-O/home/", "-I/bin/"},
                                  "",
                                  "/home/",
                                  { "/bin/" },
                                  false,
                                  CommandLineParserArgs::ExceptionType::NO_CONFIG_FILE)
        )
);

TEST_P(CommandLineParserTest,
       check_get_options)
{
    CommandLineParserArgs params = GetParam();
    Options opts;

    switch (params.exception_type_)
    {
        case CommandLineParserArgs::ExceptionType::NO_EXCEPTION:
        {
            bool return_value = GetOptions(params.argc_,
                                           params.argv_,
                                           opts);
            EXPECT_EQ(return_value,
                      params.return_value_);

            if (params.return_value_) {
                EXPECT_EQ(opts.config_file_,
                          params.config_file_);
                EXPECT_EQ(opts.output_file_,
                          params.output_file_);
                EXPECT_EQ(opts.input_files_,
                          params.input_files_);
            }
            break;
        }
        case CommandLineParserArgs::ExceptionType::NO_CONFIG_FILE:
            EXPECT_THROW(
            {
                    GetOptions(params.argc_,
                               params.argv_,
                               opts);
                },
                NoConfigFileException
            );
            break;
        case CommandLineParserArgs::ExceptionType::NO_OUTPUT_FILE:
            EXPECT_THROW(
            {
                    GetOptions(params.argc_,
                               params.argv_,
                               opts);
                },
                NoOutputFileException
            );
            break;
        case CommandLineParserArgs::ExceptionType::NO_INPUT_FILES:
            EXPECT_THROW(
            {
                    GetOptions(params.argc_,
                               params.argv_,
                               opts);
                },
                NoInputFilesException
            );
            break;
    }
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}