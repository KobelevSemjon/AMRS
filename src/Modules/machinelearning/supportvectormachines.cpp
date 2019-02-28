#include "supportvectormachines.h"

void SupportVectorMachines::fit(const Mat1f &samples, const Mat1f &answers_column)
{
    setDefault();
    Mat1i _answers_column(answers_column.size());
    answers_column.copyTo(_answers_column);
    Ptr<TrainData> data = TrainData::create(Mat(samples),cv::ml::SampleTypes::ROW_SAMPLE,_answers_column);
    _clf->train(data);


    //Mat1f responses = predict(samples);
    //auto cm = createConfusionMatrix(answers_column, responses, 0);
    //_need_inv_for_predict = (cm.accuracy() < 0.5);
}

Mat1f SupportVectorMachines::predict(const Mat1f &samples)
{
    cv::Mat prediction;
    _clf->predict(samples,prediction,StatModel::RAW_OUTPUT);

    assert(prediction.depth() == cv::DataType<float>::depth);
    //if(_need_inv_for_predict) prediction = -prediction;

    return Mat1f(0.5-prediction);//always - 0 and 1 classifying
}

void SupportVectorMachines::setDefault()
{

}

SupportVectorMachines::SupportVectorMachines()
{
    _clf->setType(SVM::Types::C_SVC);
}

void SupportVectorMachines::setKernel(int kernel_type)
{
    _clf->setKernel(kernel_type);
}

void SupportVectorMachines::setC(double penalty)
{
    //Penalty parameter C of the error term.
    _clf->setC(penalty);
}

//void SupportVectorMachines::setNeedInv(bool is_need)
//{
    //_need_inv_for_predict = is_need;
//}

void SupportVectorMachines::setGamma(double gamma)
{
     _clf->setGamma(gamma);
}

void SupportVectorMachines::setCoef0(double coef0)
{
    _clf->setCoef0(coef0);
}

void SupportVectorMachines::setDegree(double degree)
{
    _clf->setDegree(degree);
}

double SupportVectorMachines::getDegree()
{
    return _clf->getDegree();
}

double SupportVectorMachines::getCoef0()
{
    return _clf->getCoef0();
}

double SupportVectorMachines::getGamma()
{
    return _clf->getGamma();
}

double SupportVectorMachines::getC()
{
    return _clf->getC();
}

int SupportVectorMachines::getKernel()
{
    return _clf->getKernelType();
}

string SupportVectorMachines::getParams()
{
    std::stringstream ss;
    ss << "{Kernel = ";
    switch (getKernel()) {
    case 1: ss << "LINEAR; "; break;
    case 2:
        ss << "POLY {Gamma = " << getGamma()
           << ", Coef0 = " << getCoef0()
           << ", Degree = " << getDegree() << "};\n";
        break;
    case 3: ss << "RBF {Gamma = " << getGamma()
                << "};\n";
        break;
    case 4: ss << "SIGMOID {Gamma = " << getGamma()
               << ", Coef0 = " << getCoef0()<< "};\n";
        break;
    case 5: ss << "CHI2 {Gamma = " << getGamma() << "};\n";
        break;
    case 6: ss << "INTER;\n"; break;
    default: ss << "UNKNOWN;\n";
    }
    ss << "C = " << getC() << "}";
    return ss.str();
}
