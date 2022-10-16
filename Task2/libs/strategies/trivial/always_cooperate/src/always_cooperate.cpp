#include "always_cooperate.h"

Choice AlwaysCooperateStrategy::vote()
{
    return C;
}

Strategy * CreateStrategy(Matrix matrix,
                          std::string configDir)
{
    return new AlwaysCooperateStrategy();
}