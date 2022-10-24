#ifndef TASK2_STRATEGY_CREATOR_H
#define TASK2_STRATEGY_CREATOR_H

#include <memory>

#include "strategy_interface.h"

// Strategy
#include "always_cooperate.h"
#include "always_defect.h"
#include "grim_trigger.h"
#include "pavlov.h"
#include "random.h"
#include "tit_for_tat.h"

using StrategyPtr = std::unique_ptr<Strategy>;

class StrategyCreator
{
public:
    StrategyPtr Create(const std::string & name,
                       const std::string & config_dir);
};

#endif // TASK2_STRATEGY_CREATOR_H
