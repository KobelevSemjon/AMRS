#ifndef SUPPORTVECTORMACHINES_H
#define SUPPORTVECTORMACHINES_H

#include "abstractclassifier.h"
#include "metrics.h"

class SupportVectorMachines:public TemplateClassifier<SVM>
{
    //bool _need_inv_for_predict = false;
    void setDefault();
public:
    SupportVectorMachines();
    SupportVectorMachines(const String& filepath):
    TemplateClassifier<SVM>(filepath){}
    /***************setters**************/
    virtual void fit(const cv::Mat1f &samples, const cv::Mat1f& answers_column);
    Mat1f predict(const Mat1f &samples);

    void setKernel(int kernel_type);
    void setC(double penalty);
    //void setNeedInv(bool is_need = false);
    void setGamma(double gamma);
    void setCoef0(double coef0);
    void setDegree(double degree);

    double getDegree();
    double getCoef0();
    double getGamma();
    double getC();
    int getKernel();

    string getParams();

};

#endif // SUPPORTVECTORMACHINES_H
