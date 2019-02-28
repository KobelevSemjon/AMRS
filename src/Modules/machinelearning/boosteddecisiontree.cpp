#include "boosteddecisiontree.h"

void BoostedDecisionTree::setDefault()
{
    _clf->setBoostType(cv::ml::Boost::Types::LOGIT);
}

void BoostedDecisionTree::setWeakCount(int trees_count)
{
    _clf->setWeakCount(trees_count);
}

int BoostedDecisionTree::getWeakCount()
{
    return _clf->getWeakCount();
}

string BoostedDecisionTree::getParams()
{
    std::stringstream ss;
    ss << "{WeakCount = " << getWeakCount() << "}";
    return ss.str();
}
