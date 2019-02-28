#include "extendedtreeview.h"

ExtendedTreeView::ExtendedTreeView(QWidget *parent) :QTreeView(parent)
{

}

void ExtendedTreeView::setFileSystemModel(QFileSystemModel *model)
{
    _model = model;
    setModel(_model);
}


void ExtendedTreeView::mousePressEvent(QMouseEvent *event)
{
    QTreeView::mousePressEvent(event);
    if(event->button() == Qt::RightButton)
    {
        emit rightButtonClicked();
    }
}




