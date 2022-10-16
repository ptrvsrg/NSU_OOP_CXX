#ifndef TASK2_ABSTRACT_MODE_H
#define TASK2_ABSTRACT_MODE_H

#include <dlfcn.h>
#include <iostream>
#include <string>
#include <vector>

#include "matrix.h"
#include "strategy_interface.h"

class LoadedStrategy
{
public:
    std::string name_;
    Strategy * object_ptr_;

    LoadedStrategy(std::string strategy_name,
                   std::string lib_dir,
                   std::string config_dir,
                   Matrix<int, 8, 3> matrix);
    ~LoadedStrategy();

private:
    void * handle_;
};


class Mode
{
public:
    void Init(std::vector<std::string> strategies_names,
         int steps,
         std::string lib_dir,
         std::string config_dir,
         Matrix<int, 8, 3> matrix);
    virtual void Launch() = 0;
    virtual ~Mode();

protected:
    std::vector<LoadedStrategy> strategies_;
    int steps_;
    Matrix<int, 8, 3> matrix_;
    std::string config_dir_;
    std::vector<int> score_;

    int GetMatrixRowNum(Trio<Choice> choices);
    virtual Trio<Choice> GetVotingResults(Trio<int> strategy_nums = {0, 1, 2});
    virtual void UpdateData(Trio<Choice> voting_result,
                            Trio<int> strategy_nums = {0, 1, 2});
};

#endif //TASK2_ABSTRACT_MODE_H
