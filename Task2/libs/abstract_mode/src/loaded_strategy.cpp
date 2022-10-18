#include "loaded_strategy.h"

LoadedStrategy::LoadedStrategy(std::string strategy_name,
                               std::string lib_dir,
                               std::string config_dir,
                               Matrix matrix)
    :   name_(strategy_name)
{
    std::string dll_name = lib_dir + name_ + ".so";
    handle_ = dlopen(dll_name.c_str(), RTLD_LAZY);
    if (!handle_)
    {
        throw std::invalid_argument(dlerror());
    }

    Strategy * (*CreateStrategy)(Matrix, std::string) = (Strategy * (*)(Matrix, std::string))dlsym(handle_, "CreateStrategy");
    if (!CreateStrategy)
    {
        throw std::invalid_argument(dlerror());
    }

    object_ptr_ = (*CreateStrategy)(matrix, config_dir);
}

void LoadedStrategy::Clear()
{
    name_.clear();
    delete object_ptr_;
    if (dlclose(handle_))
    {
        throw std::invalid_argument(dlerror());
    }
}
