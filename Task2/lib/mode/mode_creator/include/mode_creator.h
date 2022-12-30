#ifndef TASK2_MODE_CREATOR_H
#define TASK2_MODE_CREATOR_H

#include <memory>
#include <string>

#include "abstract_mode.h"
#include "detailed_mode.h"
#include "fast_mode.h"
#include "tournament_mode.h"

using ModePtr = std::unique_ptr<Mode>;

class ModeNameException : std::invalid_argument
{
public:
    ModeNameException();
};

class ModeCreator
{
public:
    static ModePtr Create(const std::vector<std::string> & strategy_names,
                          const std::string & mode,
                          int steps,
                          const std::string & config_dir,
                          const Matrix& matrix);
};

#endif // TASK2_MODE_CREATOR_H
