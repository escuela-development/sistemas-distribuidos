#include <QtWidgets>
#include <QDebug>

#include <iostream>

#include "ventanaprincipal.h"
#include "complejosimplicial.h"
#include "optionswidget.h"

VentanaPrincipal::VentanaPrincipal()
{
    simplejo = new ComplejoSimplicial(this);
    setCentralWidget(simplejo);

    crearActions();
    crearMenus();
    crearToolBars();
    crearDockWindows();
}

void VentanaPrincipal::closeEvent(QCloseEvent *)
{
    delete simplejo;
}

void VentanaPrincipal::crearActions()
{
    openAction = new QAction(tr("&Open..."), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing simplicial complex model"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()),
            this, SLOT(close()));

    stepAction = new QAction(tr("&Step"), this);
    stepAction->setIcon(QIcon(tr(":/images/next-icon-32.png")));
    stepAction->setStatusTip(tr("Comunicar procesos"));
    connect(stepAction, SIGNAL(triggered()),
            simplejo, SLOT(comunicarProcesos()));
}

void VentanaPrincipal::crearMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
}

void VentanaPrincipal::crearToolBars()
{
    animationToolbar = new QToolBar(tr("Animate"));
    animationToolbar->addAction(stepAction);
    animationToolbar->setAllowedAreas(Qt::TopToolBarArea);

    addToolBar(animationToolbar);
}

void VentanaPrincipal::crearDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("Comunicacion"));
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setObjectName("communicationDock");

    opciones = new OptionsWidget(this);
    dock->setWidget(opciones);
    addDockWidget(Qt::RightDockWidgetArea, dock);
}

void VentanaPrincipal::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                          tr("Open model"), ".",
                          tr("simplicial complex files(*.sp)"));
    if (!fileName.isEmpty())
        leerArchivo(fileName);
}

bool VentanaPrincipal::leerArchivo(const QString &nombreArchivo)
{
    simplejo->leerArchivo(nombreArchivo);
    return true;
}
