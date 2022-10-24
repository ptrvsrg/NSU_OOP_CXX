#include "pavlov.h"

PavlovStrategy::PavlovStrategy(const std::string & config_dir)
:   config_dir_(config_dir)
{
    pt::read_json(config_dir + "pavlov.json",
                  config_tree_);

    StrategyCreator creator;
    loaded_strategy_ = creator.Create(config_tree_.get<std::string>("Start"),
                                      config_dir_);
}

Choice PavlovStrategy::vote()
{
    return loaded_strategy_->vote();
}

void PavlovStrategy::update(Choice choice1,
                            Choice choice2)
{
    if (steps_count_ < 6)
    {
        ++steps_count_;
        count_D1_ += choice1;
        count_D2_ += choice2;
    }
    else if (steps_count_ == 6)
    {
        ++steps_count_;
        std::string case_name;
        StrategyCreator creator;

        switch (std::max(GetCase(count_D1_),
                         GetCase(count_D2_)))
        {
            case TIT_FOR_TAT:
                case_name = "Tit For Tat";
                break;
            case SUSPICIOUS_TIT_FOR_TAT:
                case_name = "Suspicious Tit For Tat";
                break;
            case ALWAYS_DEFECT:
                case_name = "Always Defect";
                break;
            case RANDOM:
                case_name = "Random";
        }

        loaded_strategy_ = creator.Create(config_tree_.get<std::string>(case_name),
                                          config_dir_);
    }

    loaded_strategy_->update(choice1,
                             choice2);
}

PavlovStrategy::Case PavlovStrategy::GetCase(int count_D)
{
    if (count_D == 0)        return TIT_FOR_TAT;
    else if (count_D == 3)   return SUSPICIOUS_TIT_FOR_TAT;
    else if (count_D > 3)    return ALWAYS_DEFECT;
    else                     return RANDOM;
}
