#include "dataframe.h"

/*!
 * \brief Конструктор по умолчанию.
 * \param name - название первой колонки (колонка имен, по умолчанию "Default")
 */
DataFrame::DataFrame(std::string name):_name(name){}

/*!
 * \brief Копирующий конструктор.
 * \param dataframe - другая матрица объектов-признаков.
 */
DataFrame::DataFrame(const DataFrame &dataframe)
{
    _table = dataframe._table;
    _header = dataframe._header;
    _names = dataframe._names;
    _name = dataframe._name;
}

/*!
 * \brief Перемещающий конструктор.
 * \param dataframe - другая матрица объектов-признаков.
 */
DataFrame::DataFrame(DataFrame &&dataframe)
{
    swap(*this,dataframe);
}

/*!
 * \brief Перемещающее присваивание.
 * \param dataframe - другая матрица объектов-признаков.
 */
void DataFrame::operator=(DataFrame &&dataframe)
{
    swap(*this,dataframe);
}

/*!
 * \brief Копирующее присваивание.
 * \param dataframe - другая матрица объектов-признаков.
 */
void DataFrame::operator=(const DataFrame &dataframe)
{
    _table = dataframe._table;
    _header = dataframe._header;
    _names = dataframe._names;
}

/*!
 * \brief Очистка таблицы.
 * \details Имя первой колонки (имя таблицы) сохраняется, все остальное будет удалено.
 */
void DataFrame::reset()
{
    _table.clear();
    _header.clear();
    _names.clear();
}

/*!
 * \brief Число колонок-признаков.
 * \return Число колонок-признаков.
 */
size_t DataFrame::cols() const {return _header.size();}
/*!
 * \brief Число строк-объектов.
 * \return Число строк-объектов.
 */
size_t DataFrame::rows() const {return _names.size();}

/*!
 * \brief Имя таблицы
 * \return  Имя таблицы
 */
const string &DataFrame::getTableName() const{return _name;}

/*!
 * \brief Поменять название строки
 * \param new_name - новое название строки
 * \param row - номер строки
 */
void DataFrame::setRowName(const string &new_name, size_t row)
{
    _names[row] = new_name;
}

/*!
 * \brief Название строки
 * \param row - номер строки
 * \return название строки
 */
const string &DataFrame::getRowName(size_t row) const
{
    return _names[row];
}

/*!
 * \brief Поменять название таблицы
 * \param new_name - новое название таблицы
 */
void DataFrame::setTableName(const string &new_name)
{
    _name = new_name;
}

/*!
 * \brief Установка названий колонок.
 * \details Устанавливает названия колонок-признаков в том же порядке, что и в header_list.
 * Не влияет на название первой колонки (колонrи имен). Также неявно задается ширина матрицы
 * cols() как длина header_list.
 * \param header_list - названия колонок.
 */
void DataFrame::setHeader(const list<std::string> &header_list)
{
    reset();
    _header = deque<std::string>(header_list.cbegin(), header_list.cend());
//    for (auto col: header_list)
//        _header.push_back(col);
}

/*!
 * \brief Добавляет новый объект.
 * \details Имя name помещается в колонку имен, а значения из values помещаются в колонки-признаки
 * в том же порядке.
 * \param name - название объекта.
 * \param values - значения признаков объекта.
 * \exception invalid_argument - если длина values и cols() не совпадают.
 */
void DataFrame::newObject(const std::string &name, const vector<double> &values)
{
    if (values.size()!=cols()) throw std::invalid_argument("SDataFrame: values size and header size must be equal");
    _names.push_back(name);
    _table.push_back(values);
}
/*!
 * \brief Добавляет новый объект.
 * \details Имя name помещается в колонку имен, а значения из values помещаются в колонки-признаки
 * в том же порядке.
 * \param name - название объекта.
 * \param values - значения признаков объекта.
 * \exception invalid_argument - если длина values и cols() не совпадают.
 */
void DataFrame::newObject(const std::string &name, const list<double> &values)
{
    newObject(name, std::vector<double>(values.begin(),values.end()));
}
/*!
 * \brief Добавляет новый объект.
 * \details Имя name помещается в колонку имен, а значения из values помещаются в колонки-признаки
 * в том же порядке.
 * \param name - название объекта.
 * \param values - значения признаков объекта.
 * \exception invalid_argument - если длина values и cols() не совпадают.
 */
void DataFrame::newObject(const char name[], initializer_list<double> values)
{

    newObject(string(name), std::vector<double>(values.begin(),values.end()));
}
/*!
 * \brief Добавляет новый объект.
 * \details Заносит данные об объекте в последнюю строку таблицы.
 * \param object - объект (именованный вектор признаков).
 * \exception invalid_argument - если длина object и cols() не совпадают.
 * \attention Класс ObjectDescription содержит первым признаком класс объекта.
 * Подробнее в документации.
 */
void DataFrame::newObject(const ObjectDescription &object)
{
    if (object.size()!=cols()) throw std::invalid_argument("SDataFrame: object size and header size must be equal");
    newObject(object.name(), object.description());
}
/*!
 * \brief Добавляет новую колонку.
 * \details Добавляет новую колонку в конце с именем name и значениями values.
 * \param name - имя колонки
 * \param values - значения признаков
 */
void DataFrame::newColumn(const string &name, const vector<double> &values)
{
    if(values.size()!=rows()) throw std::invalid_argument("newColumn: values.size()!=rows()");
    _names.push_back(name);
    for(size_t row=0; row<rows();++row)
        _table[row].push_back(values[row]);
}
/*!
 * \brief Добавляет новую колонку.
 * \details Добавляет новую колонку в конце с именем name и значениями values.
 * \param name - имя колонки
 * \param values - значения признаков
 */
void DataFrame::newColumn(const string &name, const list<double> &values)
{
    if(values.size()!=rows()) throw std::invalid_argument("newColumn: values.size()!=rows()");
    _names.push_back(name);
    auto It = values.begin();
    for(size_t row=0; row<rows();++row)
        _table[row].push_back(*It++);
}

/*!
 * \brief Оператор доступа к строкам таблицы.
 * \details Названия строк и столбцев при это не учитывается т.е. dataframe[0] не является заголовком
 * аналогично со столбцами.
 * \param row - номер строки
 * \return строка значений
 */
vector<double> &DataFrame::operator[](size_t row)
{
    return _table.at(row);
}

/*!
 * \brief Обеспечивает сравнение заголовков 2-ух таблиц.
 * \param df - 2-я таблица
 * \return 0 если названия, порядок или длина заголовков различна.
 */
bool DataFrame::compareHeaders(const DataFrame &df) const
{
    if (cols()!=df.cols()) return false;
    for(size_t i=0; i<cols(); ++i)
    {
        if (_header[i]!=df._header[i])
        {
            return false;
        }
    }
    return true;
}

/*!
 * \brief Вертикальная конкатенация таблиц.
 * \details Обеспечивает присоединение данных 2ой таблицы к концу в том же порядке (Изменяет обьект!).
 * При это заголовки должны быть равны (compareHeaders).
 * \param df - 2-я таблица
 * \return Ссылка на текущую таблицу
 */
DataFrame &DataFrame::vstack(const DataFrame &df)
{
    if (!compareHeaders(df)) throw std::invalid_argument("DataFrame: headers must be compatible");
    std::move(df._table.begin(),df._table.end(), std::back_inserter(_table));
    std::move(df._names.begin(),df._names.end(), std::back_inserter(_names));
    return *this;
}

/*!
 * \brief Вертикальная конкатенация таблиц.
 * \details Заголовки должны быть равны (compareHeaders).
 * \param df - 2-я таблица
 * \return Ссылка на текущую таблицу
 */
DataFrame vstack(const DataFrame &df1, const DataFrame &df2)
{
    DataFrame stacked_df(df1);
    stacked_df.vstack(df2);
    return stacked_df;
}

/*!
 * \brief Оператор доступа к строкам таблицы (защищенный).
 * \details Названия строк и столбцев при это не учитывается т.е. dataframe[0] не является заголовком
 * аналогично со столбцами.
 * \param row - номер строки
 * \return строка значений
 */
const vector<double> &DataFrame::operator[](size_t row) const
{
    return _table.at(row);
}
/*!
 * \brief Заголовок.
 * \return Названия колонок
 */
const deque<string> &DataFrame::getHeader() const{return _header;}

/*!
 * \brief Колонка.
 * \details Позволяет получить колонку значений по указанному номеру колонки col.
 * \param col - номер колонки
 * \return вектор значений колонки
 */
vector<double> DataFrame::getColumnVector(size_t col) const
{
    list<double> column = getColumnList(col);
    return vector<double>(column.begin(),column.end());
}
/*!
 * \brief Перетасовка строк.
 * \details Перетасовывает строки с помощью std::mt19937 с указанным зерном.
 * \param seed - зерно
 */
void DataFrame::shuffleRows(int seed)
{
    shuffle(begin(_table), end(_table), mt19937(seed));
    shuffle(begin(_names), end(_names), mt19937(seed));
}

/*!
 * \brief Колонка.
 * \details Позволяет получить колонку значений по указанному номеру колонки col.
 * \param col - номер колонки
 * \return список значений колонки
 */
list<double> DataFrame::getColumnList(size_t col) const
{
    list<double> column;
    for(const vector<double>& row: _table)
        column.push_back(row[col]);
    return column;
}
/*!
 * \brief Запись матрицы объекты-признаки в файл.
 * \details Записывает csv-файл с разделителем столбцов ";" и переносом строки.
 * \param path - файловый путь до файла
 * \return true - если запись прошла успешно, иначе false.
 * \warning Использует ofstream, поэтому в path допускаются только
 * латинские символы. Оператор << является альтернативой.
 */
bool DataFrame::write(const std::string &path)
{
    ofstream fout(path.c_str());
    if (fout.is_open())
    {
        fout << _name.c_str();
        for (string col: _header)
            fout << ";" << col ;

        for (size_t i=0; i<rows(); ++i)
        {
            fout << "\n" << _names.at(i);
            for (double val: _table.at(i))
                fout << ";" << val;
        }
        fout.close();
        return true;
    }
    return false;
}




