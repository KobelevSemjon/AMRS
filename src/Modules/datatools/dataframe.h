#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <vector>
#include <deque>
#include <list>
#include <fstream>
#include <random>
#include <algorithm>

#include "objectdescription.h"

using namespace std;
/*!
 * \ingroup Datatools
 * \brief Класс матрицы объектов-признаков.
 * \details - Первая ячейка таблицы зарезервированна под название первой колонки таблицы
 * называемой колонкой имен. Все остальные колонки называются колонками-признаками.
 * - Первая строка называется заголовком. Все строки кроме первой называются строками-объектами.
 * - В первой строке написаны названия признаков (название на колонку).
 * - В первом столбце написаны имена объектов (имя на строку).
 * - На пересечении строки, соответствующей объекту, и столбца, соответствующего признаку,
 * записывается значение признака для данного объекта.
 */
class DataFrame
{
    deque<vector<double>> _table;
    deque<string> _header;
    deque<string> _names;
    string _name;

public:
    DataFrame(string name = "Default");
    DataFrame(const DataFrame& dataframe);
    DataFrame(DataFrame&& dataframe);
    void operator=(const DataFrame& dataframe);
    void operator=(DataFrame&& dataframe);
    void reset();

    size_t cols() const;
    size_t rows() const;

    void setTableName(const string& new_name);
    const string &getTableName() const;

    void setRowName(const string& new_name, size_t row);
    const string &getRowName(size_t row) const;

    void setHeader(const list<string>& header_list);
    void newObject(const string& name, const vector<double> &values);
    void newObject(const string& name, const list<double> &values);
    void newObject(const char name[], initializer_list<double> values);
    void newObject(const ObjectDescription& object);
    void newColumn(const string& name, const vector<double> &values);
    void newColumn(const string& name, const list<double> &values);

    const vector<double>& operator[](size_t row) const;
    vector<double>& operator[](size_t row);

    bool compareHeaders(const DataFrame& df) const;
    DataFrame &vstack(const DataFrame& df);

    const deque<string>& getHeader() const;
    list<double> getColumnList(size_t col) const;
    vector<double> getColumnVector(size_t col) const;

    void shuffleRows(int seed = 0);

    bool write(const string& path);
};

DataFrame vstack(const DataFrame& df1, const DataFrame& df2);

template <typename _Stream>
/*!
 * \ingroup Datatools
 * \brief Запись в поток
 * \details Обеспечивает запись датафрейма в поток, у которого
 * есть операторы записи std::string.
 * \param stream - поток
 * \param df - таблица
 * \return поток
 */
_Stream &operator<<(_Stream& stream, const DataFrame& df)
{
    stream << df.getTableName();
    for (string col: df.getHeader())
        stream << ";" << col ;

    for (size_t i=0; i<df.rows(); ++i)
    {
        stream << "\n" << df.getRowName(i);
        for (double val: df[i])
            stream << ";" << val;
    }
    return stream;
}


#endif // DATAFRAME_H
