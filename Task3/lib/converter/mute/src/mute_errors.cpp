#include "mute_errors.h"

IntervalException::IntervalException()
:   std::runtime_error("mute converter : Incorrect interval time\n") {}
