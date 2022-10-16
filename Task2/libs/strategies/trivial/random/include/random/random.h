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
    void update(Choice, Choice) override {}
};

extern "C" Strategy * CreateStrategy(Matrix matrix,
                                     std::string configDir);

#endif // TASK2_RANDOM_H