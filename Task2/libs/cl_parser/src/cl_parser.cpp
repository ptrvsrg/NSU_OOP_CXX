#include "cl_parser.h"

bool GetOptions(int argc, char ** argv,
                std::vector<std::string> & strategyName,
                std::string & mode,
                int & steps,
                std::string & libDir,
                std::string & configDir,
                std::string & matrixFile)
{
    po::options_description desc("General options");
    desc.add_options()
        ("help,h", "Show options description")
        ("names,n", po::value<std::vector<std::string>>(&strategyName)->multitoken(), "Strategy names")
        ("modes,m", po::value<std::string>(&mode), "Game modes")
        ("steps,s", po::value<int>(&steps)->default_value(-1), "Number of game steps")
        ("libs,l", po::value<std::string>(&libDir), "Path to the directory with strategy strategy dynamic libraries")
        ("configs,c", po::value<std::string>(&configDir), "Path to the directory with strategy configuration files")
        ("matrix,M", po::value<std::string>(&matrixFile), "Path to the file with game matrix");

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return false;
    }

    return true;
}
