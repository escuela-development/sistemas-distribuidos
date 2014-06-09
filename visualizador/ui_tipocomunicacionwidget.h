/********************************************************************************
** Form generated from reading UI file 'tipocomunicacionwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIPOCOMUNICACIONWIDGET_H
#define UI_TIPOCOMUNICACIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TipoComunicacionWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *tipoComunicacion;

    void setupUi(QWidget *TipoComunicacionWidget)
    {
        if (TipoComunicacionWidget->objectName().isEmpty())
            TipoComunicacionWidget->setObjectName(QStringLiteral("TipoComunicacionWidget"));
        TipoComunicacionWidget->resize(233, 49);
        verticalLayout = new QVBoxLayout(TipoComunicacionWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(TipoComunicacionWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        tipoComunicacion = new QComboBox(TipoComunicacionWidget);
        tipoComunicacion->setObjectName(QStringLiteral("tipoComunicacion"));

        gridLayout->addWidget(tipoComunicacion, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(tipoComunicacion);
#endif // QT_NO_SHORTCUT

        retranslateUi(TipoComunicacionWidget);

        QMetaObject::connectSlotsByName(TipoComunicacionWidget);
    } // setupUi

    void retranslateUi(QWidget *TipoComunicacionWidget)
    {
        TipoComunicacionWidget->setWindowTitle(QApplication::translate("TipoComunicacionWidget", "Form", 0));
        label->setText(QApplication::translate("TipoComunicacionWidget", "&Communication", 0));
        tipoComunicacion->clear();
        tipoComunicacion->insertItems(0, QStringList()
         << QApplication::translate("TipoComunicacionWidget", "Confiable", 0)
         << QApplication::translate("TipoComunicacionWidget", "No confiable", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class TipoComunicacionWidget: public Ui_TipoComunicacionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIPOCOMUNICACIONWIDGET_H
