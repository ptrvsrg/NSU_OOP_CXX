#ifndef TASK2_ALWAYS_COOPERATE_H
#define TASK2_ALWAYS_COOPERATE_H

#include "matrix.h"
#include "strategy_interface.h"

class AlwaysCooperateStrategy : public Strategy
{
public:
    AlwaysCooperateStrategy() {}
    Choice vote() override;
};

extern "C" Strategy * CreateStrategy(Matrix matrix,
                                     std::string config_dir);

#endif // TASK2_ALWAYS_COOPERATE_H