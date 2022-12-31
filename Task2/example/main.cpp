#include <iostream>
#include "../lib/cl_parser/include/cl_parser.h"
#include "../lib/game/include/game.h"

int main(int argc, char ** argv)
{
    Options opts;
    if (!GetOptions(argc,
                    argv,
                    opts))
    {
        return EXIT_SUCCESS;
    }

    Game game;
    game.Launch(opts.strategy_name_,
                opts.mode_,
                opts.steps_,
                opts.config_dir_,
                opts.matrix_file_);

    return EXIT_SUCCESS;
}