#include "histogram.h"

/*!
 * \brief Игнорирование черного фона.
 * \details Удаляет нулевую колонку гистограммы. При этом пересчитывается минимальное и максимальное значения яркости.
 */
void Histogram::ignoreZero()
{
    sum-=bars[0];
    bars.erase(0);
    if (min_key==0)
        min_key=bars.begin()->first;
    if (max_key==0)
        max_key=bars.rbegin()->first;
}

/// \brief Пустой конструктор.
Histogram::Histogram(){}

/*!
 * \brief Конструктор по изображению.
 * \details Строит гистограмму по полутоновому изображению. По сути является вызовом метода rebuild.
 * \param src - полутоновое изображение
 * \param ignore_zero - игнорирование черного фона
 */
Histogram::Histogram(const cv::Mat1b &src, bool ignore_zero)
{
    rebuild(src,ignore_zero);
}

/*!
 * \brief Поиск минимальной яркости.
 * \return минимальная яркость
 */
double Histogram::min() const {return min_key;}


/*!
 * \brief Поиск максимальной яркости.
 * \return максимальной яркости
 */
double Histogram::max() const {return max_key;}

/*!
 * \brief Вычисление средней яркости.
 * \details Происходит по формуле: сумма (i*bars[i])/число пикселей с учетом флага ignore_zero.
 * \return средняя яркость
 */
double Histogram::MX()
{
    double av=0;
    for(int i=min_key;i<=max_key;++i)
        av+=double(i*bars[i]);
    av/=double(sum);
    return av;
}

/*!
 * \brief Вычисление среднеквадратического отклонения.
 * \details В целях оптимизации вычислений в метод передается значение средней яркости в качестве аргумента.
 * Если оставить значение аргумента по умолчанию (std::numeric_limits<int>::max() - максимальное значение int), то
 * средняя яркость будет вычислена. Рассчет производится по формуле: сумма (bars[i]*(i-MX)^2)/число пикселей с учетом флага
 * ignore_zero.
 * \param mx - средняя яркость(опционально)
 * \return СКО
 */
double Histogram::SD(double mx)
{
    if (mx == std::numeric_limits<double>::max())
        mx=MX();
    double dv=0;
    for(int i=min_key;i<=max_key;++i)
        dv+=double(bars[i]*(i-mx)*(i-mx));
    dv/=double(sum);
    return sqrt(dv);
}

/*!
 * \brief Перевычисление гистограммы.
 * \details Осуществляет пересчет гистограммы по новому полутоновому изображению и указанному флагу фона.
 * \param src - полутоновое изображение
 * \param ignore_zero - игнорирование черного фона
 */
void Histogram::rebuild(const cv::Mat1b &src, bool ignore_zero)
{
    min_key=max_key=src(0,0);
    bars.clear();
    for(int r=0;r<src.rows;++r)
        for(int c=0;c<src.cols;++c)
        {
            int key=src(r,c);
            if (key<min_key) min_key=key;
            if (max_key<key) max_key=key;
            ++bars[key];
        }    
    sum=src.rows*src.cols;
    if (ignore_zero) ignoreZero();
}

/*!
 * \brief Создание листа с названиями признаков.
 * \details К названиям признаков можно добавлять некоторую приставку.
 * Итоговое название признака будет складываться из приставки и оригинального названия.
 * Например "Blue_MIN" - минимальная яркость по синему каналу. "Blue" в данном примере является приставкой.
 * \param prefix - приставка
 * \return лист с названиями признаков
 */
std::list<std::__cxx11::string> Histogram::getHeader(const std::string& prefix)
{
    std::list<std::string> header;
    header.push_back(prefix+"MIN");
    header.push_back(prefix+"MAX");
    header.push_back(prefix+"MX");
    header.push_back(prefix+"SD");
    return header;
}

/*!
 * \brief Создание листа со значениями признаков.
 * \details Признаки распологаются в том же порядке, что и в getHeader.
 * \return лист со значениями признаков
 */
std::list<double> Histogram::getFeatures()
{
    std::list<double> features;
    features.push_back(min());
    features.push_back(max());
    double average = MX();
    features.push_back(average);
    features.push_back(SD(average));
    return features;
}

