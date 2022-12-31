#include "random.h"

RandomStrategy::RandomStrategy()
{
    srand(time(nullptr));
}

Choice RandomStrategy::vote()
{
    return static_cast<Choice>(rand() % 2);
}