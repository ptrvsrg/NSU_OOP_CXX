#include "detailed_mode.h"

void DetailedMode::PrintDescription()
{
    std::cout << "Enter \"step\" to take one step\n";
    std::cout << "Enter \"quit\" to exit\n";
}

void DetailedMode::Launch()
{
    PrintDescription();
    while (true)
    {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "quit")
        {
            break;
        }
        else if (cmd == "step")
        {
            Trio<Choice> voting_result = GetVotingResults();
            UpdateData(voting_result);
            PrintCurrentScores(voting_result);
        }
        else
        {
            std::cout << "Entered an undefined command\n";
            PrintDescription();
        }
    }
}

void DetailedMode::PrintCurrentScores(Trio<Choice> voting_result)
{
    std::cout << std::setw(30) << std::left << "Strategies names"
              << std::setw(30) << std::left << "Choice"
              << std::setw(30) << std::left << "Points for current move"
              << std::setw(30) << std::left << "Current score" << std::endl;

    int row = GetMatrixRowNum(voting_result);
    for (int i = 0; i < 3; ++i)
    {
        std::cout << std::setw(30) << std::left << strategies_[i].name_
                  << std::setw(30) << std::left << voting_result[i]
                  << std::setw(30) << std::left << matrix_[row][i]
                  << std::setw(30) << std::left << score_[i] << std::endl;
    }
}
