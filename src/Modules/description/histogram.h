#ifndef SHISTOGRAM_H
#define SHISTOGRAM_H
#include <abstractfeatures.h>
#include <opencv2/opencv.hpp>
#include <limits>
/*!
 * \ingroup Description
 * \brief Класс гистограммы яркостей.
 * \details Служит для расчета гистограммных признаков по полутоновому изображению.
 * С помощью класса можно вычислить 4 признака:
 *  - MIN(минимальная яркость),
 *  - MAX(максимальная яркость),
 *  - MX(средняя яркость),
 *  - SD(СКО)
 * Коды признаков: MIN, MAX, MX, SD
 */
class Histogram:public AbstractFeatures
{   
    std::map<int,int> bars;
    int min_key,max_key;
    int sum=0;

    inline void ignoreZero();
public:
    Histogram();
    Histogram(const cv::Mat1b& src, bool ignore_zero=true);
    double min() const;
    double max() const;
    double MX();
    double SD(double mx=std::numeric_limits<double>::max());

    virtual void rebuild(const cv::Mat1b& src, bool ignore_zero=true);
    std::list<std::string> getHeader(const std::string& predicat="");
    std::list<double> getFeatures();
};

#endif // SHISTOGRAM_H
