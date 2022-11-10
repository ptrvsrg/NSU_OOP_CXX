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
               ExceptionType exception_type)
    :   argc_(static_cast<int>(args.size())),
        config_file_(std::move(config_file)),
        output_file_(std::move(output_file)),
        input_files_(std::move(input_files)),
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
            CommandLineParserArgs({"./main", "-c", "/home/", "-O", "/bin/", "-I", "/lib/", "/dev/"}, // 0
                                  "/home/",
                                  "/bin/",
                                  { "/lib/", "/dev/" },
                                  CommandLineParserArgs::ExceptionType::NO_EXCEPTION),
            CommandLineParserArgs({"./main", "-c/home/", "-O/bin/", "-I/lib/", "/dev/"}, // 1
                                  "/home/",
                                  "/bin/",
                                  { "/lib/", "/dev/" },
                                  CommandLineParserArgs::ExceptionType::NO_EXCEPTION),
            CommandLineParserArgs({"./main", "--config", "/home/", "--output", "/bin/", "--input", "/lib/", "/dev/"}, // 2
                                  "/home/",
                                  "/bin/",
                                  { "/lib/", "/dev/" },
                                  CommandLineParserArgs::ExceptionType::NO_EXCEPTION),
            CommandLineParserArgs({"./main", "--config=/home/", "--output=/bin/", "--input=/lib/", "/dev/"}, // 3
                                  "/home/",
                                  "/bin/",
                                  { "/lib/", "/dev/" },
                                  CommandLineParserArgs::ExceptionType::NO_EXCEPTION),

            CommandLineParserArgs({"./main", "-c/home/", "-O/bin/"}, // 4
                                  "/home/",
                                  "/bin/",
                                  {},
                                  CommandLineParserArgs::ExceptionType::NO_INPUT_FILES),

            CommandLineParserArgs({"./main", "-c/home/", "-I/bin/"}, // 5
                                  "/home/",
                                  "",
                                  { "/bin/" },
                                  CommandLineParserArgs::ExceptionType::NO_OUTPUT_FILE),

            CommandLineParserArgs({"./main", "-O/home/", "-I/bin/"}, // 6
                                  "",
                                  "/home/",
                                  { "/bin/" },
                                  CommandLineParserArgs::ExceptionType::NO_CONFIG_FILE)
        )
);

TEST_P(CommandLineParserTest,
       check_options)
{
    CommandLineParserArgs params = GetParam();
    Options opts;

    switch (params.exception_type_)
    {
        case CommandLineParserArgs::ExceptionType::NO_EXCEPTION:
            GetOptions(params.argc_,
                       params.argv_,
                       opts);

            EXPECT_EQ(opts.config_file_,
                      params.config_file_);
            EXPECT_EQ(opts.output_file_,
                      params.output_file_);
            EXPECT_EQ(opts.input_files_,
                      params.input_files_);
            break;
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

TEST(test_parser, check_help)
{
    std::streambuf * buf = std::cout.rdbuf();
    std::stringstream out_str;
    std::cout.rdbuf(out_str.rdbuf());

    char * argv[] = {
        "./main",
        "--help"
    };
    Options opts;
    GetOptions(sizeof(argv) / sizeof(*argv),
               argv,
               opts);

    EXPECT_STREQ(out_str.str().c_str(),
                 "Available Converters:\n"
                 "  mute <start> <end>       Mute the interval from the start time to the end"
                 "                           time\n"
                 "  mix <thread> <time>      Mix the main stream with the additional one starting"
                 "                           from the insertion time\n\n"
                 "General options:\n"
                 "  -h [ --help ]         Show options description\n"
                 "  -c [ --config ] arg   Configuration file\n"
                 "  -O [ --output ] arg   Output file\n"
                 "  -I [ --input ] arg    Input files\n\n");

    std::cout.rdbuf(buf);
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}