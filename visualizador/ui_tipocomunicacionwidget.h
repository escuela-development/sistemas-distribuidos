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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TipoComunicacionWidget
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *tipoComunicacion;

    void setupUi(QWidget *TipoComunicacionWidget)
    {
        if (TipoComunicacionWidget->objectName().isEmpty())
            TipoComunicacionWidget->setObjectName(QStringLiteral("TipoComunicacionWidget"));
        TipoComunicacionWidget->resize(400, 300);
        widget = new QWidget(TipoComunicacionWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(30, 30, 227, 31));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        tipoComunicacion = new QComboBox(widget);
        tipoComunicacion->setObjectName(QStringLiteral("tipoComunicacion"));

        gridLayout->addWidget(tipoComunicacion, 0, 1, 1, 1);

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
