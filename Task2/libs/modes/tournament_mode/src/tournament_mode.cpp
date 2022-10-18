#include "tournament_mode.h"

bool TournamentMode::GenerateCombination()
{
    if (combination_.empty())
    {
        combination_.resize(strategies_.size());
        std::fill(combination_.begin(),
                  combination_.begin() + 3,
                  true);
    }
    else if (!std::prev_permutation(combination_.begin(),
                                    combination_.end()))
    {
        return false;
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
            Trio<Choice> voting_result = GetVotingResults(strategy_nums_);
            UpdateStrategies(voting_result,
                             strategy_nums_);
            UpdateIntermediateScores(voting_result,
                                     strategy_nums_);
            UpdateScores(voting_result,
                         strategy_nums_);
        }

        PrintIntermediateScores();
        ClearIntermediateScores();
        std::cout << std::endl;
    }

    PrintScores();
}

void TournamentMode::UpdateIntermediateScores(Trio<Choice> voting_result,
                                              Trio<int> strategy_nums)
{
    int row = matrix_.GetRow(voting_result);
    for (int i = 0; i < 3; ++i)
    {
        intermediate_scores_[strategy_nums[i]] += matrix_[row][i];
    }
}

void TournamentMode::ClearIntermediateScores()
{
    intermediate_scores_ = {0, 0, 0};
}

void TournamentMode::PrintIntermediateScores()
{
    std::cout << std::setw(30) << std::left << "Strategy numbers"
              << std::setw(30) << std::left << "Strategies names"
              << std::setw(30) << std::left << "Scores" << std::endl;

    for (int i = 0; i < 3; ++i)
    {
        std::cout << std::setw(30) << std::left << strategy_nums_[i] + 1
                  << std::setw(30) << std::left << strategies_[strategy_nums_[i]].name_
                  << std::setw(30) << std::left << intermediate_scores_[i] << std::endl;
    }
}

void TournamentMode::PrintScores()
{
    std::cout << std::setw(30) << std::left << "Strategies names"
              << std::setw(30) << std::left << "Final scores" << std::endl;

    for (int i = 0; i < strategies_.size(); ++i)
    {
        std::cout << std::setw(30) << std::left << strategies_[i].name_
                  << std::setw(30) << std::left << scores_[i] << std::endl;
    }
}
