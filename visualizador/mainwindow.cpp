#include <QtWidgets>
#include <QDebug>
#include <QTimer>

#include "simplicialcomplex.h"
#include "mainwindow.h"
#include "tipocomunicacionwidget.h"
#include "optionswidget.h"

#include<iostream>

MainWindow::MainWindow()
    :TIME_INTERVAL_MSEC(1000)
{
    simplicial = new SimplicialComplex;
    setCentralWidget(simplicial);

    isAnimationActive = false;

    createActions();
    createMenus();
    createToolBars();
    createDockWindows();

    updateActions();

    // initialize animation timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), simplicial, SLOT(animate()));    
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

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()),
            this, SLOT(close()));

    playAction = new QAction(tr("&Play"), this);
    playAction->setIcon(QIcon(":/images/play-icon-32.png"));
    playAction->setStatusTip(tr("Play animation"));
    connect(playAction, SIGNAL(triggered()),
            this, SLOT(startAnimation()));
    connect(playAction, SIGNAL(triggered()),
            this, SLOT(updateActions()));

    stopAction = new QAction(tr("&Stop"), this);
    stopAction->setIcon(QIcon(":/images/stop-icon-32.png"));
    stopAction->setStatusTip(tr("Stop animation"));
    connect(stopAction, SIGNAL(triggered()),
            this, SLOT(stopAnimation()));
    connect(stopAction, SIGNAL(triggered()),
            this, SLOT(updateActions()));
    connect(stopAction, SIGNAL(triggered()),
            simplicial, SLOT(reset()));

    pauseAction = new QAction(tr("&Pause"), this);
    pauseAction->setIcon(QIcon(":/images/pause-icon-32.png"));
    pauseAction->setStatusTip(tr("Pause animation"));

    stepAction = new QAction(tr("&Step"), this);
    stepAction->setIcon(QIcon(tr(":/images/next-icon-32.png")));
    stepAction->setStatusTip(tr("Step animation"));
    connect(stepAction, SIGNAL(triggered()),
            this, SLOT(stepAnimation()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
}

void MainWindow::createToolBars()
{
    animationToolbar = new QToolBar(tr("Animate"));
    animationToolbar->addAction(playAction);
    animationToolbar->addAction(pauseAction);
    animationToolbar->addAction(stepAction);
    animationToolbar->addAction(stopAction);
    animationToolbar->setAllowedAreas(Qt::TopToolBarArea);

    addToolBar(animationToolbar);
}

void MainWindow::createDockWindows()
{
//    QDockWidget *dock = new QDockWidget(tr("Customers"), this);
//    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
//    customerList = new QListWidget(dock);
//    customerList->addItems(QStringList()
//                           << "John Doe, Harmony"
//                           << "Jane Doe");
//    dock->setWidget(customerList);
//    addDockWidget(Qt::RightDockWidgetArea, dock);

//    QDockWidget *dock = new QDockWidget(tr("Comunicacion"), this);
//    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
//    dock->setObjectName("comunicacionDockWidget");

//    tipoComunicacion = new TipoComunicacionWidget(dock);
//    dock->setWidget(tipoComunicacion);
//    addDockWidget(Qt::RightDockWidgetArea, dock);

    QDockWidget *dock = new QDockWidget(tr("Comunicacion"));
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setObjectName("communicationDock");

    options = new OptionsWidget(this);
    connect(options, SIGNAL(setCommunicationType(QString)),
            simplicial, SLOT(setCommunicationType(QString)));
    dock->setWidget(options);
    addDockWidget(Qt::RightDockWidgetArea, dock);
}

void MainWindow::updateActions()
{
    if (isAnimationActive) {
        playAction->setEnabled(false);
        pauseAction->setEnabled(true);
        stopAction->setEnabled(true);
        stepAction->setEnabled(false);
    }
    else {
        playAction->setEnabled(true);
        stepAction->setEnabled(true);
        stopAction->setEnabled(false);
        pauseAction->setEnabled(false);
    }
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

void MainWindow::startAnimation()
{
    isAnimationActive = true;
    timer->start(TIME_INTERVAL_MSEC);
}

void MainWindow::stopAnimation()
{
    isAnimationActive = false;
    timer->stop();
}

void MainWindow::stepAnimation()
{
    QTimer::singleShot(TIME_INTERVAL_MSEC,
                       simplicial, SLOT(animate()));
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
