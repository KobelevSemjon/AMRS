#include "morphology.h"
/*!
 * \brief Конструктор по умолчанию
 */
Morphology::Morphology(){}

/*!
 * \brief Конструктор по одноканальному изображению.
 * \details Эквивалентен rebuild(src, true);
 * \param src - одноканальное изображение
 */
Morphology::Morphology(const cv::Mat1b &src)
{
    rebuild(src, true);
}
/*!
 * \brief Площадь (число не нулей)
 * \return площадь
 */
double Morphology::area(){return _area;}

/*!
 * \brief Периметр (сумма длин контуров)
 * \return
 */
double Morphology::perimeter(){return _perimeter;}

/*!
 * \brief Коэффициент формы.
 * \return (периметр^2)/(4.*pi)
 */
double Morphology::formCoef()
{
    double P = perimeter();
    return pow(P,2)/(4.*_pi);
}

/*!
 * \brief Максимальный линейный размер
 * \return диаметр описывающей окружности
 */
double Morphology::maxLinearDemention()
{
    using namespace cv;
    Point2f center;
    float radius;
    minEnclosingCircle(_contour, center, radius);
    return 2.*double(radius);
}

/*!
 * \brief Коэффициент вытянутости.
 * \return максимальный линейный размер/корень(4.*площадь/pi)
 */
double Morphology::elongCoef()
{
    double MLD = maxLinearDemention();
    return MLD/sqrt(4.*_area/_pi);
}
/*!
 * \brief Morphology::roundCoef - рассчет коэффициента округлости.
 * \details Рассчитывает коэффициент округлости по формуле (Rmax)/(Rmin + E),
 * где Rmax и Rmin - максимальные и минимальные расстояния от центра масс внешнего
 * контура до точек контура, E = numeric_limits<double>::epsilon().
 * \return Коэфициент окружности.
 */
double Morphology::roundCoef()
{
    using namespace cv;
    Moments M = moments(_contour);
    Point2d mass_center{M.m10/M.m00,M.m01/M.m00};

    auto ro = [](const Point2d& p1, const Point2d& p2)->double
    {
        return sqrt(pow(p1.x-p2.x,2) + pow(p1.y-p2.y,2));
    };

    double min = std::numeric_limits<double>::max();
    double max = std::numeric_limits<double>::min();

    for(Point p: _contour)
    {
        double distance = ro(p,mass_center);
        min = std::min(distance,min);
        max = std::max(distance,max);
    }
    double e = std::numeric_limits<double>::epsilon();
    return max/(min+e);

}
/*!
 * \brief Перевычисление.
 * \details Обеспечивает поиск контуров на src, рассчет площади, периметра, и поска наибольшего контура.
 * \param src - одноканальное изображение сегмента на черном фоне.
 */
void Morphology::rebuild(const cv::Mat1b & src, bool)
{
    using namespace cv;
    std::vector<std::vector<cv::Point>> contours;
    findContours(src, contours,noArray(),RETR_LIST,CHAIN_APPROX_NONE);
    _area = double(countNonZero(src));
    _perimeter = 0.;
    _contour = contours[0];
    double contour_area = 0;
    for(auto c: contours)
    {
        _perimeter += double(c.size());
        if (contour_area<contourArea(c))
            _contour = c;
    }
}

/*!
 * \brief Заголовок с названиями всех признаков
 * \details генерирует заголовок в ввиде  prefix+AREA, prefix+PERIM,  prefix+FORM, prefix+MLD, prefix+ELONG, prefix+ROUND
 * в указанном порядке.
 * \param prefix - префикс
 * \return лист из названий заголовков
 */
std::list<std::string> Morphology::getHeader(const std::string &prefix)
{
    std::list<std::string> header;
    header.push_back(prefix+"AREA");
    header.push_back(prefix+"PERIM");
    header.push_back(prefix+"FORM");
    header.push_back(prefix+"MLD");
    header.push_back(prefix+"ELONG");
    header.push_back(prefix+"ROUND");
    return header;
}

/*!
 * \brief Вычислить все признаки
 * \details генерирует лист признаков в порядке  AREA, PERIM, FORM, MLD, ELONG, ROUND.
 * \return лист из названий заголовков
 */
std::list<double> Morphology::getFeatures()
{
    std::list<double> features;
    features.push_back(area());
    features.push_back(perimeter());
    features.push_back(formCoef());
    features.push_back(maxLinearDemention());
    features.push_back(elongCoef());
    features.push_back(roundCoef());
    return features;
}
