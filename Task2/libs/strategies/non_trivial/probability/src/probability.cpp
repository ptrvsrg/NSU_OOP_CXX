#include "probability.h"


ProbabilityStrategy::ProbabilityStrategy(Matrix matrix)
{
    matrix_ = matrix;
}

Choice ProbabilityStrategy::vote()
{
    return choice_;
}

void ProbabilityStrategy::update(Choice choice1,
                                 Choice choice2)
{

}
