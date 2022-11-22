#include "sound_processor_errors.h"

NonExistentLink::NonExistentLink(int file_link)
    : std::invalid_argument("File on the link $" + std::to_string(file_link) + " was not found") {}
