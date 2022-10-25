#include "tit_for_tat.h"

Choice TitForTatStrategy::vote()
{
    return choice_;
}

void TitForTatStrategy::update(Choice choice1,
                               Choice choice2)
{
    choice_ = (choice1 == D || choice2 == D) ? D : C;
}
