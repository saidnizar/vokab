#include "MainWindow.h"
#include "VocabFileHandler.h"

#include <QApplication>

VocabFileHandler *VocabFileHandler::instance = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(500,500);
    w.show();
    return a.exec();
}
