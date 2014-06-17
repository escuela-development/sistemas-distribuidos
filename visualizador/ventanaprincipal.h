#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QTimer>

class QAction;
class QListWidget;
class OptionsWidget;
class QToolBar;
class ComplejoSimplicial;

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    VentanaPrincipal();

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void open();

private:
    void crearActions();
    void crearMenus();
    void crearToolBars();
    void crearDockWindows();
    bool leerArchivo(const QString &nombreArchivo);

    OptionsWidget *opciones;
    ComplejoSimplicial *simplejo;
    QToolBar *animationToolbar;

    QMenu *fileMenu;
    QAction *openAction;
    QAction *exitAction;
    QAction *stepAction;
    QAction *previousStepAction;
};

#endif // VENTANAPRINCIPAL_H
