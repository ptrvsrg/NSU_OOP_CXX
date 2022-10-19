#ifndef TASK2_TOURNAMENT_MODE_H
#define TASK2_TOURNAMENT_MODE_H

#include <algorithm>
#include <iomanip>
#include <vector>

#include "abstract_mode.h"

class TournamentMode : public Mode
{
public:
    void Launch() override;
private:
    Trio<int> strategy_nums_;
    std::vector<bool> combination_;
    std::vector<int> final_scores_;

    bool GenerateCombination();
    void UpdateFinalScores(Trio<Choice> voting_result);
    void ClearScores();
    void PrintScores();
    void PrintFinalScores();
};

#endif //TASK2_TOURNAMENT_MODE_H
