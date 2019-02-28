#ifndef MLPREGRESSOR_H
#define MLPREGRESSOR_H

#include <abstractclassifier.h>

/*! \ingroup MachineLearning
 * \brief Класс многослойного персептрона.
 * \details Является оберткой для ANN_MLP из opencv.
 * https://docs.opencv.org/3.4.0/d0/dce/classcv_1_1ml_1_1ANN__MLP.html
 */
//template<>
//class AbstractClassifier<ANN_MLP>;

class MLPRegressor: public TemplateClassifier<ANN_MLP>
{
    Mat _layer_sizes;//column
    virtual void setDefault();
public:
    MLPRegressor(){}
    MLPRegressor(const cv::String& filepath)
        :TemplateClassifier<ANN_MLP>(filepath){}

    void setLayerSizes(const std::vector<ushort>& hidden_layer_sizes = {});
    vector<int> getLayerSizes();

    virtual void fit(const Mat1f &samples, const Mat1f& answers_column);
    string getParams();
};

#endif // MLPREGRESSOR_H
