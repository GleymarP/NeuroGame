#include "Homepage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Homepage w;
    w.show();
    return a.exec();
}
