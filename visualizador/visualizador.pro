HEADERS += \
    graph.h \
    vertex2d.h \
    mainwindow.h \
    simplicialcomplex.h \
    tipocomunicacionwidget.h \
    ui_tipocomunicacionwidget.h \
    optionswidget.h \
    Utils.h

SOURCES += \
    graph.cpp \
    vertex2d.cpp \
    mainwindow.cpp \
    simplicialcomplex.cpp \
    main.cpp \
    tipocomunicacionwidget.cpp \
    optionswidget.cpp

QT += opengl gui widgets

unix|win32: LIBS += -lGLU

RESOURCES += \
    visualizador.qrc

FORMS += \
    tipocomunicacionwidget.ui
