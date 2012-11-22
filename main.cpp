#include <QtGui/QApplication>
#include "popravipodnapise.h"
#include "popravljalec.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PopraviPodnapise w;
    Popravljalec p;

    QObject::connect(&w, SIGNAL(datotekaIzbrana(QString)), &p, SLOT(obdelajDatoteko(QString)));

    w.show();
    
    return a.exec();
}
