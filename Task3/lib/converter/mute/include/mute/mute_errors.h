#ifndef TASK3_MUTE_ERRORS_H
#define TASK3_MUTE_ERRORS_H

#include <stdexcept>

class IntervalException : std::runtime_error
{
public:
    IntervalException();
};

#endif //TASK3_MUTE_ERRORS_H
