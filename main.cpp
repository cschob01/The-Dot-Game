#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create the MainWindow instance and show it
    MainWindow window;
    window.show();

    return app.exec();
}
