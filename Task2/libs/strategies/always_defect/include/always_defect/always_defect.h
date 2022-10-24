#ifndef TASK2_ALWAYS_DEFECT_H
#define TASK2_ALWAYS_DEFECT_H

#include "strategy_interface.h"

class AlwaysDefectStrategy : public Strategy
{
public:
    AlwaysDefectStrategy() = default;
    Choice vote() override;
};

#endif // TASK2_ALWAYS_DEFECT_H