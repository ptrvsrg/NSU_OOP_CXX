#ifndef TASK3_SOUND_PROCESSOR_ERRORS_H
#define TASK3_SOUND_PROCESSOR_ERRORS_H

#include <stdexcept>

class NonExistentLink : public std::invalid_argument
{
public:
    explicit NonExistentLink(int file_link);
};


#endif //TASK3_SOUND_PROCESSOR_ERRORS_H
