#include "abstract_mode.h"

void Mode::Init(std::vector<std::string> strategy_names,
           int steps,
           std::string lib_dir,
           std::string config_dir,
           Matrix matrix)
{
    steps_ = steps;
    config_dir_ = config_dir;
    matrix_ = matrix;

    for (const std::string & name : strategy_names)
    {
        LoadedStrategy loaded_strategy(name,
                                       lib_dir,
                                       config_dir,
                                       matrix);
        strategies_.push_back(loaded_strategy);
    }

    scores_.resize(strategies_.size());
    std::fill(scores_.begin(), scores_.end(), 0);
}

void Mode::Clear()
{
    for (LoadedStrategy strategy : strategies_)
    {
        strategy.Clear();
    }
}

Mode::~Mode()
{
    strategies_.clear();
}

Trio<Choice> Mode::GetVotingResults(Trio<int> strategy_nums)
{
    Trio<Choice> voting_result;
    for (int i = 0; i < 3; ++i)
    {
        voting_result[i] = (strategies_[strategy_nums[i]].object_ptr_->vote());
    }

    return voting_result;
}

void Mode::UpdateStrategies(Trio<Choice> voting_result,
                            Trio<int> strategy_nums)
{
    for (int i = 0; i < 3; ++i)
    {
        strategies_[strategy_nums[i]].object_ptr_->update(voting_result[(i + 1) % 3],
                                                          voting_result[(i + 2) % 3]);
    }
}

void Mode::UpdateScores(Trio<Choice> voting_result,
                        Trio<int> strategy_nums)
{
    int row = matrix_.GetRow(voting_result);
    for (int i = 0; i < 3; ++i)
    {
        scores_[strategy_nums[i]] += matrix_[row][i];
    }
}
