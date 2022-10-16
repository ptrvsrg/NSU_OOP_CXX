#include "fast_mode.h"

void FastMode::Launch()
{
    for (int i = 0; i < steps_; ++i)
    {
        Trio<Choice> voting_result = GetVotingResults();
        UpdateData(voting_result);
    }

    PrintScore();
}

void FastMode::PrintScore()
{
    std::cout << std::setw(30) << std::left << "Strategies names"
              << std::setw(30) << std::left << "Final score" << std::endl;

    for (int i = 0; i < 3; ++i)
    {
        std::cout << std::setw(30) << std::left << strategies_[i].name_
                  << std::setw(30) << std::left << score_[i] << std::endl;
    }
}