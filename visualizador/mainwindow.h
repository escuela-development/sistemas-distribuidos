#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class SimplicialComplex;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void open();

private:
    void createActions();
    void createMenus();
    bool okToContinue();
    bool loadFile(const QString &fileName);

    SimplicialComplex *simplicial;

    QMenu *fileMenu;
    QAction *openAction;
};


#endif // MAINWINDOW_H
