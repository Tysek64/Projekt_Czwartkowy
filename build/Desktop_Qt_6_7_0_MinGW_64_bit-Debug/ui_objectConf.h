/********************************************************************************
** Form generated from reading UI file 'objectconf.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTCONF_H
#define UI_OBJECTCONF_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_objectConf
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *objectConf)
    {
        if (objectConf->objectName().isEmpty())
            objectConf->setObjectName("objectConf");
        objectConf->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(objectConf->sizePolicy().hasHeightForWidth());
        objectConf->setSizePolicy(sizePolicy);
        buttonBox = new QDialogButtonBox(objectConf);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(50, 260, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(objectConf);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(90, 10, 113, 24));
        spinBox = new QSpinBox(objectConf);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(90, 40, 81, 25));
        spinBox_2 = new QSpinBox(objectConf);
        spinBox_2->setObjectName("spinBox_2");
        spinBox_2->setGeometry(QRect(90, 70, 81, 25));
        label = new QLabel(objectConf);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 71, 21));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(objectConf);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 40, 71, 21));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(objectConf);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 70, 71, 21));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(objectConf);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, objectConf, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, objectConf, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(objectConf);
    } // setupUi

    void retranslateUi(QDialog *objectConf)
    {
        objectConf->setWindowTitle(QCoreApplication::translate("objectConf", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("objectConf", "Name:", nullptr));
        label_2->setText(QCoreApplication::translate("objectConf", "Start frame:", nullptr));
        label_3->setText(QCoreApplication::translate("objectConf", "End frame:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class objectConf: public Ui_objectConf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTCONF_H
