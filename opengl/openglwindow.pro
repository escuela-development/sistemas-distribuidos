include(openglwindow.pri)

SOURCES += \
    main.cpp

RESOURCES = simplicial_complex_visualizer.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/gui/openglwindow
INSTALLS += target
