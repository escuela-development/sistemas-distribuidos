#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "tipocomunicacionwidget.h"

class QAction;
class SimplicialComplex;
class QListWidget;
class OptionsWidget;
class QToolBar;
class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void open();
    void startAnimation();
    void stopAnimation();
    void pauseAnimation();
    void stepAnimation();
    void updateActions();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createDockWindows();
    bool okToContinue();
    bool loadFile(const QString &fileName);    

    OptionsWidget *options;
    SimplicialComplex *simplicial;

    QMenu *fileMenu;
    QAction *exitAction;
    QAction *openAction;    
    QAction *playAction;
    QAction *pauseAction;
    QAction *stopAction;
    QAction *stepAction;

    QToolBar *animationToolbar;

    TipoComunicacionWidget* tipoComunicacion;
    QListWidget *customerList;

    bool isAnimationActive;
    QTimer *timer;
    const int TIME_INTERVAL_MSEC;
};


#endif // MAINWINDOW_H
