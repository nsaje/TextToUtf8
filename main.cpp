#include <QtGui/QApplication>
#include "popravipodnapise.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PopraviPodnapise w;
    w.show();
    
    return a.exec();
}
