#ifndef TASK2_RANDOM_H
#define TASK2_RANDOM_H

#include <cstdlib>
#include <ctime>

#include "strategy_interface.h"

class RandomStrategy : public Strategy
{
public:
    RandomStrategy();
    Choice vote() override;
};

#endif // TASK2_RANDOM_H