#ifndef TASK2_GAME_H
#define TASK2_GAME_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "matrix.h"
#include "detailed_mode.h"
#include "fast_mode.h"
#include "tournament_mode.h"

class Game
{
public:
    void Launch(std::vector<std::string> & strategy_names,
                std::string & modes,
                int & steps,
                std::string & lib_dir,
                std::string & config_dir,
                std::string & matrix_file);
private:
    Matrix matrix_;
};

#endif // TASK2_GAME_H
