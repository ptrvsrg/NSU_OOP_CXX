#include "always_desert.h"

Choice AlwaysDesertStrategy::vote()
{
    return D;
}

Strategy * CreateStrategy(Matrix matrix,
                          std::string confiDir)
{
    return new AlwaysDesertStrategy();
}