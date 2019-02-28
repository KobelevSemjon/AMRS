#ifndef DATATOOLS_H
#define DATATOOLS_H
#include "dataframe.h"
#include "objectdescription.h"
#include "standardscaler.h"

/*! \defgroup Datatools Модуль манипуляции с данными.
 * \brief Набор классов и методов, обеспечивающих различные функции от
 * представления описания сегментов изображения до сохранения матрицы
 * объектов-признаков.
 * Пример использования
 * \code
DataFrame df("Names");
df.setHeader({"Sex","Age"});
auto v = ObjectDescription("Vasya") << 12;
df.newObject(v); cout << v;
df.newObject("Tanya",{0,13});
df.newObject("Rita",{0,9});
bool OK = df.write("test.csv");
    \endcode
*/
#endif // DATATOOLS_H
