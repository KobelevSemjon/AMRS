#ifndef BOOSTEDDECISIONTREE_H
#define BOOSTEDDECISIONTREE_H

#include "abstractclassifier.h"

class BoostedDecisionTree:public TemplateClassifier<Boost>
{
    virtual void setDefault();
public:
    BoostedDecisionTree(){}
    BoostedDecisionTree(const String& filepath):
    TemplateClassifier<Boost>(filepath){}

    /***************setters**************/

    void setWeakCount(int trees_count = 100);

    /***************getters**************/

    int getWeakCount();
    string getParams();

};

#endif // BOOSTEDDECISIONTREE_H
