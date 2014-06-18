#ifndef COMPLEJOSIMPLICIAL_H
#define COMPLEJOSIMPLICIAL_H

#include <QGLWidget>
#include <vector>
#include <string>

#include "grafica.h"
#include "vertex3d.h"
#include "edge.h"


class ComplejoSimplicial : public QGLWidget
{
    Q_OBJECT

public:
    ComplejoSimplicial(QWidget *parent = 0);
    ~ComplejoSimplicial();

    void leerArchivo(const QString &fileName);

public slots:
//    void reset();
    void comunicarProcesos();
    void generarIteracionAnterior();
    void setTipoComunicacion(const std::string tipoComunicacion);

protected:
    void paintEvent(QPaintEvent *event);
    void initializeGL();
    void resizeGL(int width, int height);
    void showEvent(QShowEvent *);
//    void paintGL();
    void keyPressEvent(QKeyEvent * event);
    void wheelEvent(QWheelEvent *);

private:
    void crearGradiente();
    void dibujarFondo(QPainter *painter);
    void dibujarTexto(QPainter *painter);

    void dibujar();
    void cambiarColor();
    void procesaLineaTexto(std::string cadena);
    Vertex3d leerVertice(std::string cadena);
    Edge leerArista(std::string cadena);
    void incrementarAnguloGiroY(int delta);
    void incrementarAnguloGiroX(int delta);

    void dibujarArista(Edge arista);

    void generarIteracion();

    void comunicarConfiableColoreada();
    void comunicarNoConfiableColoreada();
    void comunicarConfiableNoColoreada();
    void comunicarNoConfiableNoColoreada();

    void dibujarVertice(Vertex3d vertice);
    void dibujarArista(Vertex3d v1, Vertex3d v2);

    Grafica *grafica;
    Grafica *graficaOriginal;
    Grafica *graficaCopia;

    int anguloGiroY;
    int anguloGiroX;
    double factorEscala;
    int iteracion;
    bool seEstaRealizandoAnimacion;

    bool bCambiarColor;
    std::string tipoComunicacion;

    const double RADIO_CILINDRO;
    const double RADIO_ESFERA;
    QRadialGradient gradient;
};

#endif // COMPLEJOSIMPLICIAL_H
