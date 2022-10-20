#ifndef TASK2_TIT_FOR_TAT_H
#define TASK2_TIT_FOR_TAT_H

#include <vector>

#include "matrix.h"
#include "strategy_interface.h"

class TitForTatStrategy : public Strategy
{
public:
    TitForTatStrategy() {}
    Choice vote() override;
    void update(Choice choice1,
                Choice choice2) override;
private:
    Choice choice_ = C;
};

extern "C" Strategy * CreateStrategy(Matrix matrix,
                                     std::string config_dir);

#endif // TASK2_TIT_FOR_TAT_H