#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QDialog>

class QLabel;
class QComboBox;

/*
 * Contiene las opciones que soporta el visualizador de complejos
 * simpliciales, entre ellas se encuentran
 *
 * <ul>
 * <li>Tipo de comunicacion (confiable, no confiable)</ul>
 * </ul>
 */
class OptionsWidget : public QDialog
{
    Q_OBJECT

public:
    OptionsWidget(QWidget *parent = 0);

signals:
    void setCommunicationType(const QString &Text);

private slots:
    void communicationTypeChanged(int index);

private:

    QLabel *label;
    QComboBox *communicationList;
};

#endif // OPTIONSWIDGET_H
