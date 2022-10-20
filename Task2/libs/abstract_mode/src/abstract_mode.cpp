#include "abstract_mode.h"

void Mode::Init(std::vector<std::string> strategy_names,
           int steps,
           std::string lib_dir,
           std::string config_dir,
           Matrix matrix)
{
    steps_ = steps;
    config_dir_ = config_dir;
    lib_dir_ = lib_dir;
    matrix_ = matrix;
    strategy_names_ = strategy_names;
}

Trio<Choice> Mode::GetVotingResults()
{
    Trio<Choice> voting_result;
    for (int i = 0; i < 3; ++i)
    {
        voting_result[i] = (strategies_[i].object_ptr_->vote());
    }

    return voting_result;
}

void Mode::UpdateStrategies(Trio<Choice> voting_result)
{
    for (int i = 0; i < 3; ++i)
    {
        strategies_[i].object_ptr_->update(voting_result[(i + 1) % 3],
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

void Mode::LoadStrategies(Trio<int> strategy_nums)
{
    for (int i = 0; i < 3; ++i)
    {
        strategies_[i] = LoadedStrategy(strategy_names_[strategy_nums[i]],
                                        lib_dir_,
                                        config_dir_,
                                        matrix_);
    }
}

void Mode::ClearStrategies()
{
    for (LoadedStrategy strategy : strategies_)
    {
        strategy.Clear();
    }
}
