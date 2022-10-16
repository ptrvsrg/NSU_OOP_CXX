#ifndef TASK2_TIT_FOR_TAT_H
#define TASK2_TIT_FOR_TAT_H

#include <vector>
#include "strategy_interface.h"

class TitForTatStrategy : public Strategy
{
public:
    TitForTatStrategy() {}
    Choice vote() override;
    void update(Choice, Choice) override;
private:
    Choice previous_move = D;
};

extern "C" Strategy * CreateStrategy(Matrix matrix,
                                     std::string configDir);

#endif // TASK2_TIT_FOR_TAT_H