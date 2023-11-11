#include "Pair.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pair w;
    w.show();
    return a.exec();
}
