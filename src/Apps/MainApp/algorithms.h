#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <QFile>
#include <QImage>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QAction>
#include <QFileDialog>
#include <QStandardPaths>
#include <QTableWidgetItem>

#include <opencv2/opencv.hpp>
#include "imaging.h"
#include "description.h"
#include "datatools.h"
#include "machinelearning.h"
#include "wakeapp.h"

using namespace cv;
using namespace std;

void wakeApp();;
Mat imread(const QString& path);
QImage Mat2QImage(const Mat &bgr_img);
Mat3b getNevusOtsuThrs(const Mat3b& original_bgr_img, bool is_fitted = true);
bool isValidNevus(const Mat3b img);
QImage getNevusBoardersOnImage(const Mat3b& original_bgr_img, const Vec3b& bgr_color = {0,255,0});
ObjectDescription descriptSegment(const cv::Mat3b &bgr, string name, const WakeApp& w =WakeApp());
std::list<string> descriptHeader(bool regenerate = false);

DataFrame descriptFolder(QDir img_dir, void progress_func(int), bool is_distroyed(void));
QString savePixmap(QWidget* parent, const QPixmap& pixmap);
static const std::list<string> HEADER = descriptHeader(true);

template<typename _Value>
/*! \ingroup Algorithms
 * \brief Создать через new QTableWidgetItem
 * \param val - значение, передаваемое в конструктор.
 * \return указатель на QTableWidgetItem
 */
QTableWidgetItem* newTableItem(const _Value & val)
{
    return new QTableWidgetItem(QString("%1").arg(val));
}
QTableWidgetItem *newTableItem(const std::string& val);
QTextStream& operator<<(QTextStream& stream, const std::string& text);
void readDataFrame(DataFrame& dataframe, QString csvpath);


#endif // ALGORITHMS_H
