#include <gtest/gtest.h>
#include <sstream>
#include "cl_parser.h"

struct ParserArgs
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

    ParserArgs(std::initializer_list<std::string> args,
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

class ParserTest : public ::testing::TestWithParam<ParserArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_parser,
    ParserTest,
    ::testing::Values
        (
            ParserArgs({"./main", "-c", "/home/", "-O", "/bin/", "-I", "/lib/", "/dev/"}, // 0
                       "/home/",
                       "/bin/",
                       { "/lib/", "/dev/" },
                       ParserArgs::ExceptionType::NO_EXCEPTION),
            ParserArgs({"./main", "-c/home/", "-O/bin/", "-I/lib/", "/dev/"}, // 1
                       "/home/",
                       "/bin/",
                       { "/lib/", "/dev/" },
                       ParserArgs::ExceptionType::NO_EXCEPTION),
            ParserArgs({"./main", "--config", "/home/", "--output", "/bin/", "--input", "/lib/", "/dev/"}, // 2
                       "/home/",
                       "/bin/",
                       { "/lib/", "/dev/" },
                       ParserArgs::ExceptionType::NO_EXCEPTION),
            ParserArgs({"./main", "--config=/home/", "--output=/bin/", "--input=/lib/", "/dev/"}, // 3
                       "/home/",
                       "/bin/",
                       { "/lib/", "/dev/" },
                       ParserArgs::ExceptionType::NO_EXCEPTION),

            ParserArgs({"./main", "-c/home/", "-O/bin/"}, // 4
                       "/home/",
                       "/bin/",
                       {},
                       ParserArgs::ExceptionType::NO_INPUT_FILES),

            ParserArgs({"./main", "-c/home/", "-I/bin/"}, // 5
                       "/home/",
                       "",
                       { "/bin/" },
                       ParserArgs::ExceptionType::NO_OUTPUT_FILE),

            ParserArgs({"./main", "-O/home/", "-I/bin/"}, // 6
                       "",
                       "/home/",
                       { "/bin/" },
                       ParserArgs::ExceptionType::NO_CONFIG_FILE)
        )
);

TEST_P(ParserTest,
       check_options)
{
    ParserArgs params = GetParam();
    Options opts;

    switch (params.exception_type_)
    {
        case ParserArgs::ExceptionType::NO_EXCEPTION:
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
        case ParserArgs::ExceptionType::NO_CONFIG_FILE:
            EXPECT_THROW(
                {
                    GetOptions(params.argc_,
                               params.argv_,
                               opts);
                },
                NoConfigFileError
            );
            break;
        case ParserArgs::ExceptionType::NO_OUTPUT_FILE:
            EXPECT_THROW(
                {
                    GetOptions(params.argc_,
                               params.argv_,
                               opts);
                },
                NoOutputFileError
            );
            break;
        case ParserArgs::ExceptionType::NO_INPUT_FILES:
            EXPECT_THROW(
                {
                    GetOptions(params.argc_,
                               params.argv_,
                               opts);
                },
                NoInputFilesError
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