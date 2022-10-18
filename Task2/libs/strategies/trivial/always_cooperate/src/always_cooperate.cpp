#include "always_cooperate.h"

Choice AlwaysCooperateStrategy::vote()
{
    return C;
}

Strategy * CreateStrategy(Matrix matrix,
                          std::string config_dir)
{
    return new AlwaysCooperateStrategy();
}