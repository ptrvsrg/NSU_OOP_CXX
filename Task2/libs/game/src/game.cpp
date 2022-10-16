#include "game.h"

void Game::Launch(std::vector<std::string> & strategy_names,
                  std::string & modes,
                  int & steps,
                  std::string & lib_dir,
                  std::string & config_dir,
                  std::string & matrix_file)
{
    if (strategy_names.size() < 3) throw std::invalid_argument("Not enough strategies");
    if (!matrix_file.empty()) UpdateMatrix(matrix_file);

    Mode * process;
    if (modes == "detailed")
    {
        process = new DetailedMode;
    }
    else if (modes == "fast")
    {
        process = new FastMode;
    }
    else if (modes == "tournament")
    {
        process = new TournamentMode;
    }
    else throw std::invalid_argument("Wrong modes");


    process->Init(strategy_names,
                  steps,
                  lib_dir,
                  config_dir,
                  matrix_);
    process->Launch();

    delete process;
}

void Game::UpdateMatrix(std::string matrix_file)
{
    std::ifstream inFile(matrix_file, std::ios::in);
    if (!inFile.is_open())
    {
        throw std::invalid_argument(matrix_file + " : File opening error");
    }

    int row = 0;
    while (!inFile.eof())
    {
        if (row == 8)
        {
            throw std::invalid_argument(matrix_file + " : Wrong matrix_");
        }

        inFile >> matrix_[row][0] >> matrix_[row][1] >> matrix_[row][2];
        ++row;
    }
}