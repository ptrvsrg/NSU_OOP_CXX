#include "tournament_mode.h"

bool TournamentMode::GenerateCombination()
{
    if (combination_.empty())
    {
        combination_.resize(strategies_.size());
        std::fill(combination_.begin(), combination_.begin() + 3, true);
    }
    else
    {
        if (!std::prev_permutation(combination_.begin(), combination_.end())) return false;
    }

    int array_index = 0;
    for (int i = 0; i < combination_.size(); ++i)
    {
        if (combination_[i])
        {
            strategy_nums_[array_index] = i;
            ++array_index;
        }
    }

    return true;
}

void TournamentMode::Launch()
{
    while (GenerateCombination())
    {
        for (int i = 0; i < steps_; ++i)
        {
            Trio<Choice> generatedMoves = GetVotingResults(strategy_nums_);
            UpdateData(generatedMoves, strategy_nums_);
        }

        PrintIntermediateScore();
        UpdateScore();
        std::cout << std::endl;
    }

    PrintScore();
}

void TournamentMode::UpdateScore()
{
    for (int i = 0; i < 3; ++i)
    {
        score_[strategy_nums_[i]] += intermediate_score_[i];
    }

    std::fill(intermediate_score_.begin(), intermediate_score_.end(), 0);
}

void TournamentMode::PrintIntermediateScore()
{
    std::cout << std::setw(30) << std::left << "Strategy number"
              << std::setw(30) << std::left << "Strategies names"
              << std::setw(30) << std::left << "Final score" << std::endl;

    for (int i = 0; i < 3; ++i)
    {
        std::cout << std::setw(30) << std::left << strategy_nums_[i] + 1
                  << std::setw(30) << std::left << strategies_[strategy_nums_[i]].name_
                  << std::setw(30) << std::left << intermediate_score_[i] << std::endl;
    }
}

void TournamentMode::PrintScore()
{
    std::cout << std::setw(30) << std::left << "Strategies names"
              << std::setw(30) << std::left << "Final score" << std::endl;

    for (int i = 0; i < strategies_.size(); ++i)
    {
        std::cout << std::setw(30) << std::left << strategies_[i].name_
                  << std::setw(30) << std::left << score_[i] << std::endl;
    }
}
