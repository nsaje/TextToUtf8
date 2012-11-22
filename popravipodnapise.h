#ifndef POPRAVIPODNAPISE_H
#define POPRAVIPODNAPISE_H

#include <QMainWindow>
#include <QtCore/QStringList>

namespace Ui {
class PopraviPodnapise;
}

class PopraviPodnapise : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PopraviPodnapise(QWidget *parent = 0);
    ~PopraviPodnapise();

protected:
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
    void dropEvent(QDropEvent * event);
private:
    Ui::PopraviPodnapise *ui;
};

#endif // POPRAVIPODNAPISE_H
