#include "cl_parser.h"
#include <boost/program_options.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iomanip>
#include <iostream>
#include <regex>

namespace po = boost::program_options;
namespace pt = boost::property_tree;

static void PrintConverterDesc()
{
    // Get converter source dirs
    std::string converter_source_dirs(CONVERTER_SOURCE_DIRS);
    std::regex delim(";");
    std::vector<std::string> converter_source_dir_vector
        (std::sregex_token_iterator(converter_source_dirs.begin(),
                                    converter_source_dirs.end(),
                                    delim,
                                    -1),
         std::sregex_token_iterator());

    std::cout << "Available converter:" << std::endl;

    for (const std::string & converter_source_dir : converter_source_dir_vector)
    {
        // Create property tree
        pt::ptree ptree;
        pt::read_json(converter_source_dir + "/config/converter_desc.json",
                      ptree);

        // print converter descriptions
        std::cout << "  " << std::setw(40) << std::left
                  << ptree.get_child("Command").data()
                  << ptree.get_child("Description").data() << std::endl;
    }

    std::cout << std::endl;
}

bool GetOptions(int argc,
                char ** argv,
                Options & opts)
{
    // add necessary options
    po::options_description opts_desc("General options");
    opts_desc.add_options()
        ("help,h",
         "Show options description")
        ("config,c",
         po::value<std::string>(&opts.config_file_)->required(),
         "Configuration file")
        ("output,O",
         po::value<std::string>(&opts.output_file_)->required(),
         "Output file")
        ("input,I",
         po::value<std::vector<std::string>>(&opts.input_files_)->multitoken()->required(),
         "Input files");

    // parse command line arguments
    po::variables_map vm;
    po::parsed_options pars_opts = po::command_line_parser(argc,
                                                           argv)
        .options(opts_desc)
        .run();
    store(pars_opts,
              vm);

    // print help
    if (vm.count("help"))
    {
        PrintConverterDesc();
        std::cout << opts_desc << std::endl;
        return false;
    }

    //
    notify(vm);
    return true;
}
