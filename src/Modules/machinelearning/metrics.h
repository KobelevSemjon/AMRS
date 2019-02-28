#ifndef METRICS_H
#define METRICS_H
#include <math.h>
#include <iostream>
#include <list>


template<typename _Iterable>
/*! \ingroup MachineLearning
 * \brief Лог-лосс (логарифмическая функция ошибки)
 * \details Логистические или кросс-энтропийные потери. \n
  -log P(yt|yp) = -(yt log(yp) + (1 - yt) log(1 - yp)), где
  yt и yp соответствуют answers и predicts соответственно.
 * \param answers - столбец оветов
 * \param predicts - столбец предсказаний
 * \return точность
 */
double logLoss(const _Iterable& answers, const _Iterable& predicts)
{
    double ret = 0;
    if (answers.size()==predicts.size())
    {
        auto aIt = answers.begin();
        auto pIt = predicts.begin();
        for(; aIt!=answers.end();++aIt, ++pIt)
        {
            double yt = double(*aIt);
            double yp = double(*pIt);
            ret+= -(yt*log(yp) + (1.-yt)*log(1-yp));
            if (yp<0 || yp>1)
                std::cout << "Warning logLoss: predict out of range (0,1)\n";
        }
    }
    else ret = -1;
    return ret;
}

struct ConfusionMatrix
{
    /*          yt=1    yt=0*/
    /*yp=1*/    int TP, FP;
    /*yp=0*/    int FN, TN;
    ConfusionMatrix():TP(0),FP(0),FN(0),TN(0){}
    int total(){return TP+FP+FN+TN;}
    double sensitivity(){return double(TP)/double(TP+FN);}
    double specificity(){return double(TN)/double(TN+FP);}
    double accuracy(){return double(TP+TN)/double(total());}
};

template<typename _Iterable1, typename _Iterable2>
ConfusionMatrix createConfusionMatrix(const _Iterable1& answers, const _Iterable2& predicts, float th = 0.5)
{
    ConfusionMatrix cm;
    if (answers.size()==predicts.size())
    {
        auto aIt = answers.begin();
        auto pIt = predicts.begin();
        for(; aIt!=answers.end();++aIt, ++pIt)
        {
            int yt = round(*aIt);
            if (yt!=0 && yt!=1)
                throw std::invalid_argument("createConfusionMatrix: class mark must be 0 or 1");
            int yp = !(*pIt < th);

            if (yt==1)
                if (yp==1) ++(cm.TP);
                else /*yp==0*/ ++(cm.FN);
            else /*yt==0*/
                if (yp==0) ++(cm.TN);
                else /*yp==1*/ ++(cm.FP);
        }
    }
    return cm;
}

template<typename _Iterable1, typename _Iterable2, typename _Point>
/*!
 * \brief ROC-кривая
 * \details Строит график зависимости чувствительности от специфичности.
 * Точки кривой получаются пересчетом матрицы ошибок при изменении порога от 0 до 1.
 * delta определяет шаг изменения порога, чем она меньше, тем подробнее график.
 * \param answers - столбец оветов
 * \param predicts - столбец предсказаний
 * \param delta - шаг
 * \return упорядоченный набор точек
 */
std::list<_Point> getROC(const _Iterable1& answers, const _Iterable2& predicts, double delta = 0.05)
{
    using namespace std;
    list<_Point> curve;
    for(double th=0; th<1; th+=delta)
    {
        ConfusionMatrix cm = createConfusionMatrix(answers,predicts, th);
        curve.push_back({cm.specificity(), cm.sensitivity()});
    }
}
template<typename _Iterable>
/*!
 * \brief Площадь под графиком
 * \param curve - упорядоченный набор точек Point2d
 * \return площадь
 */
double getAUC(const _Iterable& curve)
{
    double auc=0;
    auto It1 = curve.begin();
    auto It2 = It1++;
    for(size_t i =0; i<curve.size()-1; ++i)
    {
        auto p1 = *It1++;
        auto p2 = *It2++;
        auc += 0.5*(p1.y+p2.y)*(p2.x-p1.x);
    }
    return auc;
}

#endif // METRICS_H
