#ifndef POPRAVIPODNAPISE_H
#define POPRAVIPODNAPISE_H

#include <QMainWindow>
#include <QtCore/QStringList>
#include <QStringList>

namespace Ui {
class PopraviPodnapise;
}

class PopraviPodnapise : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PopraviPodnapise(QWidget *parent = 0);
    ~PopraviPodnapise();

signals:
    void datotekaIzbrana(QString path);
    void response(int response);
public slots:
    void prikaziPopravke(QStringList *popravki);
    void error(QString description);
    void info(QString naslov, QString description);
    void reset();

protected:
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
    void dropEvent(QDropEvent * event);
private:
    Ui::PopraviPodnapise *ui;
};

#endif // POPRAVIPODNAPISE_H
