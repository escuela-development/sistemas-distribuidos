#include <QtGui>
#include <QtOpenGL>
#include <QDebug>
#include <QTimer>
#include "GL/glu.h"

#include <iostream>
#include <sstream>
#include <cstddef>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cmath>

#include <cstdlib>
#include <cstring>

#include "complejosimplicial.h"
#include "vertex3d.h"
#include "edge.h"
#include "mecanismos_comunicacion.h"
#include "Utils.h"

ComplejoSimplicial::ComplejoSimplicial(QWidget *parent)
    : QGLWidget(parent),
      RADIO_CILINDRO(0.05),
      RADIO_ESFERA(0.15)
{
    setFocusPolicy(Qt::StrongFocus);
//    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    setTipoComunicacion(STR_CONFIABLE_COLOREADA);

    bCambiarColor = false;

    iteracion = 0;
    anguloGiroX = 0;
    anguloGiroY = 0;
    factorEscala = 1.0;

    QSize size = QSize(500, 500);
    setMinimumSize(size);

    grafica = new Grafica;
    graficaOriginal = new Grafica;
    graficaCopia = new Grafica;

    setAutoFillBackground(false);
    setFormat(QGLFormat(QGL::SampleBuffers));   // support antialiasing
    crearGradiente();
}

ComplejoSimplicial::~ComplejoSimplicial()
{
    delete grafica;
}

void ComplejoSimplicial::paintEvent(QPaintEvent *event)
{
    dibujar();
}

void ComplejoSimplicial::initializeGL()
{
//    qglClearColor(Qt::gray);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
}

void ComplejoSimplicial::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-50, 50, -50, 50, -10, 10);
    gluPerspective(60, (GLfloat)width/height, 0.5, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

//    GLfloat x = GLfloat(width) / height;
//    gluPerspective(65, x, 1, 20.0);
//    glMatrixMode(GL_MODELVIEW);
}

//void ComplejoSimplicial::paintGL()
//{
//    GLfloat light_pos[] = {10, 20, 0, 0};

//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////    glLoadIdentity();
////    gluLookAt(30, -30, 0,
////              0.0, 0.0, 0,
////              0.0, 0.0, 1);

//    dibujar();

//}

//void ComplejoSimplicial::dibujar()
//{
//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
//    glLoadIdentity();

//    glRotated(anguloGiroX,1,0,0);
//    glRotated(anguloGiroY,0,1,0);

//    glBegin(GL_LINES);
//    {
//        std::vector<Vertex3d> vertices = grafica->getVertices();
//        std::vector<Edge> aristas = grafica->getAristas();

//        for (unsigned i = 0; i < aristas.size(); i++) {
//            Edge a = aristas[i];
//            Vertex3d v1 = vertices[a.getVertex1()];
//            Vertex3d v2 = vertices[a.getVertex2()];

//            glVertex3d(v1.getX(), v1.getY(), v1.getZ());
//            glVertex3d(v2.getX(), v2.getY(), v2.getZ());

//            cambiarColor();

//        }
//    }

//    glEnd();
//    glPopMatrix();

//}

void ComplejoSimplicial::dibujar()
{
    makeCurrent();
    GLfloat light_position[] = {10, 20, 0, 0};

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

//    glShadeModel(GL_FLAT);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
//    glEnable(GL_MULTISAMPLE);

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-50, 50, -50, 50, -100, 100);
//    glMatrixMode(GL_MODELVIEW);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-50, 50, -50, 50, -10, 10);
    gluPerspective(60, (GLfloat)width()/height(), 0.5, 100.0);
    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();

    glClearColor(0.4, 0.4, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    gluLookAt(0, 20, 0,
              0, 0, 0,
              0, 0, 1);

    Vertex3d light = Vertex3d(light_position[0], light_position[1], light_position[2]);
    dibujarVertice(light);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glPushMatrix();

    glRotated(anguloGiroX,1,0,0);
    glRotated(anguloGiroY,0,1,0);

    glScalef(factorEscala, factorEscala, factorEscala);

//    glEnable(GL_MULTISAMPLE);
//    glShadeModel(GL_FLAT);

//    glBegin(GL_LINES);
//    {
//        std::vector<Vertex3d> vertices = grafica->getVertices();
//        std::vector<Edge> aristas = grafica->getAristas();

//        for (unsigned i = 0; i < aristas.size(); i++) {
//            Edge a = aristas[i];
//            Vertex3d v1 = vertices[a.getVertex1()];
//            Vertex3d v2 = vertices[a.getVertex2()];

//            glVertex3d(v1.getX(), v1.getY(), v1.getZ());
//            glVertex3d(v2.getX(), v2.getY(), v2.getZ());

//            cambiarColor();

//        }
//    }
//    glEnd();


//    glBegin(GL_LINES);
//    {
//        glLineWidth(10);

//        // x
//        glColor3f(1, 0, 0);
//        glVertex3f(0, 0, 0);
//        glVertex3f(50, 0, 0);

//        // y
//        glColor3f(0, 1, 0);
//        glVertex3f(0, 0, 0);
//        glVertex3f(0, 50, 0);

//        // z
//        glColor3f(0, 0, 1);
//        glVertex3d(0, 0, 0);
//        glVertex3d(0, 0, 50);

//        glLineWidth(1);
//    }
//    glEnd();

    std::vector<Vertex3d> vertices = grafica->getVertices();
    std::vector<Edge> aristas = grafica->getAristas();

    for (unsigned i = 0; i < aristas.size(); i++) {
        Edge a = aristas[i];
        Vertex3d v1 = vertices[a.getVertex1()];
        Vertex3d v2 = vertices[a.getVertex2()];

        dibujarVertice(v1);
        dibujarVertice(v2);

        glBegin(GL_LINES); {
            glLineWidth(5);

          glVertex3f(v1.getX(), v1.getY(), v1.getZ());
          glVertex3f(v2.getX(), v2.getY(), v2.getZ());
        }
        glEnd();
        //dibujarArista(v1, v2);
    }

    if (tipoComunicacion == STR_CONFIABLE_NO_COLOREADA) {
        std::vector<Vertex3d> vertices = grafica->getVertices();

        for (unsigned i = 1; i < vertices.size(); i++) {
            dibujarVertice(vertices[i]);
        }
    }
    // end miguel

//    glDisable(GL_CULL_FACE);
//    glDisable(GL_DEPTH_TEST);

    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    QPainter painter(this);
//    painter.beginNativePainting();
//    renderText(0.0, 0.0, 0.0, QString("Texto prueba"));
//    painter.endNativePainting();

    painter.setRenderHint(QPainter::Antialiasing);
    dibujarTexto(&painter);
    painter.end();

}


void ComplejoSimplicial::leerArchivo(const QString &fileName)
{
    std::ifstream file(fileName.toStdString().c_str(), std::ios::in);
    if (!file) {
        std::cerr << "No fue posible leer el archivo " << fileName.toStdString() << std::endl;
        return;
    }

    anguloGiroX = 0;
    anguloGiroY = 0;
    factorEscala = 1.0;
    iteracion = 0;


    QApplication::setOverrideCursor(Qt::WaitCursor);

    int numero_vertices;
    int numero_aristas;
    std::string line;

    while(std::getline(file, line)) {

        std::istringstream iss_num_vertices(line);
        iss_num_vertices >> numero_vertices;

        std::vector<Vertex3d> verticesLeidos;
        for (int i = 0; i < numero_vertices; i++) {
            std::getline(file, line);
            Vertex3d v = leerVertice(line);
            verticesLeidos.push_back(v);
        }

        std::getline(file, line);
        std::istringstream iss_num_edges(line);
        iss_num_edges >> numero_aristas;

        std::vector<Edge> aristasLeidas;
        for (int i = 0; i < numero_aristas; i++) {
            std::getline(file, line);
            Edge a = leerArista(line);
            aristasLeidas.push_back(a);
        }

        grafica->limpiar();     // permite releer el archivo

        grafica->addVertices(verticesLeidos);
        grafica->addAristas(aristasLeidas);

        // guardar una copia de la grafica original
        graficaOriginal->addVertices(verticesLeidos);
        graficaOriginal->addAristas(aristasLeidas);
    }

    QApplication::restoreOverrideCursor();

    // update opengl
    update();
}

Vertex3d ComplejoSimplicial::leerVertice(std::string cadena)
{
    double valores[4];
    char *ptrToken;

    char *ptrCadena = new char[cadena.size()+1];
    strcpy(ptrCadena, cadena.c_str());

    int contador = 0;
    ptrToken = strtok(ptrCadena, " (),");
    while (ptrToken != NULL) {
        valores[contador++] = atof(ptrToken);
        ptrToken = strtok(NULL, " (),");
    }

    Vertex3d vertex = Vertex3d(valores[1],
            valores[2], valores[3]);

    return vertex;
}

Edge ComplejoSimplicial::leerArista(std::string cadena)
{
    char *ptrCadena = new char[cadena.size() + 1];
    strcpy(ptrCadena, cadena.c_str());

    int contador = 0;
    double valores[2];

    char *ptrToken = strtok(ptrCadena, ",");
    while (ptrToken != NULL) {
        valores[contador++] = atof(ptrToken);
        ptrToken = strtok(NULL, ",");
    }

    Edge edge = Edge(valores[0], valores[1]);
    return edge;
}


void ComplejoSimplicial::incrementarAnguloGiroY(int delta)
{
    if (anguloGiroY > 360)
        anguloGiroY = 0;

    anguloGiroY += delta;
}

void ComplejoSimplicial::incrementarAnguloGiroX(int delta)
{
    if (anguloGiroX > 360)
        anguloGiroX = 0;

    anguloGiroX += delta;
}

void ComplejoSimplicial::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A:
        incrementarAnguloGiroY(-10);
        break;

    case Qt::Key_D:
        incrementarAnguloGiroY(10);
        break;

    case Qt::Key_W:
        incrementarAnguloGiroX(-10);
        break;

    case Qt::Key_S:
        incrementarAnguloGiroX(10);
        break;

    default:
        QWidget::keyPressEvent(event);
        break;
    }

    update();

}

void ComplejoSimplicial::wheelEvent(QWheelEvent *event)
{
    double numDegrees = event->delta() / 8.0;
    double numSteps   = numDegrees / 15.0;
    factorEscala      += numSteps;

    update();
}

void ComplejoSimplicial::comunicarConfiableColoreada()
{
    std::vector<Edge> aristasGeneradas;
    std::vector<Vertex3d> verticesGenerados;

    std::vector<Edge> aristas = grafica->getAristas();
    std::vector<Vertex3d> vertices = grafica->getVertices();

    for (unsigned i = 0; i < aristas.size(); i++) {
        int index_vertex_1;
        int index_vertex_2;

        index_vertex_1 = aristas[i].getVertex1();
        index_vertex_2 = aristas[i].getVertex2();

        std::vector<Vertex3d> result = comunicarDeFormaColoreada(vertices[index_vertex_1],
                                                                     vertices[index_vertex_2]);
        std::copy(result.begin(), result.end(),
                  std::back_inserter(verticesGenerados));

        // generar las nuevas aristas
        // en una comunicacion confiable coloreada entre dos
        // procesos se generara solo una arista nueva y
        // cuatro vertices siempre
        std::vector<Vertex3d>::iterator iter = verticesGenerados.end();

        iter--;     // apuntar al ultimo elemento
        iter--;     // apuntar al penultimo elemento

        int indice_actual = iter - verticesGenerados.begin();
        Edge nueva_arista = Edge(indice_actual - 1, indice_actual);
        aristasGeneradas.push_back(nueva_arista);
    }

    grafica->limpiar();
    grafica->addVertices(verticesGenerados);
    grafica->addAristas(aristasGeneradas);

}


void ComplejoSimplicial::comunicarNoConfiableColoreada()
{
    std::vector<Edge> aristasGeneradas;
    std::vector<Vertex3d> verticesGenerados;

    std::vector<Edge> aristas = grafica->getAristas();
    std::vector<Vertex3d> vertices = grafica->getVertices();

    for (unsigned i = 0; i < aristas.size(); i++) {
        int index_vertex_1;
        int index_vertex_2;

        index_vertex_1 = aristas[i].getVertex1();
        index_vertex_2 = aristas[i].getVertex2();

        std::vector<Vertex3d> result = comunicarDeFormaColoreada(vertices[index_vertex_1],
                                                                     vertices[index_vertex_2]);
        std::copy(result.begin(), result.end(),
                  std::back_inserter(verticesGenerados));

        // generar las nuevas aristas
        // en una comunicacion no segura coloreada entre dos
        // procesos se generaran tres aristas nuevas y
        // cuatro vertices siempre
        unsigned NUM_ARISTAS_GENERADAS = 3;
        std::vector<Vertex3d>::iterator iter = verticesGenerados.end();

        iter--;     // apuntar al ultimo elemento

        for (unsigned i = 0; i < NUM_ARISTAS_GENERADAS; i++) {
            int indice_actual = iter - verticesGenerados.begin();
            Edge nueva_arista = Edge(indice_actual - 1, indice_actual);
            aristasGeneradas.push_back(nueva_arista);

            iter--;
        }
    }

    grafica->limpiar();
    grafica->addVertices(verticesGenerados);
    grafica->addAristas(aristasGeneradas);

//    qDebug() << "Vertices";
//    qDebug() << print(grafica->getVertices()).c_str();
//    qDebug() << "Aristas";
//    qDebug() << print(grafica->getAristas()).c_str();
}

void ComplejoSimplicial::comunicarConfiableNoColoreada()
{
    std::vector<Edge> aristasGeneradas;
    std::vector<Vertex3d> verticesGenerados;

    std::vector<Edge> aristas = grafica->getAristas();
    std::vector<Vertex3d> vertices = grafica->getVertices();

    for (unsigned i = 0; i < aristas.size(); i++) {
        int index_vertex_1;
        int index_vertex_2;

        index_vertex_1 = aristas[i].getVertex1();
        index_vertex_2 = aristas[i].getVertex2();

        std::vector<Vertex3d> result = comunicarDeFormaNoColoreada(vertices[index_vertex_1],
                                                                   vertices[index_vertex_2]);
        // solo nos interesa el vertice central
        verticesGenerados.push_back(result.at(1));

        // generar las nuevas aristas
        // en una comunicacion confiable no coloreada entre dos
        // procesos no  se generaran nuevas aristas
    }

    grafica->limpiar();
    grafica->addVertices(verticesGenerados);
    grafica->addAristas(aristasGeneradas);
}

void ComplejoSimplicial::comunicarNoConfiableNoColoreada()
{
    std::vector<Edge> aristasGeneradas;
    std::vector<Vertex3d> verticesGenerados;

    std::vector<Edge> aristas = grafica->getAristas();
    std::vector<Vertex3d> vertices = grafica->getVertices();

    for (unsigned i = 0; i < aristas.size(); i++) {
        int index_vertex_1;
        int index_vertex_2;

        index_vertex_1 = aristas[i].getVertex1();
        index_vertex_2 = aristas[i].getVertex2();

        std::vector<Vertex3d> result = comunicarDeFormaNoColoreada(vertices[index_vertex_1],
                                                                   vertices[index_vertex_2]);
        std::copy(result.begin(), result.end(),
                  std::back_inserter(verticesGenerados));

        // generar las nuevas aristas
        // en una comunicacion no segura no coloreada entre dos
        // procesos se generaran dos aristas nuevas y
        // tres vertices siempre
        unsigned NUM_ARISTAS_GENERADAS = 2;
        std::vector<Vertex3d>::iterator iter = verticesGenerados.end();

        iter--;     // apuntar al ultimo elemento

        for (unsigned i = 0; i < NUM_ARISTAS_GENERADAS; i++) {
            int indice_actual = iter - verticesGenerados.begin();
            Edge nueva_arista = Edge(indice_actual - 1, indice_actual);
            aristasGeneradas.push_back(nueva_arista);

            iter--;
        }
    }

    grafica->limpiar();
    grafica->addVertices(verticesGenerados);
    grafica->addAristas(aristasGeneradas);

//    qDebug() << "Vertices";
//    qDebug() << print(grafica->getVertices()).c_str();
//    qDebug() << "Aristas";
//    qDebug() << print(grafica->getAristas()).c_str();

}

/**
 * This function is called when the user press the "next button" on
 * the toolbar and cause the application make one round of communication.
 *
 * @brief ComplejoSimplicial::comunicarProcesos
 */
void ComplejoSimplicial::comunicarProcesos()
{
    generarIteracion();
    iteracion++;

    update();
}

void ComplejoSimplicial::generarIteracion()
{
    if (tipoComunicacion == STR_CONFIABLE_COLOREADA) {
        comunicarConfiableColoreada();
    }

    if (tipoComunicacion == STR_NO_CONFIABLE_COLOREADA) {
        comunicarNoConfiableColoreada();
    }

    if (tipoComunicacion == STR_CONFIABLE_NO_COLOREADA) {
        comunicarConfiableNoColoreada();
    }

    if (tipoComunicacion == STR_NO_CONFIABLE_NO_COLOREADA) {
        comunicarNoConfiableNoColoreada();
    }
}

void ComplejoSimplicial::setTipoComunicacion(const std::string tipoComunicacion)
{
    qDebug() << tipoComunicacion.c_str();

    this->tipoComunicacion = tipoComunicacion;
}

void ComplejoSimplicial::cambiarColor()
{
    if (bCambiarColor) {
        glColor3f(1, 1, 1);
    }
    else {
        glColor3f(0, 0, 0);
    }

    bCambiarColor = !bCambiarColor;
}

void ComplejoSimplicial::crearGradiente()
{
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    gradient.setCenter(0.45, 0.50);
    gradient.setFocalPoint(0.40, 0.45);
    gradient.setColorAt(0.0, QColor(105, 146, 182));
    gradient.setColorAt(0.4, QColor(81, 113, 150));
    gradient.setColorAt(0.8, QColor(16, 56, 121));
}

void ComplejoSimplicial::dibujarFondo(QPainter *painter)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawRect(rect());
}

void ComplejoSimplicial::dibujarTexto(QPainter *painter)
{
//    const int Margin = 11;
//    const int Padding = 6;

//    QTextDocument textDocument;
//    textDocument.setDefaultStyleSheet("* { color: #FFEFEF }");
//    textDocument.setHtml("Aqui va la descripcion");
//    textDocument.setTextWidth(textDocument.size().width());

//    QRect rect(QPoint(0, 0), textDocument.size().toSize()
//               + QSize(2 * Padding, 2 * Padding));
//    painter->translate(width() - rect.width() - Margin,
//                       height() - rect.height() - Margin);
//    painter->setPen(QColor(255, 239, 239));
//    painter->setBrush(QColor(255, 0, 0, 31));
//    painter->drawRect(rect);

//    painter->translate(Padding, Padding);
//    textDocument.drawContents(painter);

    QString text = tr("Click and drag with");
    QFontMetrics metrics = QFontMetrics(font());
    int border = qMax(4, metrics.leading());

    QRect rect = metrics.boundingRect(0, 0, width() - 2*border,
                                      int(height()*0.125),
                                      Qt::AlignCenter | Qt::TextWordWrap, text);
    painter->setRenderHint(QPainter::TextAntialiasing);
    painter->fillRect(QRect(0, 0, width(), rect.height() + 2*border),
                      QColor(0, 0, 0, 127));
    painter->setPen(Qt::white);
    painter->fillRect(QRect(0, 0, width(), rect.height() + 2*border),
                      QColor(0, 0, 0, 127));
    painter->drawText((width() - rect.width())/2, border,
                      rect.width(), rect.height(),
                      Qt::AlignCenter | Qt::TextWordWrap, text);
}

void ComplejoSimplicial::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
}

void ComplejoSimplicial::generarIteracionAnterior()
{
    if (iteracion > 0) {

        // generar todas las iteraciones antes de la actual
        // empezando desde la grafica original
        int iteraciones_por_realizar = iteracion - 1;

        grafica->limpiar();
        grafica->addVertices(graficaOriginal->getVertices());
        grafica->addAristas(graficaOriginal->getAristas());

        qDebug() << "Iteraciones por realizar " << iteraciones_por_realizar;
        while (iteraciones_por_realizar >= 1) {
            generarIteracion();
            iteraciones_por_realizar--;
        }

        iteracion--;

        update();
    }
}

void ComplejoSimplicial::dibujarVertice(Vertex3d vertice)
{
    float material_difuso[] = {1, 0, 0, 0};

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_difuso);
    glTranslatef(vertice.getX(), vertice.getY(), vertice.getZ());
    dibujarEsfera(RADIO_ESFERA, 50, 50);
    glPopMatrix();
}

void ComplejoSimplicial::dibujarArista(Vertex3d v1, Vertex3d v2)
{
    double w1 = v2.getX() - v1.getX();
    double w2 = v2.getY() - v1.getY();
    double w3 = v2.getZ() - v1.getZ();

    double ax1 = -w2;
    double ax2 = w1;
    double ax3 = 0;

    double l = sqrt((w1*w1) + (w2*w2) + (w3*w3));
    double angle = (180.0 * acos(w3/l)) / M_PI;

    float material_difuso[] = {1, 1, 0, 0};

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_difuso);
    glTranslatef(v1.getX(), v1.getY(), v1.getZ());
    glRotatef(angle, ax1, ax2, ax3);
    dibujarCilindro(RADIO_CILINDRO, l, 20, 20);
    glPopMatrix();
}
