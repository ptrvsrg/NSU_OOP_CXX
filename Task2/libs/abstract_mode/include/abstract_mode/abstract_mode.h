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
    void Init(std::vector<std::string> strategy_names,
         int steps,
         std::string lib_dir,
         std::string config_dir,
         Matrix matrix);
    void Clear();
    virtual void Launch() = 0;
    virtual ~Mode();

protected:
    std::vector<LoadedStrategy> strategies_;
    int steps_;
    Matrix matrix_;
    std::string config_dir_;
    Trio<int> scores_ = {0, 0, 0};

    Trio<Choice> GetVotingResults(Trio<int> strategy_nums = {0, 1, 2});
    void UpdateStrategies(Trio<Choice> voting_result,
                          Trio<int> strategy_nums = {0, 1, 2});
    void UpdateScores(Trio<Choice> voting_result);
};

#endif //TASK2_ABSTRACT_MODE_H
