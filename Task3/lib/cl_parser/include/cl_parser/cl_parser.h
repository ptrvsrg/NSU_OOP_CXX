#ifndef TASK2_CL_PARSER_H
#define TASK2_CL_PARSER_H

#include <string>
#include <vector>

struct Options
{
    std::vector<std::string> input_files_;
    std::string output_file_;
    std::string config_file_;

    Options() = default;
};

bool GetOptions(int argc,
                char ** argv,
                Options & opts);

#endif // TASK2_CL_PARSER_H
