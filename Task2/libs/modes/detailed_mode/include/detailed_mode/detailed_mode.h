#ifndef TASK2_DETAILED_MODE_H
#define TASK2_DETAILED_MODE_H

#include <iomanip>

#include "abstract_mode.h"

class DetailedMode : public Mode
{
public:
    void Launch() override;
private:
    void PrintDescription();
    void PrintScores(Trio<Choice> voting_result);
};

#endif //TASK2_DETAILED_MODE_H
