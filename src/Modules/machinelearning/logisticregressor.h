#ifndef LOGISTICREGRESSOR_H
#define LOGISTICREGRESSOR_H

#include "abstractclassifier.h"

class LogisticRegressor:public TemplateClassifier<LogisticRegression>
{
    virtual void setDefault();
public:
    LogisticRegressor(){}
    LogisticRegressor(const String& filepath):
    TemplateClassifier<LogisticRegression>(filepath){}

    /***************setters**************/

    virtual void setIterations (int val = 100);
    virtual void setLearningRate (double val = 0.01);
    virtual void setRegularization (int val = LogisticRegression::RegKinds::REG_L2);

    /***************getters**************/
    int getIterations();
    double getLearningRate();
    int getRegularization();
    string getParams();
};

#endif // LOGISTICREGRESSOR_H
