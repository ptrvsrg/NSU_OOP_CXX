#include "fast_mode.h"

FastMode::FastMode(const std::vector<std::string> & strategy_names,
                   int steps,
                   const std::string & config_dir,
                   Matrix matrix)
: Mode(strategy_names,
       steps,
       config_dir,
       matrix) {}

void FastMode::Launch()
{
    CreateStrategies();

    for (int i = 0; i < steps_; ++i)
    {
        Trio<Choice> voting_result = GetVotingResults();
        UpdateStrategyData(voting_result);
        UpdateScores(voting_result);
    }

    PrintScores();
}

void FastMode::PrintScores()
{
    std::cout << std::setw(30) << std::left << "Strategies names"
              << std::setw(30) << std::left << "Final scores" << std::endl;

    for (int i = 0; i < 3; ++i)
    {
        std::cout << std::setw(30) << std::left << strategy_names_[i]
                  << std::setw(30) << std::left << scores_[i] << std::endl;
    }
}