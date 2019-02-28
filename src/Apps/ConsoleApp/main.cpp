#include <QCoreApplication>
#include <QtDebug>
#include <opencv2/opencv.hpp>
#include "machinelearning.h"

int main(int argc, char *argv[])
{
    using namespace cv;
    QCoreApplication a(argc, argv);
    int rows = 500, cols = 2;

    cout<< "train sample generation" << endl;
    Mat1f S(rows,cols);
    Mat1i A(rows,1);
    cv::randn(S,{0},{1});
    for(int i = 0; i<rows; ++i)
    {
        float x = S[i][0];
        float y = S[i][1];
        A[i][0] = (x-y < 0);
    }
    cout<< "classifier learning" << endl;
    //BoostedDecisionTree clf;
    //clf.setBoostType();
    //clf.setWeakCount();

    SupportVectorMachines clf;
    clf.setKernel(SVM::KernelTypes::RBF);
    clf.setC(10);
    //clf.setNeedInv()
    //clf.setP(0.1);
    clf.setCoef0(0);
    clf.setGamma(1);
    //A(0,0) = 0;
    clf.fit(S,A);
    //std::cout<<endl;

    cout<< "accuracy check" << endl;
    Mat1f St(100,cols);
    cv::randn(St,{0},{1});
    Mat1i At(100,1);
    Mat1f P = clf.predict(St);
    for(int i = 0; i<100; ++i)
    {
        float x = St[i][0];
        float y = St[i][1];
        At[i][0] = (x-y < 0);
        cout << i<<":" << x-y<< "<0? " << At[i][0] << "==" << P[i][0]  << endl;
    }
    auto cm = createConfusionMatrix(At,P,0);
    cout << cm.accuracy();

    return a.exec();
}
