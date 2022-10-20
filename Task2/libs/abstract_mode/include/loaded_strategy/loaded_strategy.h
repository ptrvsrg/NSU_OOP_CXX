#ifndef TASK2_LOADED_STRATEGY_H
#define TASK2_LOADED_STRATEGY_H

#include <dlfcn.h>
#include <iostream>
#include <string>

#include "matrix.h"
#include "strategy_interface.h"

class LoadedStrategy
{
public:
    Strategy * object_ptr_;

    LoadedStrategy();
    LoadedStrategy(std::string strategy_name,
                   std::string lib_dir,
                   std::string config_dir,
                   Matrix matrix);
    void Clear();

private:
    void * handle_;
};


#endif // TASK2_LOADED_STRATEGY_H
