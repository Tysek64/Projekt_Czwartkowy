#include "objectconf.h"
#include "ui_objectconf.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>

objectConf::objectConf(QWidget *parent, MainWindow &dataReceiver, trackedObject activeItem)
    : QDialog(parent)
    , ui(new Ui::objectConf)
{
    ui->setupUi(this);
    ui->classSelect->addItem("-");
    ui->typeSelect->addItem("-");

    QString jsonStringHelper;
    QFile jsonListsFile;
    jsonListsFile.setFileName("lists_configuration.json");
    jsonListsFile.open(QIODevice::ReadOnly | QIODevice::Text);
    jsonStringHelper = jsonListsFile.readAll();

    QJsonDocument jsonLists = QJsonDocument::fromJson(jsonStringHelper.toUtf8());
    QJsonObject jsonListsObject = jsonLists.object();
    QList<QVariant> classListHelper =  jsonListsObject.value(QString("class_list")).toArray().toVariantList();
    QString helper;
    for (int i=0; i< classListHelper.size(); i++) {
        helper = classListHelper[i].toString();
        ui->classSelect->addItem(helper);
    }
    QList<QVariant> typeListHelper =  jsonListsObject.value(QString("type_list")).toArray().toVariantList();
    for (int i=0; i< typeListHelper.size(); i++) {
        helper = typeListHelper[i].toString();
        ui->typeSelect->addItem(helper);
    }

    this->dataReceiver = &dataReceiver;

    ui->spinBox->setValue(activeItem.getStart());
    ui->spinBox_2->setValue(activeItem.getEnd());
    ui->classSelect->setCurrentIndex(activeItem.getClass() + 1);
    ui->typeSelect->setCurrentIndex(activeItem.getType() + 1);
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
    dataReceiver->getConf(ui->lineEdit->text(), ui->spinBox->value(), ui->spinBox_2->value(), ui->classSelect->currentIndex() - 1, ui->typeSelect->currentIndex() - 1);
}

