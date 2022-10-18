#ifndef TASK2_STRATEGY_INTERFACE_H
#define TASK2_STRATEGY_INTERFACE_H

#include <array>
#include <string>

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
    virtual void update(Choice choice1,
                        Choice choice2) {}
};

#endif // TASK2_STRATEGY_INTERFACE_H
