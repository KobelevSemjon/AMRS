#include "mlpregressor.h"


/*!
 * \brief Установить число скрытых слоев.
 * \details При этом не нужно думать о входном и выходном слое -
 * их размеры будут рассчитаны исходя из размеров обучающей выборки и
 * колонок ответов.
 * \param hidden_layer_sizes - числа скрытых слоев.
 */
void MLPRegressor::setLayerSizes(const std::vector<ushort> &hidden_layer_sizes)
{
    const auto& hls = hidden_layer_sizes;
    int layer_count =  1 + int(hls.size()) + 1;
    _layer_sizes = Mat(layer_count, 1, CV_16U);
    for(int row = 1; row < layer_count-1; ++row)
        _layer_sizes.row(row) = Scalar(hls[size_t(row-1)]);
    //setLayerSizes() в fit, в котором будет определено input и output размеры
}

/*!
 * \brief Вернуть число скрытых слоев.
 * \return hidden_layer_sizes - числа скрытых слоев.
 */
vector<int> MLPRegressor::getLayerSizes()
{
    vector<int> sizes;
    Mat layer_sizes_column = _clf->getLayerSizes();
    layer_sizes_column.copyTo(sizes);
    sizes.erase(sizes.begin());
    sizes.erase(prev(sizes.end()));
    return sizes;
}

/*!
 * \brief Установить параметры по умолчанию.
 * \details ANN_MLP::ActivationFunctions::SIGMOID_SYM,
 *  ANN_MLP::TrainingMethods::BACKPROP
 */
void MLPRegressor::setDefault()
{
    _clf->setActivationFunction(ANN_MLP::ActivationFunctions::SIGMOID_SYM,1,1);
    _clf->setTrainMethod(ANN_MLP::TrainingMethods::BACKPROP);
}

/*!
 * \brief Обучить персептрон.
 * \details Формат аргументов "признаки-столбцы" и "объекты-строчки".
 * \warning setLayerSizes должен быть вызван до fit.
 * \param samples
 * \param answers_column
 */

void MLPRegressor::fit(const Mat1f &samples, const Mat1f &answers_column)
{
    int layer_count = _layer_sizes.rows;
    _layer_sizes.row(0) = samples.cols;
    _layer_sizes.row(layer_count-1) = answers_column.cols;//
    _clf->setLayerSizes(_layer_sizes);
    setDefault();
    _clf->train(samples,SampleTypes::ROW_SAMPLE,answers_column);
    _is_valid = true;
}

string MLPRegressor::getParams()
{
    std::stringstream ss;
    ss << "{LayerSizes = [";
    bool is_first = true;
    for (int x: getLayerSizes())
    {
        if (is_first)
            is_first = false;
        else
            ss << ", ";
        ss << x;
    }
    ss << "]}";
    return ss.str();
}



