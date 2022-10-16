#ifndef TASK2_TOURNAMENT_MODE_H
#define TASK2_TOURNAMENT_MODE_H

#include <algorithm>
#include <iomanip>

#include "abstract_mode.h"

class TournamentMode : public Mode
{
public:
    void Launch() override;
private:
    Trio<int> strategy_nums_;
    std::vector<bool> combination_;
    Trio<int> intermediate_score_;

    bool GenerateCombination();
    void UpdateScore();
    void PrintIntermediateScore();
    void PrintScore();
};

#endif //TASK2_TOURNAMENT_MODE_H
