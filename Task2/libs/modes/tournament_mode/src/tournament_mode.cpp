#include "tournament_mode.h"

bool TournamentMode::GenerateCombination()
{
    if (combination_.empty())
    {
        combination_.resize(strategy_names_.size());
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
    final_scores_.resize(strategy_names_.size());
    std::fill(final_scores_.begin(),
              final_scores_.end(),
              0);

    while (GenerateCombination())
    {
        LoadStrategies(strategy_nums_);

        for (int i = 0; i < steps_; ++i)
        {
            Trio<Choice> voting_result = GetVotingResults();
            UpdateStrategies(voting_result);
            UpdateScores(voting_result);
            UpdateFinalScores(voting_result);
        }

        PrintScores();
        ClearScores();
        std::cout << std::endl;

        ClearStrategies();
    }

    PrintFinalScores();
}

void TournamentMode::UpdateFinalScores(Trio<Choice> voting_result)
{
    int row = matrix_.GetRowIndex(voting_result);
    for (int i = 0; i < 3; ++i)
    {
        final_scores_[strategy_nums_[i]] += matrix_[row][i];
    }
}

void TournamentMode::ClearScores()
{
    scores_ = {0, 0, 0};
}

void TournamentMode::PrintScores()
{
    std::cout << std::setw(30) << std::left << "Strategy numbers"
              << std::setw(30) << std::left << "Strategies names"
              << std::setw(30) << std::left << "Scores" << std::endl;

    for (int i = 0; i < 3; ++i)
    {
        std::cout << std::setw(30) << std::left << strategy_nums_[i] + 1
                  << std::setw(30) << std::left << strategy_names_[strategy_nums_[i]]
                  << std::setw(30) << std::left << scores_[i] << std::endl;
    }
}

void TournamentMode::PrintFinalScores()
{
    std::cout << std::setw(30) << std::left << "Strategies names"
              << std::setw(30) << std::left << "Final scores" << std::endl;

    for (int i = 0; i < strategy_names_.size(); ++i)
    {
        std::cout << std::setw(30) << std::left << strategy_names_[i]
                  << std::setw(30) << std::left << final_scores_[i] << std::endl;
    }
}
