#include "detailed_mode.h"

DetailedMode::DetailedMode(const std::vector<std::string> & strategy_names,
                           int steps,
                           const std::string & config_dir,
                           Matrix matrix)
: Mode(strategy_names,
       steps,
       config_dir,
       matrix) {}

void DetailedMode::PrintDescription()
{
    std::cout << "Enter \"step\" to take one step\n";
    std::cout << "Enter \"quit\" to exit\n";
}

void DetailedMode::Launch()
{
    CreateStrategies();
    PrintDescription();
    while (true)
    {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "quit") break;
        else if (cmd == "step")
        {
            Trio<Choice> voting_result = GetVotingResults();
            UpdateStrategyData(voting_result);
            UpdateScores(voting_result);
            PrintScores(voting_result);
        }
        else
        {
            std::cout << "Entered an undefined command\n";
            PrintDescription();
        }
    }
}

void DetailedMode::PrintScores(Trio<Choice> voting_result)
{
    std::cout << std::setw(30) << std::left << "Strategies names"
              << std::setw(30) << std::left << "Choices"
              << std::setw(30) << std::left << "Points for step"
              << std::setw(30) << std::left << "Scores" << std::endl;

    int row = matrix_.GetRowIndex(voting_result);
    for (int i = 0; i < 3; ++i)
    {
        std::cout << std::setw(30) << std::left << strategy_names_[i]
                  << std::setw(30) << std::left << voting_result[i]
                  << std::setw(30) << std::left << matrix_[row][i]
                  << std::setw(30) << std::left << scores_[i] << std::endl;
    }
}
