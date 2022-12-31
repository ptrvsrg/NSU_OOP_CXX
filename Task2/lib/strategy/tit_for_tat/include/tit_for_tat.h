#ifndef TASK2_TIT_FOR_TAT_H
#define TASK2_TIT_FOR_TAT_H

#include "strategy_interface.h"

class TitForTatStrategy : public Strategy
{
public:
    TitForTatStrategy() = default;
    Choice vote() override;
    void update(Choice choice1,
                Choice choice2) override;
private:
    Choice choice_ = C;
};

#endif // TASK2_TIT_FOR_TAT_H