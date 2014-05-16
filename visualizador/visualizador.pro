HEADERS += \
    graph.h \
    vertex2d.h \
    mainwindow.h \
    simplicialcomplex.h

SOURCES += \
    graph.cpp \
    vertex2d.cpp \
    mainwindow.cpp \
    simplicialcomplex.cpp \
    main.cpp

QT += opengl

unix|win32: LIBS += -lGLU

RESOURCES += \
    visualizador.qrc
