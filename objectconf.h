#ifndef OBJECTCONF_H
#define OBJECTCONF_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class objectConf;
}

class objectConf : public QDialog
{
    Q_OBJECT

public:
    explicit objectConf(QWidget *parent = nullptr, MainWindow &dataReceiver = *new MainWindow());
    ~objectConf();

    QString getName();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::objectConf *ui;
    MainWindow *dataReceiver;
};

#endif // OBJECTCONF_H
