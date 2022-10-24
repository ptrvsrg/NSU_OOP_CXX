#ifndef TASK2_RANDOM_H
#define TASK2_RANDOM_H

#include <cstdlib>
#include <ctime>

#include "matrix.h"
#include "strategy_interface.h"

class RandomStrategy : public Strategy
{
public:
    RandomStrategy();
    Choice vote() override;
};

extern "C" Strategy * CreateStrategy(Matrix matrix,
                                     std::string config_dir);

#endif // TASK2_RANDOM_H