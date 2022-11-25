#include <gtest/gtest.h>
#include <boost/program_options.hpp>
#include "cl_parser.h"

struct CommandLineParserArgs
{
    int argc_;
    char ** argv_;
    std::string config_file_;
    std::string output_file_;
    std::vector<std::string> input_files_;
    bool return_value_;
    bool exception_;

    CommandLineParserArgs(std::initializer_list<std::string> args,
               std::string config_file,
               std::string output_file,
               std::vector<std::string> input_files,
               bool return_value,
               bool exception)
    :   argc_(static_cast<int>(args.size())),
        config_file_(std::move(config_file)),
        output_file_(std::move(output_file)),
        input_files_(std::move(input_files)),
        return_value_(return_value),
        exception_(exception)
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
                                  false),
            CommandLineParserArgs({"./main", "-c/home/", "-O/bin/", "-I/lib/", "/dev/"},
                                  "/home/",
                                  "/bin/",
                                  { "/lib/", "/dev/" },
                                  true,
                                  false),
            CommandLineParserArgs({"./main", "--config", "/home/", "--output", "/bin/", "--input", "/lib/", "/dev/"},
                                  "/home/",
                                  "/bin/",
                                  { "/lib/", "/dev/" },
                                  true,
                                  false),
            CommandLineParserArgs({"./main", "--config=/home/", "--output=/bin/", "--input=/lib/", "/dev/"},
                                  "/home/",
                                  "/bin/",
                                  { "/lib/", "/dev/" },
                                  true,
                                  false),
            CommandLineParserArgs({"./main", "-h"},
                                  "",
                                  "",
                                  {},
                                  false,
                                  false),
            CommandLineParserArgs({"./main", "--help"},
                                  "",
                                  "",
                                  {},
                                  false,
                                  false),

            CommandLineParserArgs({"./main", "-c/home/", "-O/bin/"},
                                  "/home/",
                                  "/bin/",
                                  {},
                                  false,
                                  true),

            CommandLineParserArgs({"./main", "-c/home/", "-I/bin/"},
                                  "/home/",
                                  "",
                                  { "/bin/" },
                                  false,
                                  true),

            CommandLineParserArgs({"./main", "-O/home/", "-I/bin/"},
                                  "",
                                  "/home/",
                                  { "/bin/" },
                                  false,
                                  true),

            CommandLineParserArgs({"./main", "-O/home/", "-I/bin/"},
                                  "",
                                  "/home/",
                                  { "/bin/" },
                                  false,
                                  true)
        )
);

TEST_P(CommandLineParserTest,
       check_get_options)
{
    CommandLineParserArgs params = GetParam();
    Options opts;

    if (!params.exception_)
    {
        bool return_value = GetOptions(params.argc_,
                                       params.argv_,
                                       opts);
        EXPECT_EQ(return_value,
                  params.return_value_);

        if (params.return_value_) 
        {
            EXPECT_EQ(opts.config_file_,
                      params.config_file_);
            EXPECT_EQ(opts.output_file_,
                      params.output_file_);
            EXPECT_EQ(opts.input_files_,
                      params.input_files_);
        }
    }
    else
        EXPECT_THROW
        (
            {
                GetOptions(params.argc_,
                           params.argv_,
                           opts);
            },
            boost::wrapexcept<boost::program_options::required_option>
        );
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}