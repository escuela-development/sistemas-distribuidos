HEADERS += \
    graph.h \
    vertex2d.h \
    mainwindow.h \
    simplicialcomplex.h \
    tipocomunicacionwidget.h \
    ui_tipocomunicacionwidget.h \
    optionswidget.h \
    Utils.h \
    vertex3d.h \
    grafica.h \
    edge.h \
    complejosimplicial.h \
    ventanaprincipal.h

SOURCES += \
    graph.cpp \
    vertex2d.cpp \
    mainwindow.cpp \
    simplicialcomplex.cpp \
    main.cpp \
    tipocomunicacionwidget.cpp \
    optionswidget.cpp \
    vertex3d.cpp \
    grafica.cpp \
    edge.cpp \
    complejosimplicial.cpp \
    ventanaprincipal.cpp

QT += opengl gui widgets

unix|win32: LIBS += -lGLU

RESOURCES += \
    visualizador.qrc

FORMS += \
    tipocomunicacionwidget.ui
