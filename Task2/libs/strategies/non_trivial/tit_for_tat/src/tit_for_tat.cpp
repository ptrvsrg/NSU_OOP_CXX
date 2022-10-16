#include "tit_for_tat.h"

Choice TitForTatStrategy::vote()
{
    return (previous_move == C) ? D : C;
}

void TitForTatStrategy::update(Choice move1, Choice move2)
{
    previous_move = (move1 == D || move2 == D) ? D : C;
}

Strategy * CreateStrategy(Matrix matrix,
                          std::string configDir)
{
    return new TitForTatStrategy();
}
