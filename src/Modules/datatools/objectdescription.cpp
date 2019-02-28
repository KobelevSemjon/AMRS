#include "objectdescription.h"

/*!
 * \brief Конструктор.
 * \param name - название объекта (по умолчанию "Default").
 */
ObjectDescription::ObjectDescription(string name):_name(name){}

/*!
 * \brief Оператор <<
 * \details Заносит значение признака в конец вектора признаков.
 * \param feature_value - значение признака.
 * \return Ссылка на объект.
 */
ObjectDescription &ObjectDescription::operator<<(const double &feature_value)
{
    _description.push_back(feature_value);
    return *this;
}
/*!
 * \brief Оператор <<
 * \details Заносит значения признаков из списка инициализации
 * в конец вектора признаков в том же порядке.
 * \param feature_values - список со значением признаков.
 * \return Ссылка на объект.
 */
ObjectDescription &ObjectDescription::operator<<(initializer_list<double> feature_values)
{
    for(double value: feature_values)
        _description.push_back(value);
    return *this;
}
/*!
 * \brief Оператор <<
 * \details Заносит значения признаков из списка
 * в конец вектора признаков в том же порядке.
 * \param feature_values - список со значением признаков.
 * \return Ссылка на объект.
 */
ObjectDescription &ObjectDescription::operator<<(list<double> feature_values)
{
    for(double value: feature_values)
        _description.push_back(value);
    return *this;
}

/*!
 * \brief Имя объекта.
 * \return Ссылка на имя объекта.
 */
string &ObjectDescription::name() {return _name;}

/*!
 * \brief Имя объекта.
 * \return Константная ссылка на имя объекта.
 */
const string &ObjectDescription::name() const {return _name;}

/*!
 * \brief Вектор значений признаков.
 * \details Признаки даются в том же порядке, в котором их записывали в объект.
 * \return Ссылка на вектор значений признаков.
 */
list<double> &ObjectDescription::description() {return _description;}

/*!
 * \brief Вектор значений признаков.
 * \details Признаки даются в том же порядке, в котором их записывали в объект.
 * \return Константная ссылка на Вектор значений признаков.
 */
const list<double> &ObjectDescription::description() const {return _description;}

/*!
 * \brief Число признаков.
 * \details  Эквивалентно description().size().
 * \return Число признаков.
 */
size_t ObjectDescription::size() const {return _description.size();}

