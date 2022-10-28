#ifndef TASK2_MODE_CREATOR_H
#define TASK2_MODE_CREATOR_H

#include <memory>
#include <string>

#include "abstract_mode.h"
#include "detailed_mode.h"
#include "fast_mode.h"
#include "tournament_mode.h"

class ModeCreator
{
public:
    std::unique_ptr<Mode> Create(const std::vector<std::string> & strategy_names,
                                 const std::string & mode,
                                 int steps,
                                 const std::string & config_dir,
                                 Matrix matrix);
};

#endif // TASK2_MODE_CREATOR_H
