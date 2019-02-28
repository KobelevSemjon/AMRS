#ifndef EXTENDEDTREEVIEW_H
#define EXTENDEDTREEVIEW_H

#include <QTreeView>
#include <QMouseEvent>
#include <QFileSystemModel>


class ExtendedTreeView : public QTreeView
{
    Q_OBJECT

    QFileSystemModel* _model;
private:
    void createMenu();

public:
    explicit ExtendedTreeView(QWidget *parent = nullptr);
    void setFileSystemModel(QFileSystemModel* model);
    ~ExtendedTreeView(){}

public slots:
    void mousePressEvent(QMouseEvent *event);

signals:
    void rightButtonClicked();

};



#endif // EXTENDEDTREEVIEW_H
