#ifndef TASK2_ALWAYS_COOPERATE_H
#define TASK2_ALWAYS_COOPERATE_H

#include "strategy_interface.h"

class AlwaysDesertStrategy : public Strategy
{
public:
    AlwaysDesertStrategy() {}
    Choice vote() override;
};

extern "C" Strategy * CreateStrategy(Matrix matrix,
                                     std::string confiDir);

#endif // TASK2_ALWAYS_COOPERATE_H