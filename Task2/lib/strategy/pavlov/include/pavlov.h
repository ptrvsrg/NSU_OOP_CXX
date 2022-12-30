#ifndef TASK2_PAVLOV_H
#define TASK2_PAVLOV_H

#include <boost/property_tree/json_parser.hpp>
#include <memory>

#include "strategy_creator.h"
#include "strategy_interface.h"

namespace pt = boost::property_tree;

class PavlovStrategy : public Strategy
{
public:
    PavlovStrategy(const std::string & config_dir);
    Choice vote() override;
    void update(Choice choice1,
                Choice choice2) override;
private:
    int steps_count_ = 0;
    int count_D1_ = 0;
    int count_D2_ = 0;
    std::string config_dir_;
    pt::ptree config_tree_;
    std::unique_ptr<Strategy> loaded_strategy_;

    enum Case
    {
        TIT_FOR_TAT,
        SUSPICIOUS_TIT_FOR_TAT,
        ALWAYS_DEFECT,
        RANDOM
    };
    Case GetCase(int count_D);
};

#endif // TASK2_PAVLOV_H
