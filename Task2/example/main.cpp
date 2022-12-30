#include <iostream>
#include "cl_parser.h"
#include "game.h"

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