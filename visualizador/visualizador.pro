HEADERS += \
    vertex2d.h \
    optionswidget.h \
    Utils.h \
    vertex3d.h \
    grafica.h \
    edge.h \
    complejosimplicial.h \
    ventanaprincipal.h \
    mecanismos_comunicacion.h \
    triangle.h

SOURCES += \
    vertex2d.cpp \
    main.cpp \
    optionswidget.cpp \
    vertex3d.cpp \
    grafica.cpp \
    edge.cpp \
    complejosimplicial.cpp \
    ventanaprincipal.cpp \
    mecanismos_comunicacion.cpp \
    Utils.cpp \
    triangle.cpp

QT += opengl gui widgets

unix|win32: LIBS += -lGLU

RESOURCES += \
    visualizador.qrc

