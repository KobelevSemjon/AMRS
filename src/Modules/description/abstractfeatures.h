#ifndef SABSTRACTFEATURES_H
#define SABSTRACTFEATURES_H

#include <map>
#include <list>
#include <opencv2/opencv.hpp>

/*!
 * \ingroup Description
 * \brief Абстрактные признаки.
 * \details Абстрактный базовый класс для всех классов-описателей.
 * Обеспечивает единообразие по методам getHeader, getHeader и rebuild.
 */
class AbstractFeatures
{
public:
    //! \brief Пустой конструктор
    AbstractFeatures(){}

    //! \brief Перестраивание(перевычисление признаков) класса по новому полутоновому изображению.
    virtual void rebuild(const cv::Mat1b& , bool){}

    //! \brief Список имен классов(пустой).
    virtual std::list<std::string> getHeader(const std::string&){return {};}

    //! \brief Список из вычисленных классом значений признаков(пустой).
    virtual std::list<double> getFeatures(){return {};}

    //! \brief Пустой деструктор(виртуальный).
    virtual ~AbstractFeatures(){}
};

#endif // SABSTRACTFEATURES_H
