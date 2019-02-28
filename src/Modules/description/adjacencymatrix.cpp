#include "adjacencymatrix.h"
/*!
 * \brief Вычисление МПС для изображения.
 * \details Учитывает краевые пиксели изображения.
 * \param img - полутоновое изображение
 */
inline void AdjacencyMatrix::calculate(const cv::Mat1b &img)
{    
//    img.forEach([&](uchar center, const int* pos)
//    {
//        int x = pos[1], y = pos[0];
//        cv::Rect rect({0,0},img.size());
//        for(int i=-radius;i<=radius;++i)for(int j=-radius;j<=radius;++j)
//        {
//            int xn=x+i,yn=y+j;
//            if (rect.contains({xn,yn}))//img.isValidPos(xn,yn))
//            {
//                int neighbor=img({xn,yn});
//                ++matrix[center][neighbor];
//            }
//            --matrix[center][center];
//        }
//    });
    for(int y=0;y<img.rows;++y)for(int x=0;x<img.cols;++x)
        {
            int center=img({x,y});
            for(int i=-radius;i<=radius;++i)for(int j=-radius;j<=radius;++j)
            {
                int xn=x+i,yn=y+j;                
                if (cv::Rect({0,0},img.size()).contains({xn,yn}))//img.isValidPos(xn,yn))
                {
                    int neighbor=img({xn,yn});
                    ++matrix[center][neighbor];
                }                
            }
            --matrix[center][center];
        }
}

/*!
 * \brief Игнорирование черного фона.
 * \details Зануляет 0 строку и стобец матрицы смежности.
 */
void AdjacencyMatrix::ignoreZero()
{
    for( auto& m: matrix)
    {
        matrix[0][m.first]=0;
        matrix[m.first][0]=0;
    }
}

/*!
 * \brief Конструктор по радиусу смежности.
 * \details Устнавливает радиус смежности, который нельзя впоследствии изменить.
 * \param radius - радиус смежности
 * \warning Отсутствует контроль redius<1.
 */
AdjacencyMatrix::AdjacencyMatrix(int radius):radius(radius)
{}

/*!
 * \brief Конструктор по изображению.
 * \details Строит МПС с указанным радиусом смежности и флагом фона для полутонового изображения.
 * \param img - полутоновое изображение.
 * \param radius - радиус смежности
 * \param ignore_zero - игнорирование черного фона
 * \warning Отсутствует контроль redius<1 и валидности img.
 */
AdjacencyMatrix::AdjacencyMatrix(const cv::Mat1b &img, int radius, bool ignore_zero):radius(radius)
{rebuild(img,ignore_zero);}

/*!
 * \brief Вычисление Энергии.
 * \details Энергия = отношение суммы квадратов элементов матрицы к числу пикселей.
 * \return энергия
 */
double AdjacencyMatrix::energy()
{
    using namespace std;
    double energy=0;
    for(auto& r: matrix)
    {
        int y=r.first;
        for(auto& c: matrix)
        {
            int x=c.first;
            energy+=(double(matrix[x][y])*double(matrix[x][y]));
        }
    }
    energy/=double(elements);
    assert(energy>=0);
    return energy;
}

/*!
 * \brief Вычисление Энтропии.
 * \details Энтропия равна сумме (N*log(N) если (0<N), иначе 0), нормированной на число пикселей, где N - элемент матрицы смежности.
 * \return энтропия
 */
double AdjacencyMatrix::entropy()
{
    double entropy=0;
    for(auto& r: matrix)
    {
        int y=r.first;
        for(auto& c: matrix)
        {
            int x=c.first;
            double N=matrix[x][y];
            if (0<N) entropy+=N*log(N);
        }
    }
    entropy/=double(elements);
    return entropy;
}

/*!
 * \brief Вычисление Локальной однородности.
 * \details Локальная однородность равна сумме (элемент_матрицы[x][y]/(1+(x-y)^2), нормированной на число пикселей.
 * \return локальная однородность
 */
double AdjacencyMatrix::localHomogenity()
{
    double homogenity=0;
    for(auto& r: matrix)
    {
        int y=r.first;
        for(auto& c: matrix)
        {
            int x=c.first;
            homogenity+=double(matrix[x][y])/(1+(x-y)*(x-y));
        }
    }
    homogenity/=double(elements);
    return homogenity;
}

/*!
 * \brief Вычисление Максимальной вероятности.
 * \details Максимальная вероятность равна максимальному из значений ячеек матрицы смежности, нормированному на число пикселей.
 * \return максимальная вероятность
 */
double AdjacencyMatrix::maxProbability()
{
    double max_p=0;
    for(auto& r: matrix)
    {
        int y=r.first;
        for(auto& c: matrix)
        {
            int x=c.first;
            if (max_p<matrix[x][y]) max_p=matrix.at(x).at(y);
        }
    }
    max_p/=double(elements);
    return max_p;
}

/*!
 * \brief Вычисление Момента инерции.
 * \details Момент инерции равен сумме (элемент_матрицы[x][y]*(x-y)^2), нормированной на число пикселей.
 * \return момент инерции
 */
double AdjacencyMatrix::inertiaMoment()
{
    double iner=0;
    for(auto& r: matrix)
    {
        int y=r.first;
        for(auto& c: matrix)
        {
            int x=c.first;
            iner+=double(matrix[x][y])*(x-y)*(x-y);
        }
    }
    iner/=double(elements);
    return iner;
}

/*!
 * \brief Вычисление Следа МПС.
 * \details След МПС равен сумме диагональных элементов, нормированной на число пикселей.
 * \return след МПС
 */
double AdjacencyMatrix::trail()
{
    double tr=0;
    for(auto& r: matrix)
    {
        int i=r.first;
        tr+=matrix[i][i];
    }
    tr/=double(elements);
    assert(tr>=0);
    return tr;
}

/*!
 * \brief Вычисление Средней яркости.
 * \details Средняя яркость равна сумме по y (y * сумма по х(matrix[x][y])), нормированной на число пикселей.
 * \return средняя яркость
 */
double AdjacencyMatrix::averageBrightness()
{
    double av=0,buffer;
    for(auto& r: matrix)
    {
        int y=r.first;
        buffer=0;
        for(auto& c: matrix)
        {
            int x=c.first;
            buffer+=matrix[x][y];
        }
        av+=y*buffer;
    }
    av/=double(elements);
    assert(av>=0);
    return av;
}


/*!
 * \brief Оператор сравнения.
 * \details Две матрицы считаются равными если соответствующие элементы матрицы МПС равны между собой.
 * \param other - сравниваемая МПС
 * \return true - если равны
 */
bool AdjacencyMatrix::operator==(const AdjacencyMatrix &other) const
{
    return (matrix==other.matrix);
}

/*!
 * \brief Перевычисляет МПС.
 * \details Осуществляет перевычисление матрицы смежности по указанному полутоновому изображению и значению флага фона.
 * Не меняет значение радиуса смежности.
 * \param img - полутоновое изображение
 * \param ignore_zero - игнорирование черного фона
 */
void AdjacencyMatrix::rebuild(const cv::Mat1b &img, bool ignore_zero)
{
    elements=img.rows*img.cols;
    calculate(img);
    if (ignore_zero)
    {
        for(int y=0;y<img.rows;++y)for(int x=0;x<img.cols;++x)
            if (img({x,y})==0)
                --elements;
        assert(elements>=0);
        ignoreZero();
    }
}

/*!
 * \brief Создание листа с названиями признаков.
 * \details К названиям признаков можно добавлять некоторую приставку.
 * Итоговое название признака будет складываться из приставки и оригинального названия.
 * Например "Blue_1_Energy" - Энергия по МПС с шагом(радиусом)=1 по синему каналу. "Blue" в данном примере является приставкой.
 * \param prefix - приставка
 * \return лист с названиями признаков
 */
std::list<std::__cxx11::string> AdjacencyMatrix::getHeader(const std::string& prefix)
{
    using namespace std;
    list<string> header;
    string str=prefix+to_string(radius);
    header.push_back(str+"_Energy");
    header.push_back(str+"_ENT");
    header.push_back(str+"_LUN");
    header.push_back(str+"_MPR");
    header.push_back(str+"_CON");
    header.push_back(str+"_TR");
    header.push_back(str+"_AV");
    return header;
}

/*!
 * \brief Создание листа со значениями признаков.
 * \details Признаки распологаются в том же порядке, что и в getHeader.
 * \return лист со значениями признаков
 */
std::list<double> AdjacencyMatrix::getFeatures()
{
    std::list<double> features;
    features.push_back(energy());
    features.push_back(entropy());
    features.push_back(localHomogenity());
    features.push_back(maxProbability());
    features.push_back(inertiaMoment());
    features.push_back(trail());
    features.push_back(averageBrightness());
    return features;
}
/* работает странно
double SAdjacencyMatrix::correlationBrightness(double av) const
{
    if (av<0) av=averageBrightness();
    double nsum,dsum,numerator=0,denominator=0;
    for(int i=0;i<256;++i)
    {
        nsum=0,dsum=0;
        for(int j=0;j<256;++j)
        {
            nsum+=(j-av)*matrix[i][j];
            dsum+=matrix[i][j];
        }
        numerator+=(i-av)*nsum;
        denominator+=(i-av)*(i-av)*dsum;
    }
    double corr=numerator/denominator;
    return corr;
}
*/


