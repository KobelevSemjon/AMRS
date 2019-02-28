#include "standardscaler.h"
/*!
 * \brief Обучить табличный скалер.
 * \details Производит вычисление среднего и десперсии для каждой колонки df,
 * для последующей нормировки.
 * \param df - таблица
 */
void StandardTableScaler::fit(const DataFrame &df)
{
    _column_scalers.clear();
    _column_scalers.reserve(df.cols());
    for(size_t col=0; col < df.cols(); ++col)
    {
        StandardScaler scaler = fit_scaler(df.getColumnList(col));
        _column_scalers.push_back(scaler);
    }
}

/*!
 * \brief Нормирование таблицы.
 * \details Нормирует все колонки df на среднее и дисперсию, полученных после fit.
 * \param df - таблица
 */
void StandardTableScaler::transform(DataFrame &df) const
{
    for(size_t row=0; row<df.rows(); ++row)
    {
        vector<double>& df_row = df[row];
        for(size_t col=0; col< df.cols();++col)
        {
            double& value = df_row[col];
            const StandardScaler& scaler = _column_scalers[col];
            value = scaler(value);
        }
    }
}

/*!
 * \brief Нормирование признаков.
 * \details Нормирует все значения od на среднее и дисперсию, полученных после fit.
 * \param od - описание объекта
 */
void StandardTableScaler::transform(ObjectDescription &od) const
{
    if (od.size()!=_column_scalers.size())
        throw std::invalid_argument("od.size() and _column_scalers.size() must be equal");

    auto descriptIt = begin(od.description());

    for (const StandardScaler& scaler: _column_scalers)
    {
        double& value = *descriptIt;
        value = scaler(value);
        ++descriptIt;
    }
}

/*!
 * \brief Сериализация скалера.
 * \details Генерирует текст, в каждой строчке которого записаны среднее и ско через пробел.
 * \return строка вида "MX1 SD1\nMX2 SD2\n...\nMXn SDn"
 */
string StandardTableScaler::toStdString() const
{
    std::stringstream ss;
    for (const StandardScaler& scaler: _column_scalers)
        ss << scaler._mx << " " << scaler._sd <<"\n";
    return  ss.str();
}

/*!
 * \brief Десериализация скалера.
 * \details Комплиментарный метод - toStdString()
 * \param scaler_str - строка вида "MX1 SD1\nMX2 SD2\n...\nMXn SDn"
 */
void StandardTableScaler::fromStdString(const string &scaler_str)
{
    _column_scalers.clear();
    std::stringstream ss(scaler_str);
    std::string line;
    while (getline(ss, line))
    {
        double MX, SD;
        std::stringstream(line) >> MX >> SD;
        StandardScaler scaler(MX,SD);
        _column_scalers.push_back(scaler);
    }
}

/*!
 * \brief Сохранение скалера.
 * \details занчения сохраняются через ofstream в виде fout << mx << " " << sd <<"\n".
 * \param path - путь
 * \return true если запись прошла успешно.
 */
bool StandardTableScaler::save(const string &path) const
{
    std::ofstream fout(path.c_str());
    if (fout.is_open())
    {
        auto str = toStdString();
        fout.write(str.c_str(),int(str.size()));
        fout.close();
        return true;
    }
    return false;
}

/*!
 * \brief Загружающий конструктор.
 * \details Обеспечивает загрузку скалера(комплиментарен методу save)
 * \param path - путь
 */
StandardTableScaler::StandardTableScaler(const string &path)
{
    std::ifstream fin(path.c_str());
    if (fin.is_open())
    {
        std::string str((std::istreambuf_iterator<char>(fin)),
                         std::istreambuf_iterator<char>());
        fromStdString(str);
        fin.close();
    }
}

size_t StandardTableScaler::size(){return _column_scalers.size();}

/*!
 * \brief Конструктор скалера.
 * \param mx - среднее
 * \param sd - скреднеквадратическое отклонение
 */
StandardScaler::StandardScaler(double mx, double sd):
    _mx(mx),_sd(sd){}

/*!
 * \brief Нормировать значение.
 * \param value - значение
 */
double StandardScaler::operator()(double value) const
{
    return (value - _mx)/_sd;
}
