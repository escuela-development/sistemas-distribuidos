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

    bool leerArchivo(const QString &fileName);

public slots:
//    void reset();
    void comunicarProcesos();
    void setTipoComunicacion(const std::string tipoComunicacion);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent(QKeyEvent * event);

private:
    void dibujar();
    void cambiarColor();
    void procesaLineaTexto(std::string cadena);
    Vertex3d leerVertice(std::string cadena);
    Edge leerArista(std::string cadena);
    void incrementarAnguloGiroY(int delta);
    void incrementarAnguloGiroX(int delta);

    void dibujarVertice(Vertex3d vertice);
    void dibujarArista(Edge arista);

    void comunicarConfiableColoreada();
    void comunicarNoConfiableColoreada();
    void comunicarConfiableNoColoreada();
    void comunicarNoConfiableNoColoreada();


    Grafica *grafica;
    Grafica *graficaOriginal;
    Grafica *graficaCopia;

    int anguloGiroY;
    int anguloGiroX;

    bool bCambiarColor;
    std::string tipoComunicacion;
};

#endif // COMPLEJOSIMPLICIAL_H
