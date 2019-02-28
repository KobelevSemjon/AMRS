#ifndef OBJECTDESCRPTION_H
#define OBJECTDESCRPTION_H
#include <list>
#include <string>
using namespace std;

/*!
 * \ingroup Datatools
 * \brief Класс объекта.
 * \details Представляет собой именованного вектора признаков, отождествляемого с объектом.
 * Всегда имеет имя, а также вектор признаков.
 */
class ObjectDescription
{
    string _name;
    list<double> _description;

public:
    ObjectDescription(string name = "Default");
    ObjectDescription& operator<<(const double& feature_value);
    ObjectDescription& operator<<(initializer_list<double> feature_values);
    ObjectDescription& operator<<(list<double> feature_values);

    string& name();
    const string& name() const;
    list<double>& description();
    const list<double>& description() const;
    size_t size() const;


};

template <typename _Stream>
/*!
 * \ingroup Datatools
 * \brief Оператор вывода <<
 * \details Осуществляет запись объекта object в поток stream.
 * С определенным оператором << для std::string.
 * \param stream - поток вывода (шаблонный).
 * \param object - объект.
 * \return Ссылка на поток вывода.
 */
_Stream &operator<<(_Stream& stream, const ObjectDescription& object)
{
    stream << "Object \""<<object.name()<<"\":";
    stream << "\n  1. class = ";
    int row = 2;
    for(double value: object.description())
        stream << value << "\n  " << row++ <<". ";
    stream << "size = " << object.size() << "\n";
    return stream;
}


#endif // OBJECTDESCRPTION_H
