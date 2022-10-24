#ifndef TASK2_ALWAYS_COOPERATE_H
#define TASK2_ALWAYS_COOPERATE_H

#include "strategy_creator.h"
#include "strategy_interface.h"

class AlwaysCooperateStrategy : public Strategy
{
public:
    AlwaysCooperateStrategy() = default;
    Choice vote() override;
};

#endif // TASK2_ALWAYS_COOPERATE_H