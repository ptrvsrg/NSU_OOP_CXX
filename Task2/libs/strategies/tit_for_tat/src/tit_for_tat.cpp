#include "tit_for_tat.h"

Choice TitForTatStrategy::vote()
{
    return choice_;
}

void TitForTatStrategy::update(Choice move1,
                               Choice move2)
{
    choice_ = (move1 == D || move2 == D) ? D : C;
}
