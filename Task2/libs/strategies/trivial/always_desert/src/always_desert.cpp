#include "always_desert.h"

Choice AlwaysDesertStrategy::vote()
{
    return D;
}

Strategy * CreateStrategy(Matrix matrix,
                          std::string config_dir)
{
    return new AlwaysDesertStrategy();
}