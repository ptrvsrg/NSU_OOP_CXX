#include "tit_for_tat_with_forgiveness.h"

TitForTatWithForgivenessStrategy::TitForTatWithForgivenessStrategy(const std::string & config_dir)
{
    pt::ptree config_tree;
    pt::read_json(config_dir + "tit_for_tat_with_forgiveness.json",
                  config_tree);

    int forgiveness_percentage_ = config_tree.get<int>("Forgiveness percentage");
    if (forgiveness_percentage_ < 0 || forgiveness_percentage_ > 100) throw std::invalid_argument("Wrong forgiveness percentage");

    max_count_D_ = 100 / forgiveness_percentage_;
}

Choice TitForTatWithForgivenessStrategy::vote()
{
    return choice_;
}

void TitForTatWithForgivenessStrategy::update(Choice choice1,
                                              Choice choice2)
{
    if (choice1 == D || choice2 == D)
    {
        count_D_ = (count_D_ + 1) % max_count_D_;
        choice_ = (count_D_ == 0) ? C : D;
        return;
    }

    choice_ = C;
}