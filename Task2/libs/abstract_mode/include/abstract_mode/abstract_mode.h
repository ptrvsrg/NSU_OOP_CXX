#ifndef TASK2_ABSTRACT_MODE_H
#define TASK2_ABSTRACT_MODE_H

#include <iostream>
#include <string>
#include <vector>

#include "loaded_strategy.h"
#include "matrix.h"

class Mode
{
public:
    Mode(std::vector<std::string> strategy_names,
         int steps,
         std::string lib_dir,
         std::string config_dir,
         Matrix matrix);
    virtual void Launch() = 0;
    virtual ~Mode() = default;

protected:
    std::vector<std::string> strategy_names_;
    Trio<LoadedStrategy> strategies_;
    int steps_;
    std::string lib_dir_;
    std::string config_dir_;
    Matrix matrix_;
    Trio<int> scores_ = {0, 0, 0};

    Trio<Choice> GetVotingResults();
    void UpdateStrategies(Trio<Choice> voting_result);
    void UpdateScores(Trio<Choice> voting_result);
    void LoadStrategies(Trio<int> strategy_nums = {0, 1, 2});
    void ClearStrategies();
};

#endif //TASK2_ABSTRACT_MODE_H
