#ifndef MINIVIEW_H
#define MINIVIEW_H

#include <QMouseEvent>
#include <imageview.h>

class MiniView:public QGraphicsView
{
    Q_OBJECT

    ImageView* _sender;
    double coef_x, coef_y;
public:
    MiniView(QWidget *parent);
    void setScalableView(ImageView* sender);
    void setMinimap(const QPixmap& pixmap);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    ~MiniView();
public slots:
    void areaChanged();
private:
    QRectF visibleAreaRect();
signals:
    void positionChanged(QPointF);
};

#endif // MINIVIEW_H
