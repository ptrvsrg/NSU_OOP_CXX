#ifndef TASK2_PROBABILITY_H
#define TASK2_PROBABILITY_H

#include <algorithm>

#include "matrix.h"
#include "strategy_interface.h"

class ProbabilityStrategy : public Strategy
{
public:
    explicit ProbabilityStrategy(Matrix matrix);
    Choice vote() override;
    void update(Choice choice1,
                Choice choice2) override;
private:
    Choice choice_ = C;
    std::array<int, 4> choices_frequencies_ = {0, 0, 0, 0};
    std::array<Choice, 4> choices_;
};

extern "C" Strategy * CreateStrategy(Matrix matrix,
                                     std::string config_dir);

#endif // TASK2_PROBABILITY_H
