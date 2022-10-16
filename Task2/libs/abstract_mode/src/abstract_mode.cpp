#include "abstract_mode.h"

LoadedStrategy::LoadedStrategy(std::string strategy_name,
                               std::string lib_dir,
                               std::string config_dir,
                               Matrix<int, 8, 3> matrix)
    :   name_(strategy_name)
{
    std::string dll_name = lib_dir + name_ + ".so";
    handle_ = dlopen(dll_name.c_str(), RTLD_LAZY);
    if (!handle_)
    {
        throw std::invalid_argument(dlerror());
    }

    Strategy * (*CreateStrategy)(Matrix<int, 8, 3>, std::string) = (Strategy * (*)(Matrix<int, 8, 3>, std::string))dlsym(handle_, "CreateStrategy");
    if (!CreateStrategy)
    {
        throw std::invalid_argument(dlerror());
    }

    object_ptr_ = (*CreateStrategy)(matrix, config_dir);
}

LoadedStrategy::~LoadedStrategy()
{
    name_.clear();

    delete object_ptr_;

    if (dlclose(handle_))
    {
        throw std::invalid_argument(dlerror());
    }
}



void Mode::Init(std::vector<std::string> strategies_names,
           int steps,
           std::string lib_dir,
           std::string config_dir,
           Matrix<int, 8, 3> matrix)
{
    steps_ = steps;
    config_dir_ = config_dir;
    CopyMatrix(matrix_, matrix);

    for (const std::string & name : strategies_names)
    {
        strategies_.push_back(LoadedStrategy(name,
                                             lib_dir,
                                             config_dir,
                                             matrix));
    }

    score_.resize(strategies_.size());
    std::fill(score_.begin(), score_.end(), 0);
}

Mode::~Mode()
{
    strategies_.clear();
}

int Mode::GetMatrixRowNum(Trio<Choice> choices)
{
    int row = 0;
    for(Choice choice : choices)
    {
        row = (row << 1) + choice;
    }

    return row;
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

void Mode::UpdateData(Trio<Choice> voting_result,
                      Trio<int> strategy_nums)
{
    int row = GetMatrixRowNum(voting_result);
    for (int i = 0; i < 3; ++i)
    {
        score_[i] += matrix_[row][i];
        strategies_[strategy_nums[i]].object_ptr_->update(voting_result[(i + 1) % 3], voting_result[(i + 2) % 3]);
    }
}
