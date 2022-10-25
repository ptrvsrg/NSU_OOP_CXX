#ifndef TASK2_TIT_FOR_TAT_WITH_FORGIVENESS_H
#define TASK2_TIT_FOR_TAT_WITH_FORGIVENESS_H

#include <boost/property_tree/json_parser.hpp>

#include "strategy_interface.h"

namespace pt = boost::property_tree;

class TitForTatWithForgivenessStrategy : public Strategy
{
public:
    TitForTatWithForgivenessStrategy(const std::string & config_dir);
    Choice vote() override;
    void update(Choice choice1,
                Choice choice2) override;
private:
    int max_count_D_;
    int count_D_ = 0;
    Choice choice_ = C;
};

#endif //TASK2_TIT_FOR_TAT_WITH_FORGIVENESS_H
