#ifndef TASK2_GRIM_TRIGGER_H
#define TASK2_GRIM_TRIGGER_H

#include "matrix.h"
#include "strategy_interface.h"

class GrimTriggerStrategy : public Strategy
{
public:
    GrimTriggerStrategy() {}
    Choice vote() override;
    void update(Choice choice1,
                Choice choice2) override;
private:
    Choice choice_ = C;
};

extern "C" Strategy * CreateStrategy(Matrix matrix,
                                     std::string config_dir);

#endif // TASK2_GRIM_TRIGGER_H
