#ifndef TRANSFORMS_H
#define TRANSFORMS_H
#include "dataframe.h"


template<typename Table>
/*!
 * \ingroup Datatools
 * \brief Обобщенная конвертация датафрейма в таблицу.
 * \details Совершает копирование значений df в tb. У tb
 * должен быть реализован доступ в виде  tb[row][col]
 * \param df - датафрейм
 * \param tb - таблица
 */
void tableConvert(const DataFrame& df, Table& tb)
{
    for(size_t r = 0; r < df.rows(); ++r)
        for(size_t c = 0; c < df.cols();++c)
            tb[int(r)][int(c)]=df[r][c];

}

template<typename Container>
/*!
 * \ingroup Datatools
 * \brief Обобщенная конвертация описания объекта в контейнер.
 * \details  Контейнер должен быть итерируемым (иметь begin()).
 * \param od - описание объекта
 * \param c - контейнер
 */
void containerConvert(const ObjectDescription& od, Container& c)
{
    auto begin_it = od.description().begin();
    auto end_it = od.description().end();
    std::copy(begin_it, end_it, c.begin());
}




#endif // TRANSFORMS_H
