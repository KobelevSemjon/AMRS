#ifndef ABSTRACTCLASSIFIER_H
#define ABSTRACTCLASSIFIER_H

#include <opencv2/ml.hpp>
#include <fstream>

using namespace std;
using namespace cv;
using namespace cv::ml;

struct AbstractClassifier
{
    AbstractClassifier(){}
    virtual void save(const cv::String &){}
    virtual void loadFromString(const std::string& ){}
    virtual std::string saveToString(){return "";}
    virtual void fit(const cv::Mat1f&, const cv::Mat1f&){}
    virtual cv::Mat1f predict(const cv::Mat1f &){return cv::Mat1f();}
    virtual float predict_for(const cv::Mat1f &){return 0;}
    virtual string getParams(){return "";}
    virtual ~AbstractClassifier(){}
};

template <typename _StatModel>
class TemplateClassifier: public AbstractClassifier
{
protected:
    bool _is_valid = false;
    virtual void setDefault();
    cv::Ptr<_StatModel> _clf;
public:
    TemplateClassifier();
    TemplateClassifier(const cv::String& filepath);
    bool isValid() const;
    virtual void save(const cv::String &xmlfile);
    virtual void loadFromString(const std::string& str_model);
    virtual std::string saveToString();
    virtual void fit(const cv::Mat1f &samples, const cv::Mat1f& answers_column);
    virtual cv::Mat1f predict(const cv::Mat1f &samples);
    virtual float predict_for(const cv::Mat1f &sample_row); 
    virtual string getParams();
    virtual ~TemplateClassifier();
};

//gcc не поддерживает export template,приходится мучиться
template<typename _StatModel>
TemplateClassifier<_StatModel>::TemplateClassifier()
{
    _clf = _StatModel::create();
}

template<typename _StatModel>
TemplateClassifier<_StatModel>::TemplateClassifier(const String &filepath)
{
    _clf = cv::Algorithm::load<_StatModel>(filepath, String());
    _is_valid = true;
}

template<typename _StatModel>
bool TemplateClassifier<_StatModel>::isValid() const
{
    return _is_valid;
}

template<typename _StatModel>
void TemplateClassifier<_StatModel>::save(const String &xmlfile)
{
    _clf->save(xmlfile);
}

template<typename _StatModel>
void TemplateClassifier<_StatModel>::loadFromString(const string &str_model)
{
    _clf = cv::Algorithm::loadFromString<_StatModel>(str_model);
}

template<typename _StatModel>
std::string TemplateClassifier<_StatModel>::saveToString()
{
    std::string path = "temp_cash.xml";
    remove(path.c_str());
    save(path);
    std::ifstream fin(path.c_str());
    if(fin.is_open())
    {
        std::string str((std::istreambuf_iterator<char>(fin)),
                        std::istreambuf_iterator<char>());
        fin.close();
        return str;
    }
    return "";
}

template<typename _StatModel>
void TemplateClassifier<_StatModel>::fit(const Mat1f &samples, const Mat1f& answers_column)
{
    setDefault();
    _clf->train(samples,cv::ml::SampleTypes::ROW_SAMPLE,answers_column);
    _is_valid = true;
}

template<typename _StatModel>
void TemplateClassifier<_StatModel>::setDefault(){}

template<typename _StatModel>
Mat1f TemplateClassifier<_StatModel>::predict(const Mat1f &samples)
{
    cv::Mat prediction;
    _clf->predict(samples,prediction,StatModel::RAW_OUTPUT);
    assert(prediction.depth() == cv::DataType<float>::depth);
    return Mat1f(prediction);
}

template<typename _StatModel>
float TemplateClassifier<_StatModel>::predict_for(const Mat1f &sample_row)
{
    cv::Mat1f prediction = predict(sample_row);
    float value = prediction.at<float>(0,0);
    return value;
}

template<typename _StatModel>
string TemplateClassifier<_StatModel>::getParams()
{
    return "";
}

template<typename _StatModel>
TemplateClassifier<_StatModel>::~TemplateClassifier(){}

#endif // ABSTRACTCLASSIFIER_H


