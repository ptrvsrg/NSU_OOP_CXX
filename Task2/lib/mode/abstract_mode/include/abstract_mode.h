#ifndef TASK2_ABSTRACT_MODE_H
#define TASK2_ABSTRACT_MODE_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "matrix.h"
#include "strategy_creator.h"

template<class T> using Trio = std::array<T, 3>;

class Mode
{
public:
    Mode(const std::vector<std::string> & strategy_names,
         int steps,
         const std::string & config_dir,
         Matrix matrix);
    virtual void Launch() = 0;
    virtual ~Mode() = default;

protected:
    std::vector<std::string> strategy_names_;
    Trio<StrategyPtr> strategies_;
    int steps_;
    std::string config_dir_;
    Matrix matrix_;
    Trio<int> scores_ = {0, 0, 0};

    Trio<Choice> GetVotingResults();
    void UpdateStrategyData(Trio<Choice> voting_result);
    void UpdateScores(Trio<Choice> voting_result);
    void CreateStrategies(Trio<int> strategy_nums = {0, 1, 2});
    void UpdateStrategies(Trio<int> strategy_nums);
};

#endif //TASK2_ABSTRACT_MODE_H
