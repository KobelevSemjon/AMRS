#ifndef DIALOGSVM_H
#define DIALOGSVM_H

#include <QDialog>

namespace Ui {
class DialogSVM;
}

class DialogSVM : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSVM(QWidget *parent = nullptr);
    ~DialogSVM();

private:
    Ui::DialogSVM *ui;
};

#endif // DIALOGSVM_H
