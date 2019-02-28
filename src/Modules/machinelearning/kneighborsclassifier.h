#ifndef KNEIGHBORSCLASSIFIER_H
#define KNEIGHBORSCLASSIFIER_H
#include <opencv2/ml.hpp>
#include <abstractclassifier.h>
/*!
 * \brief The KNeighborsClassifier class
 * \details https://docs.opencv.org/3.4.0/dc/dd6/ml_intro.html#ml_intro_knn
 */
class KNeighborsClassifier: public TemplateClassifier<KNearest>
{
    virtual void setDefault();
public:
    KNeighborsClassifier()
        :TemplateClassifier<KNearest>(){}
    KNeighborsClassifier(const cv::String& filepath)
        :TemplateClassifier<KNearest>(filepath){}
    /***************setters**************/

    void setDefaultK(int k_neigh);

    /***************getters**************/
    int getDefaultK();
    string getParams();
};

#endif // KNEIGHBORSCLASSIFIER_H
