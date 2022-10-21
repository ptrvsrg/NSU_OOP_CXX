#include "game.h"

void Game::Launch(std::vector<std::string> & strategy_names,
                  std::string & modes,
                  int & steps,
                  std::string & lib_dir,
                  std::string & config_dir,
                  std::string & matrix_file)
{
    if (strategy_names.size() < 3) throw std::invalid_argument("Not enough strategies");
    if (!matrix_file.empty()) matrix_.Update(matrix_file);

    Mode * process;
    if (modes == "detailed")
        process = new DetailedMode(strategy_names,
                                   steps,
                                   lib_dir,
                                   config_dir,
                                   matrix_);
    else if (modes == "fast")
        process = new FastMode(strategy_names,
                               steps,
                               lib_dir,
                               config_dir,
                               matrix_);
    else if (modes == "tournament")
        process = new TournamentMode(strategy_names,
                                     steps,
                                     lib_dir,
                                     config_dir,
                                     matrix_);
    else throw std::invalid_argument("Wrong modes");

    process->Launch();

    delete process;
}