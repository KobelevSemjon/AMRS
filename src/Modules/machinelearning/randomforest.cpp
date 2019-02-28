#include "randomforest.h"

void RandomForest::setDefault()
{
    auto tc = TermCriteria(TermCriteria::COUNT, _trees_count, 0.1);
    _clf->setTermCriteria(tc);
}

void RandomForest::setTreesCount(int trees_count)
{
    _trees_count = trees_count;
}

int RandomForest::getTreesCount()
{
    auto criteria = _clf->getTermCriteria();
    return criteria.maxCount;
}

string RandomForest::getParams()
{
    std::stringstream ss;
    ss << "{TreesCount = " << getTreesCount() << "}";
    return ss.str();
}

