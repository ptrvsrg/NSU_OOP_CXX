#include "strategy_creator.h"

StrategyPtr StrategyCreator::Create(const std::string & name,
                                    const std::string & config_dir)
{
    if      (name == "always_cooperate")    return std::make_unique<AlwaysCooperateStrategy>();
    else if (name == "always_defect")       return std::make_unique<AlwaysDefectStrategy>();
    else if (name == "grim_trigger")        return std::make_unique<GrimTriggerStrategy>();
    else if (name == "pavlov")              return std::make_unique<PavlovStrategy>(config_dir);
    else if (name == "random")              return std::make_unique<RandomStrategy>();
    else if (name == "tit_for_tat")         return std::make_unique<TitForTatStrategy>();
    else                                    throw std::invalid_argument("Wrong strategy name");
}
