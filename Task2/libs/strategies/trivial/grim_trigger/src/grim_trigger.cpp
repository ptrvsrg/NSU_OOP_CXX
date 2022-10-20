#include "grim_trigger.h"

Choice HandshakeStrategy::vote()
{
    return choice_;
}

void HandshakeStrategy::update(Choice choice1,
                               Choice choice2)
{
    if (choice1 == D || choice2 == D)
    {
        choice_ = D;
    }
}

Strategy * CreateStrategy(Matrix matrix,
                          std::string config_dir)
{
    return new HandshakeStrategy();
}
