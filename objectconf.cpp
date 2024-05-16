#include "objectconf.h"
#include "ui_objectconf.h"

objectConf::objectConf(QWidget *parent, MainWindow &dataReceiver)
    : QDialog(parent)
    , ui(new Ui::objectConf)
{
    ui->setupUi(this);

    this->dataReceiver = &dataReceiver;
}

objectConf::~objectConf()
{
    delete ui;
}

QString objectConf::getName() {
    return ui->lineEdit->text();
}

void objectConf::on_buttonBox_accepted()
{
    qDebug() << dataReceiver->getcol().test();
    dataReceiver->getConf(ui->lineEdit->text(), ui->spinBox->value(), ui->spinBox_2->value());
}

