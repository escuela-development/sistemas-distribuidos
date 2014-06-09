#ifndef TIPOCOMUNICACIONWIDGET_H
#define TIPOCOMUNICACIONWIDGET_H

#include <QDialog>

#include "ui_tipocomunicacionwidget.h"

class TipoComunicacionWidget : public QDialog,
  public Ui::TipoComunicacionWidget
{
  Q_OBJECT

  public:
    TipoComunicacionWidget(QWidget *parent = 0);

};

#endif
