#include <QtWidgets>
#include "optionswidget.h"
#include "mecanismos_comunicacion.h"

OptionsWidget::OptionsWidget(QWidget *parent)
    :QDialog(parent)
{
    label = new QLabel(tr("&Tipo comunicacion"));
    communicationList = new QComboBox();
    communicationList->addItems(QStringList()
                    << "Confiable"
                    << "No confiable");
    label->setBuddy(communicationList);

    connect(communicationList, SIGNAL(activated(int)),
            this, SLOT(communicationTypeChanged(int)));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(label);
    mainLayout->addWidget(communicationList);
    setLayout(mainLayout);

    setWindowTitle(tr("Opciones"));
    setFixedHeight(sizeHint().height());
}

void OptionsWidget::communicationTypeChanged(int index)
{
    int selectedItem = communicationList->currentIndex();
    if (selectedItem == 0)
        emit setTipoComunicacion(STR_CONFIABLE_COLOREADA);
    else
        emit setTipoComunicacion(STR_NO_CONFIABLE_COLOREADA);
}
