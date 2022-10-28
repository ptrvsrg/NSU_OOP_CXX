#ifndef TASK2_GRIM_TRIGGER_H
#define TASK2_GRIM_TRIGGER_H

#include "strategy_interface.h"

class GrimTriggerStrategy : public Strategy
{
public:
    GrimTriggerStrategy() = default;
    Choice vote() override;
    void update(Choice choice1,
                Choice choice2) override;
private:
    Choice choice_ = C;
};

#endif // TASK2_GRIM_TRIGGER_H
