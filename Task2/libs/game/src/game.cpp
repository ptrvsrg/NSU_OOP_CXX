#include "game.h"

StrategyCountException::StrategyCountException()
:   std::invalid_argument("Not enough strategies") {}

void Game::Launch(const std::vector<std::string> & strategy_names,
                  const std::string & mode,
                  int steps,
                  const std::string & config_dir,
                  const std::string & matrix_file)
{
    if (strategy_names.size() < 3) throw StrategyCountException();

    Matrix matrix;
    if (!matrix_file.empty()) matrix.Update(matrix_file);

    ModeCreator creator;
    const ModePtr process = creator.Create(strategy_names,
                                                   mode,
                                                   steps,
                                                   config_dir,
                                                   matrix);

    process->Launch();
}