#ifndef TASK2_CL_PARSER_H
#define TASK2_CL_PARSER_H

#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace po = boost::program_options;

bool GetOptions(int argc, char ** argv,
                std::vector<std::string> & strategyName,
                std::string & mode,
                int & steps,
                std::string & libDir,
                std::string & configDir,
                std::string & matrixFile);

#endif // TASK2_CL_PARSER_H
