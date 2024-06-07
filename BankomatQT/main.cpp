#include "interface.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Interface atmInterface;
    atmInterface.show();
    return app.exec();
}