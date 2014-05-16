#include <QtWidgets>
#include <QDebug>

#include "simplicialcomplex.h"
#include "mainwindow.h"

#include<iostream>

MainWindow::MainWindow()
{
    simplicial = new SimplicialComplex;
    setCentralWidget(simplicial);

    createActions();
    createMenus();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // implement logic here
}

void MainWindow::createActions()
{
    openAction = new QAction(tr("&Open..."), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing simplicial complex model"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
}

void MainWindow::open()
{
    if (okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                              tr("Open model"), ".",
                              tr("simplicial complex files(*.sp)"));
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::okToContinue()
{
    return true;
}

bool MainWindow::loadFile(const QString &fileName)
{
    simplicial->readFile(fileName);
    return true;
}
