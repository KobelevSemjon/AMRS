#ifndef RANDOMFOREST_H
#define RANDOMFOREST_H

#include "abstractclassifier.h"

class RandomForest:public TemplateClassifier<RTrees>
{
    int _trees_count = 1;
    virtual void setDefault();
public:
    RandomForest():TemplateClassifier<RTrees>(){}
    RandomForest(const String& filepath):
    TemplateClassifier<RTrees>(filepath){}
    /***************setters**************/

    void setTreesCount(int trees_count = 1);
    int getTreesCount();
    string getParams();
};

#endif // RANDOMFOREST_H
