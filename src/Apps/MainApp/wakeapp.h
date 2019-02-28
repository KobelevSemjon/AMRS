#ifndef WAKEAPP_H
#define WAKEAPP_H

#include <QObject>
#include <QApplication>

/*! \ingroup Application
 * \brief Разбудить приложение.
 * \details Данная функция будит зависнувшее приложение.
 */
class WakeApp : public QObject
{
    Q_OBJECT

public:
    WakeApp(){}
    ~WakeApp(){}

public:
    void operator()(void) const
    {
        qApp->processEvents();
    }
public slots:
    void wakeApp() const
    {
        operator()();
        emit called();
    }

signals:
    void called() const;
};


#endif // WAKEAPP_H
