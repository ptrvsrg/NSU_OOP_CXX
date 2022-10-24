#ifndef TASK2_GAME_H
#define TASK2_GAME_H

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "matrix.h"
#include "mode_creator.h"

class Game
{
public:
    void Launch(const std::vector<std::string> & strategy_names,
                const std::string & mode,
                int steps,
                const std::string & config_dir,
                const std::string & matrix_file);
};

#endif // TASK2_GAME_H
