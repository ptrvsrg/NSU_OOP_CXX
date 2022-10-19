#include "probability.h"

ProbabilityStrategy::ProbabilityStrategy(Matrix matrix)
{
    for (int i = 0; i < 4; ++i)
    {
        choices_[i] = (matrix[i + (C << 2)][0] < matrix[i + (D << 2)][0]) ? D : C;
    }
}

Choice ProbabilityStrategy::vote()
{
    int index = std::distance(choices_frequencies_.cbegin(),
                              std::max_element(choices_frequencies_.cbegin(),
                                               choices_frequencies_.cend()));
    return choices_[index];
}

void ProbabilityStrategy::update(Choice choice1,
                                 Choice choice2)
{
    int index = (choice1 << 1) + choice2;
    ++choices_frequencies_[index];
}

Strategy * CreateStrategy(Matrix matrix,
                          std::string config_dir)
{
    return new ProbabilityStrategy(matrix);
}
