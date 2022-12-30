#include "grim_trigger.h"

Choice GrimTriggerStrategy::vote()
{
    return choice_;
}

void GrimTriggerStrategy::update(Choice choice1,
                                 Choice choice2)
{
    if (choice1 == D || choice2 == D)
    {
        choice_ = D;
    }
}
