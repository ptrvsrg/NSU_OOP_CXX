#include "fast_mode.h"

void FastMode::Launch()
{
    LoadStrategies();

    for (int i = 0; i < steps_; ++i)
    {
        Trio<Choice> voting_result = GetVotingResults();
        UpdateStrategies(voting_result);
        UpdateScores(voting_result);
    }

    PrintScores();
    ClearStrategies();
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