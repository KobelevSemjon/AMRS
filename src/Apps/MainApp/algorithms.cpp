#include "algorithms.h"

/*! \ingroup Application
 * \brief Дать сегмент новообразования используя бинаризацию Отсу.
 * \details Реализует следующий алгоритм:
 * 1) Получает из оригинального изображения серое.
 * 2) Бинаризует инвертированно по Отсу.
 * 3) Комбинирует маленькие области с крупными с адаптивным порогом (src.rows*src.cols)/1000..
 * 4) В прямоугольнике (src.cols/3, src.rows/3, src.cols/3, src.rows/3) находит самый
 * популярный сегмент. Если единственный сегмент - фон, то сегмент с max площадью.
 * 5) Получить маску данного сегмента и наложить ее на оригинальное.
 * \param original_bgr_img - оригинальное изображение.
 * \param get_fitted - true если хотите подогнанное под размеры сегмента изображение.
 * \return Новообразование на черном фоне.
 */
Mat3b getNevusOtsuThrs(const Mat3b &original_bgr_img, bool get_fitted)
{
    const Mat3b& bgr_img = original_bgr_img;
    Mat1b src(bgr_img.size()), ret(bgr_img.size());
    cvtColor(bgr_img, ret, CV_BGR2GRAY);
    wakeApp();

    cv::swap(src,ret);
    threshold(src, ret, 0 ,255, THRESH_BINARY_INV | THRESH_OTSU);
    wakeApp();

    cv::swap(src,ret);
    ConnectedComponents cc(src);
    wakeApp();

    cv::Rect roi(src.cols/3, src.rows/3, src.cols/3, src.rows/3);
    std::map<int, int> areas = cc.areas(roi);
    if (areas.size()==1) areas = cc.areas();

    int nevus_label = -1;
    int nevus_area = -1;
    for(auto label_and_area: areas)
    {
        int label = label_and_area.first;
        int area = label_and_area.second;
        if (label==0) continue; //пропуск сегмента фона;
        if (nevus_area < area)
        {
            nevus_label = label;
            nevus_area = area;
        }
    }
    assert(nevus_label!=-1);
    wakeApp();
    if (get_fitted)
        return cc.fittedMask(nevus_label)(bgr_img);
    return cc.simpleMask(nevus_label)(bgr_img);
}

/*! \ingroup Application
 * \brief Нарисовать границу невуса на цветном изображении
 * \details Находит (аналогично getNevusOtsuThrs) и рисует границу невуса на оригинальном изображении.
 * \param original_bgr_img - цветное оригинальное изображение
 * \param bgr_color - цвет границы (зеленый по умолчанию)
 * \return Изображение с границей невуса
 */
QImage getNevusBoardersOnImage(const Mat3b &original_bgr_img, const Vec3b& bgr_color)
{
    Mat3b bgr_img = original_bgr_img.clone();
    Mat1b src(bgr_img.size()), ret(bgr_img.size());
    cvtColor(bgr_img, ret, CV_BGR2GRAY);
    wakeApp();

    cv::swap(src,ret);
    threshold(src, ret, 0 ,255, THRESH_BINARY_INV | THRESH_OTSU);
    wakeApp();

    cv::swap(src,ret);
    ConnectedComponents cc(src);
    wakeApp();

    cv::Rect roi(src.cols/3, src.rows/3, src.cols/3, src.rows/3);
    std::map<int, int> areas = cc.areas(roi);
    if (areas.size()==1) areas = cc.areas();

    int nevus_label = -1;
    int nevus_area = -1;
    for(auto label_and_area: areas)
    {
        int label = label_and_area.first;
        int area = label_and_area.second;
        if (label==0) continue; //пропуск сегмента фона;
        if (nevus_area < area)
        {
            nevus_label = label;
            nevus_area = area;
        }
    }
    assert(nevus_label!=-1);
    wakeApp();
    auto boarder = cc.segmentBorder(nevus_label);
    for(auto& pair: boarder)
    {
        set<Point> pix_set = pair.second;
        for(Point pt: pix_set)
            bgr_img(pt)=bgr_color;
    }
    return Mat2QImage(bgr_img);
}

/*! \ingroup Application
 * \brief Чтение изображения в Mat.
 * \details В отличае от одноименного метода opencv, данная функция работает с путями с кириллическими символами.
 * \param path - путь
 * \return Изображение.
 */
Mat imread(const QString &path)
{
    QFile file(path);
    std::vector<char> buffer;
    buffer.resize(size_t(file.size()));
    if (!file.open(QIODevice::ReadOnly)) {
        return cv::Mat();
    }
    file.read(buffer.data(), file.size());
    file.close();
    cv::Mat image = cv::imdecode(buffer, CV_LOAD_IMAGE_COLOR);
    return image;
}
/*!
 * \ingroup Application
 * \brief Конвертация цветного 3-хканального Mat изображения в QImage.
 * \param src - Цветное 3-хканальное Mat изображение.
 * \return Эквивалентное QImage изображение.
 */
QImage Mat2QImage(const Mat &bgr_img)
{
    cv::Mat temp;
    cvtColor(bgr_img, temp,CV_BGR2RGB);
    QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    dest.bits();
    return dest;
}
/*!
 * \ingroup Application
 * \brief Описать сегмент на черном фоне.
 * \details Производит рассчет следующих признаков.
 -	Цветовые: минимальное “MIN”, максимальное “MAX”, среднее “MX”, среднеквадратическое отклонение “SD”.
-	Текстурные: энергия “Energy”, энтропия “ENT”, локальная однородность “LUN”, максимальная вероятность “MPR”,
момент инерции “CON”, след “TR”, средняя яркость “AV”.
-	Морфологические: площадь “AREA”, периметр “PERIM”, коэффициент формы “FORM”, максимальный линейный размер “MLD”,
 коэффициент вытянутости “ELONG”, коэффициент округлости внешнего контура “ROUND”.
Цветовые и текстурные признаки рассчитываются для компонент: RGB, HSV.
Текстурные признаки считаются по матрице смежности радиуса смежности = 1 для уменьшенных изображений (25% высоты и ширины).
Морфологические признаки считаются для V компоненты.
 * \param bgr - сегмент на черном фоне.
 * \param name - название объекта.
 * \return Признаковое описание.
 */
ObjectDescription descriptSegment(const Mat3b &bgr, string name, const WakeApp& w)
{
    using namespace cv;
    ObjectDescription obj(name);
    if (bgr.rows==0) throw std::invalid_argument("descriptSegment: bgr is empty image");
    qDebug()<<"descriptSegment "+QString::fromStdString(name);
    Mat1b channels[3];
    split(bgr, channels);
    for (int ch =0; ch < bgr.channels(); ++ch)
    {
        Mat1b& channel = channels[ch];
        auto hist = Histogram(channel);
        obj<<hist.min();w.wakeApp();
        obj<<hist.max();w.wakeApp();
        obj<<hist.MX();w.wakeApp();
        obj<<hist.SD();w.wakeApp();

        Mat1b scaled;
        cv::resize(channel, scaled, Size(),0.25,0.25,cv::INTER_LINEAR);
        auto am = AdjacencyMatrix(scaled);
        obj<<am.energy();w.wakeApp();
        obj<<am.entropy();w.wakeApp();
        obj<<am.localHomogenity();w.wakeApp();
        obj<<am.maxProbability();w.wakeApp();
        obj<<am.inertiaMoment();w.wakeApp();
        obj<<am.trail();w.wakeApp();
        obj<<am.averageBrightness();w.wakeApp();
    }

    Mat3b hsv;
    cvtColor(bgr,hsv,CV_BGR2HSV);
    split(hsv, channels);
    for (int ch =0; ch < hsv.channels(); ++ch)
    {
        Mat1b& channel = channels[ch];
        auto hist = Histogram(channel);
        obj<<hist.min();w.wakeApp();
        obj<<hist.max();w.wakeApp();
        obj<<hist.MX();w.wakeApp();
        obj<<hist.SD();w.wakeApp();

        Mat1b scaled;
        cv::resize(channel, scaled, Size(),0.25,0.25,cv::INTER_LINEAR);
        auto am = AdjacencyMatrix(scaled);
        obj<<am.energy();w.wakeApp();
        obj<<am.entropy();w.wakeApp();
        obj<<am.localHomogenity();w.wakeApp();
        obj<<am.maxProbability();w.wakeApp();
        obj<<am.inertiaMoment();w.wakeApp();
        obj<<am.trail();w.wakeApp();
        obj<<am.averageBrightness();w.wakeApp();
    }

    obj << Morphology(channels[2]).getFeatures();
    w.wakeApp();

    return obj;
}

bool isValidNevus(const Mat3b img)
{
    bool is_valid_nevus = img.rows!=0 && img.cols!=0;
    if (is_valid_nevus)
    {
        Mat1b channels[3];
        split(img, channels);
        for (int ch =0; ch < img.channels(); ++ch)
        {
            is_valid_nevus &= countNonZero(channels[ch])!=0;
            if (is_valid_nevus == false) return false;
        }
        Mat3b hsv;
        cvtColor(img,hsv,CV_BGR2HSV);
        for (int ch =0; ch < hsv.channels(); ++ch)
        {
            is_valid_nevus &= countNonZero(channels[ch])!=0;
            if (is_valid_nevus == false) return false;
        }
    }
    return is_valid_nevus;
}

std::list<string> descriptHeader(bool regenerate)
{
    using namespace std;
    if(regenerate)
    {
        list<string> header;
        for (auto prefix: {"B_","G_","R_","H_","S_","V_"})
        {
            header.splice(header.end(), Histogram().getHeader(prefix));
            header.splice(header.end(), AdjacencyMatrix().getHeader(prefix));
        }
        header.splice(header.end(), Morphology().getHeader());
        return header;
    }
    return HEADER;
}

DataFrame descriptFolder(QDir img_dir, void progress_func(int), bool is_distroyed(void))
{
    DataFrame df("Image");
    df.setHeader(descriptHeader());

    int dirrownum = 0;
    for(QString name: img_dir.entryList())
    {
        QString filepath = img_dir.absoluteFilePath(name);
        cv::Mat3b cv_img = imread(filepath);
        if(cv_img.rows==0) continue;

        cv::Mat3b nevi = getNevusOtsuThrs(cv_img);

        cv_img.release();
        auto obj = descriptSegment(nevi, name.toStdString());

        nevi.release();
        df.newObject(obj);
        dirrownum +=1;
        progress_func(dirrownum);
        if (is_distroyed()) break;
        wakeApp();
    }
    return df;
}

QString savePixmap(QWidget *parent, const QPixmap &pixmap)
{
    QString file_path;
    if(!pixmap.isNull())
    {
        QString base_folder = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        file_path = QFileDialog::getSaveFileName(parent, "Сохранить изображение",
                          base_folder,"Изображения (*.bmp)");
        pixmap.save(file_path);
    }
    return file_path;
}

QTableWidgetItem *newTableItem(const string &val)
{
    return new QTableWidgetItem(QString::fromStdString(val));
}

/*! \ingroup Algorithms
 * \brief Оператор вывода.
 * \details Специализация <<, позволяющая выводить string в QTextStream.
 * \param stream - поток
 * \param text - текст
 * \return Ссылка на поток.
 */
QTextStream &operator<<(QTextStream &stream, const string &text)
{
    stream << QString::fromStdString(text);
    return stream;
}


/*! \ingroup Algoritms
 * \brief Чтение в датафрейм.
 * \details Позволяет читать csv-таблицу с разделителем столбцев ";" в dataframe.
 * \param dataframe - датафрейм
 * \param csvpath - путь до csv-таблицы
 */
void readDataFrame(DataFrame &dataframe, QString csvpath)
{
    QFile csv(csvpath);
    if (!csv.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&csv);
    QStringList rude_header = in.readLine().split(';');
    std::list<std::string> clear_header;
    for (QString s:rude_header)
        clear_header.push_back(s.toStdString());

    dataframe.reset();
    dataframe.setTableName(clear_header.front());
    clear_header.pop_front();
    dataframe.setHeader(clear_header);

    while(!in.atEnd())
    {
        QStringList row = in.readLine().split(';');
        std::string name = row.takeFirst().toStdString();
        std::list<double> values;
        for (QString s:row)
            values.push_back(s.toDouble());
        dataframe.newObject(name,values);
    }
    csv.close();
}

//DATABASE::set(DataBase("clf_v1.sqlite",true));

void wakeApp()
{
    qApp->processEvents();
}
