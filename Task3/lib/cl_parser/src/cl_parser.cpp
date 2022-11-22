#include "cl_parser.h"
#include "cl_parser_errors.h"
#include <boost/program_options.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iomanip>
#include <iostream>

namespace po = boost::program_options;
namespace pt = boost::property_tree;

static void PrintConverterDesc()
{
    pt::ptree ptree;
    pt::read_json(CONVERTERS_CONFIG_FILE,
                  ptree);

    std::cout << "Available converters:" << std::endl;

    for (const auto & converter_info : ptree.get_child("Converters"))
        std::cout << "  " << std::setw(40) << std::left
                  << converter_info.second.get<std::string>("Command")
                  << converter_info.second.get<std::string>("Description") << std::endl;
}

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
        PrintConverterDesc();
        std::cout << std::endl << opts_desc << std::endl;
        return false;
    }

    if (opts.config_file_.empty())
        throw NoConfigFileException();
    if (opts.output_file_.empty())
        throw NoOutputFileException();
    if (opts.input_files_.empty())
        throw NoInputFilesException();

    return true;
}
