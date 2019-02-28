#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H

#include <abstractfeatures.h>
#include <opencv2/opencv.hpp>

/*!
 * \ingroup Description
 * \brief Класс рассчета морфологических признаков.
 * \details Служит для расчета морфологических признаков по полутоновому изображению.
 * С помощью класса можно вычислить 6 признаков:
 *  - AREA(площадь),
 *  - PERIM(периметр),
 *  - FORM(коэффициент формы),
 *  - MLD(максимальный линейный размер),
 *  - ELONG(коэффициент вытянутости)
 *  - ROUND(коэффициент округлости внешнего контура)
 * Коды признаков: AREA, PERIM, FORM, MLD, ELONG, ROUND
 */

class Morphology:public AbstractFeatures
{
    std::vector<cv::Point> _contour;
    double _area, _perimeter;
    double _pi = M_PI;
public:
    Morphology();
    Morphology(const cv::Mat1b& src);

    double area();
    double perimeter();
    double formCoef();
    double maxLinearDemention();
    double elongCoef();
    double roundCoef();

    virtual void rebuild(const cv::Mat1b& , bool);
    virtual std::list<std::string> getHeader(const std::string& prefix = "");
    virtual std::list<double> getFeatures();


};

#endif // MORPHOLOGY_H
