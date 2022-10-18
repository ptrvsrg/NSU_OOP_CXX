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
    Trio<int> intermediate_scores_ = {0, 0, 0};

    bool GenerateCombination();
    void UpdateIntermediateScores(Trio<Choice> voting_result,
                                  Trio<int> strategy_nums);
    void ClearIntermediateScores();
    void PrintIntermediateScores();
    void PrintScores();
};

#endif //TASK2_TOURNAMENT_MODE_H
