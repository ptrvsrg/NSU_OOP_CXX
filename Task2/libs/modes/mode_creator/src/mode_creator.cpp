#include "mode_creator.h"

std::unique_ptr<Mode> ModeCreator::Create(const std::vector<std::string> & strategy_names,
                                          const std::string & mode,
                                          int steps,
                                          const std::string & config_dir,
                                          Matrix matrix)
{
    if (mode == "detailed") return std::make_unique<DetailedMode>(strategy_names,
                                                                  steps,
                                                                  config_dir,
                                                                  matrix);
    else if (mode == "fast") return std::make_unique<FastMode>(strategy_names,
                                                               steps,
                                                               config_dir,
                                                               matrix);
    else if (mode == "tournament") return std::make_unique<TournamentMode>(strategy_names,
                                                                           steps,
                                                                           config_dir,
                                                                           matrix);
    else throw std::invalid_argument("Wrong modes");
}
