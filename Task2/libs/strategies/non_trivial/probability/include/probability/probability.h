#ifndef TASK2_PROBABILITY_H
#define TASK2_PROBABILITY_H

#include "matrix.h"
#include "strategy_interface.h"

class ProbabilityStrategy : Strategy
{
public:
    explicit ProbabilityStrategy(Matrix matrix);
    Choice vote() override;
    void update(Choice choice1,
                Choice choice2) override;
private:
    Choice choice_ = C;
    std::array<float, 4> choices_probabilities_ = {0, 0, 0, 0};
    int step_count_ = 0;
    Matrix matrix_;
};

extern "C" Strategy * CreateStrategy(Matrix matrix,
                                     std::string config_dir);

#endif // TASK2_PROBABILITY_H
