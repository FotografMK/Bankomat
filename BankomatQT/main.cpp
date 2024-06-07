#include "interface.h"
#include <QtWidgets/QApplication>
#include <stdio.h>
#include <sqlite3.h>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Interface atmInterface;
    atmInterface.show();
    return app.exec();
}
