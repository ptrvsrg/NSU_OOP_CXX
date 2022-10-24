#include "random.h"


RandomStrategy::RandomStrategy()
{
    srand(time(nullptr));
}

Choice RandomStrategy::vote()
{
    return static_cast<Choice>(rand() % 2);
}

Strategy* CreateStrategy(Matrix matrix,
                         std::string config_dir)
{
    return new RandomStrategy();
}