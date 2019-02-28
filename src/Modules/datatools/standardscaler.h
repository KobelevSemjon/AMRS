#ifndef STANDARDSCALER_H
#define STANDARDSCALER_H

#include <math.h>
#include <regex>
#include "dataframe.h"
/*!
 * \ingroup Datatools
 * \brief Скалер (Класс Стандартной нормировки).
 */
struct StandardScaler
{
    double _mx;
    double _sd;

    StandardScaler(){}
    StandardScaler(double mx, double sd);
    double operator()(double value) const;
};

template<class Iterable>
/*!
 * \ingroup Datatools
 * \brief Обучить Скалер.
 * \param container - итерируемый double
 * \return Скалер.
 */
StandardScaler fit_scaler(Iterable container)
{
    size_t size=0;
    double mx = 0, dx = 0, sd = 0;
    for(auto value: container)
    {
        mx += value;
        ++size;
    }
    mx/=size;
    for(auto value: container)
    {
        dx += pow(value-mx,2);
    }
    dx/=size;
    sd = sqrt(dx);
    return StandardScaler(mx,sd);
}

/*!
 * \ingroup Datatools
 * \brief Табличный Скалер
 * \details Служит для нормировки значений колонок таблиц на их среднее и дисперсию.
 */
class StandardTableScaler
{
    std::vector<StandardScaler> _column_scalers;
public:
    StandardTableScaler(){}

    void fit(const DataFrame& df);
    void transform(DataFrame& df) const;
    void transform(ObjectDescription& od) const;

    std::string toStdString() const;
    void fromStdString(const std::string& scaler_str);
    bool save(const std::string& path) const;
    StandardTableScaler(const std::string& path);
    size_t size();
};



#endif // STANDARDSCALER_H
