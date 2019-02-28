#ifndef MACHINELEARNING_H
#define MACHINELEARNING_H

#include <list>
#include "abstractclassifier.h"
#include "boosteddecisiontree.h"
#include "decisiontree.h"
#include "randomforest.h"
#include "mlpregressor.h"
#include "logisticregressor.h"
#include "kneighborsclassifier.h"
#include "supportvectormachines.h"
#include "metrics.h"

/*! \defgroup MachineLearning
 * \brief Модуль классификации.
 * \details Содержит классы и методы, необходимые для подготовки данных, обучения, сохранения и загрузки
 * многослойного персептрона, а также метрики качества полученных решений.
 */

template<typename _FirTableType, typename _SecTableType, typename _Rect>
/*! \ingroup MachineLearning
 * \brief Конвертация таблиц разных типов.
 * \param src - копируемая таблица
 * \param dst - изменяемая таблица
 * \param rect - область копирования.
 */
void table2table(const _FirTableType& src, _SecTableType& dst, _Rect rect)
{

    for(auto r = rect.y; r < rect.y + rect.height; ++r)
        for(auto c = rect.x; c < rect.x + rect.width;++c)
            dst[r][c]=src[r][c];
}

/*! \ingroup MachineLearning
 * \brief Тасование строк изображения.
 * \details Результаты тасования воспроизводимы.
 * \param matrix - изображение(таблица).
 * \param seed - зерно генератора случайных чисел.
 * \return Перетасованное изображение.
 */
cv::Mat shuffleRows(const cv::Mat &matrix, int seed = 0);

template<typename _Df>
/*! \ingroup MachineLearning
 * \brief Создать выборку.
 * \details Для двух таблиц с примерами положительного и отрицательного классов
 * создает выборку и столбец ответов (предварительно перемешав строки). (Метки 0 и 1)
 * \param positive - таблица с положительными примерами (признаки-колонки, объекты-строчки)
 * \param negative - таблица с отрицательными примерами (признаки-колонки, объекты-строчки)
 * \param seed- зерно генератора случайных чисел
 * \return pair<sample,answers>
 */
std::pair<Mat1f,Mat1f> createSample(const _Df& positive, const _Df& negative, int seed = 0)
{
    using namespace cv;
    using namespace std;
    const _Df& pos = positive;
    const _Df& neg = negative;
    if(pos.cols()!=neg.cols()) throw std::invalid_argument("createSample: positive.cols()!=negative.cols())");
    int rows = pos.rows()+neg.rows();
    int cols = pos.cols();

    Mat1i XY = cv::Mat1i::zeros(pos.rows(),cols+1);
    table2table(pos,XY,Rect{0,0,cols,pos.rows()});

    Mat1i neg_sample = cv::Mat1i::zeros(neg.rows(),cols+1);
    table2table(neg,neg_sample,Rect{0,0,cols,neg.rows()});

    XY.push_back(neg_sample);

    int i=0;
    for(; size_t(i)<pos.rows();++i) XY(i,cols)=1;
    for(; i<rows; ++i) XY(i,cols)=0;

    XY = shuffleRows(XY, seed);
    Mat1i X = XY(Rect{0,0,cols,XY.rows});
    Mat1i Y = XY.col(cols);

    return std::make_pair(X,Y);
}

/*! \ingroup MachineLearning
 * \brief Случайно разбить на 2 выборки в соотношении (1-size)/size.
 * \param matrix - суммарная выборка с колонкой ответов.
 * \param size - доля 2 выборки от суммарной.
 * \param seed - зерно
 * \return <train,test>
 */
std::pair<Mat1f,Mat1f> random_split(Mat1f matrix, double size = 0.2, int seed = 0);

/*! \ingroup MachineLearning
 * \brief Разбиение X_train, y_train, X_test, y_test.
 * \param X - суммарная выборка с признаками.
 * \param y - колонка ответов.
 * \param size - доля test выборки от суммарной.
 * \param seed - зерно
 * \return X_train, y_train, X_test, y_test
 */
std::tuple<Mat1f,Mat1f,Mat1f,Mat1f> train_test_split(const Mat1f& X, const Mat1f& y, double size = 0.2, int seed = 0);

/*! \ingroup MachineLearning
 * \brief Посчитать кол-во "+" и "-" примеров в выборке.
 * \param y - колонка ответов
 * \param th - порог, "-" ЕСЛИ (y(row,0) < th) ИНАЧЕ "+"
 * \return число "+" и "-" примеров в y
 */
std::pair<int,int> getPosAndNegCount(const Mat1f& y, float th = 0.5);


#endif // MACHINELEARNING_H
