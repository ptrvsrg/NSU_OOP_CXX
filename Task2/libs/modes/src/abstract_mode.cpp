#include "abstract_mode.h"

Mode::Mode(const std::vector<std::string> & strategy_names,
           int steps,
           const std::string & config_dir,
           Matrix matrix)
:   steps_(steps),
    config_dir_(config_dir),
    matrix_(matrix),
    strategy_names_(strategy_names) {}

Trio<Choice> Mode::GetVotingResults()
{
    Trio<Choice> voting_result;
    for (int i = 0; i < 3; ++i)
    {
        voting_result[i] = strategies_[i]->vote();
    }

    return voting_result;
}

void Mode::UpdateStrategyData(Trio<Choice> voting_result)
{
    for (int i = 0; i < 3; ++i)
    {
        strategies_[i]->update(voting_result[(i + 1) % 3],
                               voting_result[(i + 2) % 3]);
    }
}

void Mode::UpdateScores(Trio<Choice> voting_result)
{
    int row = matrix_.GetRowIndex(voting_result);
    for (int i = 0; i < 3; ++i)
    {
        scores_[i] += matrix_[row][i];
    }
}

void Mode::CreateStrategies(Trio<int> strategy_nums)
{
    StrategyCreator creator;
    for (int i = 0; i < 3; ++i)
    {
        strategies_[i] = creator.Create(strategy_names_[strategy_nums[i]],
                                        config_dir_);
    }
}

void Mode::UpdateStrategies(Trio<int> strategy_nums)
{
    StrategyCreator creator;
    for (int i = 0; i < 3; ++i)
    {
        strategies_[i].reset();
        strategies_[i] = creator.Create(strategy_names_[strategy_nums[i]],
                                        config_dir_);
    }
}
