#include "../include/cl_parser.h"

bool GetOptions(int argc,
                char ** argv,
                Options & opts)
{
    po::options_description desc("General options");
    desc.add_options()
        ("help,h", "Show options description")
        ("names,n", po::value<std::vector<std::string>>(&opts.strategy_name_)->multitoken(), "Strategy names")
        ("mode,m", po::value<std::string>(&opts.mode_), "Game mode")
        ("steps,s", po::value<int>(&opts.steps_), "Number of game steps")
        ("configs,c", po::value<std::string>(&opts.config_dir_), "Path to the directory with strategy configuration files")
        ("matrix,M", po::value<std::string>(&opts.matrix_file_), "Path to the file with game matrix");

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).run(),
              vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return false;
    }

    return true;
}
