#ifndef TASK2_STRATEGY_INTERFACE_H
#define TASK2_STRATEGY_INTERFACE_H

#include <array>
#include <string>

template<class T> using Trio = std::array<T, 3>;

enum Choice
{
    C,  // cooperation
    D   // desertion
};

class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual Choice vote() = 0;
    virtual void update(Choice, Choice) {}
};

#endif // TASK2_STRATEGY_INTERFACE_H
