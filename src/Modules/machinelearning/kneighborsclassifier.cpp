#include "kneighborsclassifier.h"

void KNeighborsClassifier::setDefault()
{
    //_clf->setIsClassifier(true);//!true

}

void KNeighborsClassifier::setDefaultK(int k_neigh)
{
    _clf->setIsClassifier(true);//!true
    /*!
If the algorithm is set to BRUTE_FORCE, this training data is simply stored internally as
an array and then scanned sequentially in order to find the nearest neighbors. In the
case of KDTree, the BBF (best-bin-first) algorithm (introduced by D. Lowe) will be
used, which is much more efficient when features ≪ log(samples).*/
    _clf->setAlgorithmType(KNearest::Types::BRUTE_FORCE);
    _clf->setDefaultK(k_neigh);
}

int KNeighborsClassifier::getDefaultK()
{
    return _clf->getDefaultK();
}

string KNeighborsClassifier::getParams()
{
    std::stringstream ss;
    ss << "{DefaultK = " << getDefaultK() << "}";
    return ss.str();
}
