#include "iconeditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IconEditor w;
    w.setImage("/home/sxd/Desktop/1.png");


    w.setZoomFactor(5);
    w.show();

    return a.exec();
}
