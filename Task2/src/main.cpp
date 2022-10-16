#include <iostream>
#include "cl_parser.h"
#include "game.h"

int main(int argc, char ** argv)
{
    std::vector<std::string> strategy_names;
    std::string mode;
    int steps;
    std::string lib_dir;
    std::string config_dir;
    std::string matrix_file;

    if (!GetOptions(argc, argv,
               strategy_names,
               mode,
               steps,
               lib_dir,
               config_dir,
               matrix_file))
    {
        return EXIT_SUCCESS;
    }

    Game game;
    game.Launch(strategy_names,
                mode,
                steps,
                lib_dir,
                config_dir,
                matrix_file);

    return EXIT_SUCCESS;
}