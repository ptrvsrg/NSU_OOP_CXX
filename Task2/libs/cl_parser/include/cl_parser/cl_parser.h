#ifndef TASK2_CL_PARSER_H
#define TASK2_CL_PARSER_H

#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace po = boost::program_options;

struct Options
{
    std::vector<std::string> strategy_name_;
    std::string mode_;
    int steps_;
    std::string config_dir_;
    std::string matrix_file_;

    Options()
    :   mode_("detailed"),
        steps_(-1)
    {}
};

bool GetOptions(int argc,
                char ** argv,
                Options & opts);

#endif // TASK2_CL_PARSER_H
