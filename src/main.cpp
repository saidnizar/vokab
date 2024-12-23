#include "vokab.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Vokab w;
    w.show();
    return a.exec();
}
