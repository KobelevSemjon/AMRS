#ifndef DECISIONTREE_H
#define DECISIONTREE_H
#include <opencv2/ml.hpp>
#include <abstractclassifier.h>

/*!
 * \brief Не работает fit - sigsegf на train
 * \details Используйте лес деревьев в числом деревьев = 1
 * \deprecated
 */

class DecisionTree: public TemplateClassifier<DTrees>
{
    virtual void setDefault();
public:
    DecisionTree()
        :TemplateClassifier<DTrees>(){}
    DecisionTree(const cv::String& filepath)
        :TemplateClassifier<DTrees>(filepath){}
    /***************setters**************/

    void setMaxDepth(int depth)
    {
        _clf->setMaxDepth(depth);
    }
    void setRegressionAccuracy(float acc = 0.01f)
    {
        _clf->setRegressionAccuracy(acc);
    }
    virtual void fit(const Mat1f & samples, const Mat1f & answers_column);

};

#endif // DECISIONTREE_H
