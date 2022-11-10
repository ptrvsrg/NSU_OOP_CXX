#include "cl_parser.h"
#include "cl_parser_errors.h"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;
bool GetOptions(int argc,
                char ** argv,
                Options & opts)
{
    po::options_description opts_desc("General options");
    opts_desc.add_options()
        ("help,h",
         "Show options description")
        ("config,c",
         po::value<std::string>(&opts.config_file_),
         "Configuration file")
        ("output,O",
         po::value<std::string>(&opts.output_file_),
         "Output file")
        ("input,I",
         po::value<std::vector<std::string>>(&opts.input_files_)->multitoken(),
         "Input files");

    po::variables_map vm;
    po::parsed_options pars_opts = po::command_line_parser(argc,
                                                           argv)
        .options(opts_desc)
        .run();
    store(pars_opts,
              vm);
    notify(vm);

    if (vm.count("help"))
    {
        char * converter_desc = "Available Converters:\n"
                                "  mute <start> <end>       Mute the interval from the start time to the end"
                                "                           time\n"
                                "  mix <thread> <time>      Mix the main stream with the additional one starting"
                                "                           from the insertion time\n\n";
        std::cout << converter_desc << opts_desc << std::endl;
        return false;
    }

    if (opts.config_file_.empty()) throw NoConfigFileException();
    if (opts.output_file_.empty()) throw NoOutputFileException();
    if (opts.input_files_.empty()) throw NoInputFilesException();

    return true;
}
