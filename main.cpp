#include <QtGui/QApplication>
#include "popravipodnapise.h"
#include "popravljalec.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PopraviPodnapise w;
    Popravljalec p;

    QObject::connect(&w, SIGNAL(datotekaIzbrana(QString)), &p, SLOT(obdelajDatoteko(QString)));
    QObject::connect(&p, SIGNAL(error(QString)), &w, SLOT(error(QString)));
    QObject::connect(&p, SIGNAL(info(QString, QString)), &w, SLOT(info(QString, QString)));
    QObject::connect(&p, SIGNAL(reset()), &w, SLOT(reset()));

    w.show();
    
    return a.exec();
}
