#include "trianglewindow.h"
#include <QApplication>




TriangleWindow::TriangleWindow() : GameWindow()
{
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setSamples(16);

    setFormat(format);

    this->AddGameState("Dreieck_test", new DreieckGameState(this));
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TriangleWindow window;
    window.show();

    return app.exec();
}
