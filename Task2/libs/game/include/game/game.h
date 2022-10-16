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
    Matrix<int, 8, 3> matrix_ = {{
        { 4, 4, 4, },
        { 3, 3, 9, },
        { 3, 9, 3, },
        { 0, 5, 5, },
        { 9, 3, 3, },
        { 5, 0, 5, },
        { 5, 5, 0, },
        { 1, 1, 1, }
    }};

    void UpdateMatrix(std::string matrix_file);
};

#endif // TASK2_GAME_H
